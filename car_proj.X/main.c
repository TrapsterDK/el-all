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

//timer 0
#define TMR 178
int antal = 0;

//start time
int sek = 00;
int min = 00;
int tim = 00;

//alarm
int a_sek = 15;
int a_min = 00;
int a_tim = 00;

int update_timer = 0;
bool alarm = true;
bool drive_mode = false;
int drive_timer = 0;

void update_screen(){
    //buffers 9 len for [2 digits, semicolon, 2 digits, semicolon, 2 digits, null terminator]
    char a_str[9];
    char str[9]; 
    
    //insert time using sprintf %02d for 2 digits with leading 0, d meaning integer/digit
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

void __interrupt() ISR()
{  
    //timer 0 interrupt
    if(TMR0IF == 1)
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

                // buzzer
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
        
        // reset timer 0
        TMR0IF = 0;
        TMR0 = TMR;
    }
}

int main()
{
    //timer registers
    OPTION_REG = 0b10000100;
    INTCON = 0b11100000;
    TMR0 = TMR;
    
    //lcd registers
    TRISD = 0x00;
    TRISE = 0x00;
    CMCON = 0b00000111;
    ADCON1 = 0x4E;
    
    LCD_Init();
    
    //RB4 hc-sr04 echo, RB3 hc-sr04 trig, RB2 buzzer
    TRISB = 0b11110011;           //RB4 as Input PIN (ECHO)
    //timer 1
    T1CON = 0x10;
    
    //RC1 drive forward, RC2 drive backward
    TRISC = 0;
    while(1)
    {
        // if not driving or driven for at least one second
        if(RC1 == 0 || RC1 && drive_timer == 0){
            // test if alarm has been triggered
            if(drive_mode){
                int dist;

                //timer setup
                TMR1H = 0;
                TMR1L = 0;

                //hc-sr04 high low transition, 10us
                RB3 = 1;
                __delay_us(10);
                RB3 = 0;

                //wait for echo response
                while(!RB4);
                //start timer
                T1CONbits.TMR1ON = 1;
                //wait for echo to end  
                while(RB4);
                //stop timer    
                T1CONbits.TMR1ON = 0

                //read timer value
                dist = (TMR1L | (TMR1H<<8));

                //convert to cm 
                dist = dist/58.82;
                dist = dist + 1;
                
                // 2 as as noice margin, 300 as max distance while hc-sr04 can measure approx 400cm
                if(dist>=2 && dist<=300)
                {   
                    // drive for 1 second
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
      
        //update screen every second done here instead of interupt as it takes 4ms to draw a characther
        if (update_timer >= 1000){
            update_timer = 0;
            update_screen();
        }
    }
    return 0;
}
