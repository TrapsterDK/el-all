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
#include "stdio.h"
#include "lcd.h"
#define _XTAL_FREQ 10000000

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
    
    while(1){
    //hc-sr04
        //__delay_ms(10);
        LCD_Clear();
        LCD_Set_Cursor(1,0);
        LCD_putrs("  HELLO WORLD!  ");
        return;
    }
    /*
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
            LCD_Set_Cursor(1,11);
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
        __delay_ms(400);
    }*/
    /*
    while(1){
    //hc-sr04
        //__delay_ms(10);
        LCD_Clear();
        LCD_Set_Cursor(1,0);
        LCD_putrs("  HELLO WORLD!  ");
        return;
    }
    */
}
