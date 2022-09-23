/*
 * File:   main.c
 * Author: marti
 *
 * Created on 6. september 2022, 12:32
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include<xc.h>
#include "lcd.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#define _XTAL_FREQ 10000000

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define CLAMP(x, lower, upper) x = (MIN(upper, MAX(x, lower)))

//LCD Functions Developed by Circuit Digest.
#define TMR 178
int antal = 0;
int sek = 00;
int min = 00;
int tim = 00;
int a_sek = 05;
int a_min = 00;
int a_tim = 00;
char a_str[32];
char str[32];
int mode  = 0;
int flag = 0;
int flag_2 = 0;
int flag_3 = 0;
int flag_update = 0;
bool alarm = true;
bool tone = false;
int hz_delay = 1;

int flag_4 = 0;

/*
void main(void) {
    //lcd
    TRISD = 0x00;
    TRISE = 0x00;
    CMCON = 0b00000111;
    ADCON1 = 0x4E;
    LCD_Init();
    
    //hc-sr04
    TRISB = 0b00010000;           //RB4 as Input PIN (ECHO)
    T1CON = 0x10;                 //Initialize Timer Module
    int a;
    char txt[4];
    
    while(1)
    {
        TMR1H = 0;                  //Sets the Initial Value of Timer
        TMR1L = 0;                  //Sets the Initial Value of Timer

        RB0 = 1;               //TRIGGER HIGH
        __delay_us(10);               //10uS Delay
        RB0 = 0;               //TRIGGER LOW

        while(!RB4);           //Waiting for Echo
        T1CONbits.TMR1ON = 1;               //Timer Starts
        while(RB4);            //Waiting for Echo goes LOW
        T1CONbits.TMR1ON = 0;               //Timer Stops

        a = (TMR1L | (TMR1H<<8));   //Reads Timer Value
        a = a/58.82;                //Converts Time to Distance
        a = a + 1;                  //Distance Calibration
        if(a>=2 && a<=400)          //Check whether the result is valid or not
        {
            sprintf(txt, "%03d", a);
            LCD_Clear();
            LCD_Set_Cursor(1,0);
            LCD_putrs("Distance = ");
            LCD_Set_Cursor(1,11   );
            LCD_putrs(txt);
            LCD_Set_Cursor(1,14);
            LCD_putrs("cm");
        }
        else
        {
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_putrs("Out of Range");
        }
    }
}*/

void setup2()
{
    OPTION_REG = 0b10000100;
    INTCON = 0b11100000;
    TMR0 = TMR;
    TRISB = 0b11111111;
}

void mode3(){
    tone = true;
    if (flag_2 == 0){
        RC3 = !RC3;
        flag_2 = hz_delay;
    }
    if (RB0 == 1 & flag == 0){
        flag = 500;
        a_sek = a_sek + 30;
        mode = 0;
    }
    if (RB1 == 1 & flag == 0){
        flag = 500;
        mode = 0;
    }
}
void update(){
    if (a_sek == sek & a_min == min & a_tim == tim & alarm == true){
        mode = 3;   
    }
    CLAMP(sek,0,60);
    CLAMP(min,0,60);
    CLAMP(tim,0,24);
    CLAMP(a_sek,0,60);
    CLAMP(a_min,0,60);
    CLAMP(a_tim,0,24);
     
    LCD_Clear();
    LCD_Set_Cursor(0,0);
    LCD_putrs("kl:");
    LCD_Set_Cursor(0,4);
    sprintf(str, "%02d:%02d:%02d", tim, min, sek);
    LCD_putrs(str);
    LCD_Set_Cursor(1,0);
    LCD_putrs("al:");
    LCD_Set_Cursor(1,4);
    sprintf(a_str, "%02d:%02d:%02d", a_tim, a_min, a_sek);
    LCD_putrs(a_str);
    if (tone == true){
        LCD_Set_Cursor(0,15);
        LCD_putrs("!");
    }
    if (alarm == true){
        LCD_Set_Cursor(1,15);
        LCD_putrs("A");
        
    }
     
    
    
}
void __interrupt() ISR()         //Her lander programmet når det bliver afbrudt (interrupt))
{  
    if(TMR0IF == 1)                //Hvis det er en TIMER0 interrupt
    {
        antal++;
        flag_update++;
        
        if(antal >= 1000)
        {
            sek++;
            antal = 0;
            if (sek == 60){
                sek = 00;
                min++;
                if (min == 60){
                    tim++;
                    min = 00;
                    if (tim == 24){
                        tim = 0;
                    }
                }
            }
            

        }
        if (flag != 0){
            flag--;
        }
        if (flag_2 != 0){
            flag_2--;
        }
        if (flag_3 != 0){
            flag_3--;
        }
        if(flag_4 != 0){
            flag_4--;
        }
        
         TMR0IF = 0;
         TMR0 = TMR;

    }
    
   
}

