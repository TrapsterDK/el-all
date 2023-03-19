/*
 * File:   main.c
 * Author: marti
 *
 * Created on October 24, 2022, 12:33 PM
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
#define _XTAL_FREQ 10000000
#include "lcdt.h"
#include <stdio.h>

void main(void) {
    OPTION_REG = 0b10000000;
    //lcd
    setup();
    TRISD = 0x00;
    TRISE = 0x00;
    CMCON = 0b00000111;
    //input anolog 4
    TRISA = 0b11111111;
    
    OPTION_REG = 0b10000000;
    
    ADCON1bits.ADFM = 1;
    ADCON1bits.PCFG = 0b1110;
    ADCON1bits.ADCS2 = 0;
    
    
    Lcd_Start();
    
    unsigned int result;
    
    //analog 
    //ADCON1 = 0b00001110;
    
    char txt[10];
    
    //7-6 clock, bit 5-3 an4, 0 power, 2 status
    ADCON0 = 0b00000001;
    while(1){
        ADCON0bits.GO = 1; 
        while (ADCON0bits.GO_DONE); 
        result = ADRESH; 
        result = result << 8; 
        result |= ADRESL;
        
        sprintf(txt, "Hey %d", result);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String(txt);
        
        __delay_ms(1000);
    }
    return;
}
