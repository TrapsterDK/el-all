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

#define TMR 178

int antal = 0;
int sek = 00;
int min = 00;
int tim = 00;
int a_sek = 15;
int a_min = 00;
int a_tim = 00;

int update_timer = 0;
bool alarm = true;
bool drive_mode = false;
int drive_timer = 0;

void update_screen(){
    //clamp values to make sure no buffer overflow happens
    CLAMP(sek,0,60);
    CLAMP(min,0,60);
    CLAMP(tim,0,24);
    
    //buffers
    char a_str[9];
    char str[9]; 
    
    //insert time using sprintf
    sprintf(str, "%02d:%02d:%02d", tim, min, sek);
    sprintf(a_str, "%02d:%02d:%02d", a_tim, a_min, a_sek);
    
    //update lcd screen
    LCD_Clear();
    
    LCD_Set_Cursor(0,0);
    LCD_putrs("kl:");
    
    LCD_Set_Cursor(0,4);
    LCD_putrs(str);
    
    LCD_Set_Cursor(1,0);
    LCD_putrs("al:");
    
    LCD_Set_Cursor(1,4);
    LCD_putrs(a_str);
    
    //show drive mode is on 
    if (drive_mode == true){
        LCD_Set_Cursor(0,15);
        LCD_putrs("!");
    }
    
    //show alarm is on
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
        update_timer++;

        //if triggered one sec has passed
        if(antal >= 1000)
        {
            //update sek, min, tim
            antal = 0;
            sek++;
            if (sek >= 60){
                sek = 0;
                min++;
                if (min >= 60){
                    min = 0;
                    tim++;
                    if (tim >= 24){
                        tim = 0;
                    }
                }
            }
            
            //check if alarm is triggered and should initialize drive mode
            if (a_sek == sek & a_min == min & a_tim == tim & alarm == true){
                drive_mode = true; 
                RB2 = 1;
            }
        }
        
        //driver timer to make sure it drives for 1 sec
        if(drive_timer != 0){
            drive_timer--;
        }
        
        
        //check if button pressed to disable car
        if (RB5 == 1){
            drive_mode = false;
            RB2 = 0;
        }
        
        TMR0IF = 0;
        TMR0 = TMR;
    }
}

int main()
{
    OPTION_REG = 0b10000100;
    INTCON = 0b11100000;
    TMR0 = TMR;
    
    TRISD = 0x00;
    TRISE = 0x00;
    CMCON = 0b00000111;
    ADCON1 = 0x4E;
    
    LCD_Init();
    
    //hc-sr04
    TRISB = 0b11110011;           //RB4 as Input PIN (ECHO)
    T1CON = 0x10;                 //Initialize Timer Module
    
    TRISC = 0;
    while(1)
    {        
        if(RC1 == 0 || RC1 && drive_timer == 0){
            if(drive_mode){
                int dist;
                
                TMR1H = 0;                  //Sets the Initial Value of Timer
                TMR1L = 0;                  //Sets the Initial Value of Timer

                RB3 = 1;               //TRIGGER HIGH
                __delay_us(10);               //10uS Delay
                RB3 = 0;               //TRIGGER LOW

                while(!RB4);           //Waiting for Echo
                T1CONbits.TMR1ON = 1;               //Timer Starts
                while(RB4);            //Waiting for Echo goes LOW
                T1CONbits.TMR1ON = 0;               //Timer Stops

                dist = (TMR1L | (TMR1H<<8));   //Reads Timer Value
                dist = dist/58.82;                //Converts Time to Distance
                dist = dist + 1;                  //Distance Calibration
                
                if(dist>=2 && dist<=300)          //Check whether the result is valid or not
                {   
                    drive_timer = 1000;
                    RC1 = 1;
                }
                else{
                    RC1 = 0;
                }
            }
            else{
                RC1 = 0;
            }
        }
      
        if (update_timer >= 1000){
            update_timer = 0;
            update_screen();
        }
    }
    return 0;
}