void mode1()
{   
    
    
        if(RB7 == 1 & flag == 0){
            tim++;
            flag = 500;

        }
        if (RB6 == 1 & flag == 0){
            tim--;
            flag = 500;

        }
        if(RB5 == 1 & flag == 0){
            min++;
            flag = 500;

        }
        if (RB4 == 1 & flag == 0){
            min--;
            flag = 500;

        }
        if(RB3 == 1 & flag == 0){
            sek++;
            flag = 500;

        }
        if (RB2 == 1 & flag == 0){
            sek--;
            flag = 500;

        }
        if(RB0 == 1 & flag == 0){
            mode = 0;
            flag = 500;

        }
    
    

}
void mode2(){
    
        if(RB7 == 1 & flag == 0){
            a_tim++;
            flag = 500;

        }
        if (RB6 == 1 & flag == 0){
            a_tim--;
            flag = 500;

        }
        if(RB5 == 1 & flag == 0){
            a_min++;
            flag = 500;

        }
        if (RB4 == 1 & flag == 0){
            a_min--;
            flag = 500;

        }
        if(RB3 == 1 & flag == 0){
            a_sek++;
            flag = 500;

        }
        if (RB2 == 1 & flag == 0){
            a_sek--;
            flag = 500;

        }
        if(RB0 == 1 & flag == 0){
            mode = 0;
            flag = 500;

        }
    
}

int main()
{
    setup2();
    TRISD = 0x00;
    TRISE = 0x00;
    CMCON = 0b00000111;
    ADCON1 = 0x4E;
    
    LCD_Init();
    
    //hc-sr04
    TRISB = 0b11110111;           //RB4 as Input PIN (ECHO)
    T1CON = 0x10;                 //Initialize Timer Module
    int a;
    
    TRISC = 0;
    while(1)
    {
      if (mode == 0)
        {
          
          if(RB0 == 1 & flag == 0){
              mode = 1;
              flag = 500;

          }
          if(RB1 ==1 & flag == 0){
              mode = 2;
              flag = 500;
          }
          if(RB2 ==1 & flag == 0){
              flag = 500;
              alarm = !alarm;
        }
      }
      if (mode == 1){
          mode1();
      }
      if (mode == 2){
          mode2();
      }
      if (mode == 3){
          mode3();
      }
      
      if(tone && flag_4 == 0){
        TMR1H = 0;                  //Sets the Initial Value of Timer
        TMR1L = 0;                  //Sets the Initial Value of Timer

        RB3 = 1;               //TRIGGER HIGH
        __delay_us(10);               //10uS Delay
        RB3 = 0;               //TRIGGER LOW

        while(!RB4);           //Waiting for Echo
        T1CONbits.TMR1ON = 1;               //Timer Starts
        while(RB4);            //Waiting for Echo goes LOW
        T1CONbits.TMR1ON = 0;               //Timer Stops

        a = (TMR1L | (TMR1H<<8));   //Reads Timer Value
        a = a/58.82;                //Converts Time to Distance
        a = a + 1;                  //Distance Calibration
        if(a>=2 && a<=400)          //Check whether the result is valid or not
        {
            RC1 = 1;
        }
        else{
            RC1 = 0;
        }
      }
      
      if (flag_update >= 1000){
          flag_update = 0;
          update();
      }
      
       
        
    }
    return 0;
    
    
 
    
}
