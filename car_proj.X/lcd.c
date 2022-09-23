/*
 * File: lcd.c
 *
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 *
 * LCD library source file.
 */
 
#define _XTAL_FREQ 10000000

#include <xc.h>
#include "lcd.h"

void LCD_Out ( char c ) {
    if(c & 1)
        D4 = 1;
    else
       D4 = 0;
    if(c & 2)
       D5 = 1;
    else
       D5 = 0;
    if(c & 4)
       D6 = 1;
    else
       D6 = 0;
    if(c & 8)
       D7 = 1;
    else
       D7 = 0;
}

void LCD_Write ( unsigned char c ) {

    RS = 0;
    LCD_Out(c);

    EN = 1;
    __delay_ms(4);
    EN = 0;

}

bool LCD_Init ( ) {
    // Give some time to the LCD to start function properly
    __delay_ms(20);

    // Send reset signal to the LCD
    LCD_Write(0x03);
    __delay_ms(5);
    LCD_Write(0x03);
    __delay_ms(16);
    LCD_Write(0x03);

    // Specify the data lenght to 4 bits
    LCD_Write(0x02);

    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCD_Cmd(0x28);

    // Set cursor to move from left to right
    LCD_Cmd(0x06);

    LCD_Display(true, false, false); // Turn on display and set cursor off

    LCD_Clear();
    
    return true;
}

void LCD_putc ( char c ) {

    RS = 1;
    LCD_Out((c & 0xF0) >> 4);    //Data transfer

    EN = 1;
    __delay_us(40);
    EN = 0;

    LCD_Out(c & 0x0F);

    EN = 1;
    __delay_us(40);
    EN = 0;

}

void LCD_puts ( char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
        LCD_putc(a[i]);
    }

}

void LCD_putrs ( const char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
        LCD_putc(a[i]);
    }

}
