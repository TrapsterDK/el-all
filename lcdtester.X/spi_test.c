/*
 * File:   spi_test.c
 * Author: marti
 *
 * Created on 26. august 2022, 11:23
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "spi.h"

#define _XTAL_FREQ 10000000



void slave(){
    PORTB = 0b00000001;
    SPI_init_slave();
    while(1){
        if(SPI_data_ready()){
            PORTB = SPI_read();
        }
    }
}
void master(){
    SPI_init_master();
    while(1){
        PORTB = 0b00110011;
        SPI_write(0b00110011);
        __delay_ms(1000);
        PORTB = 0b11001100;
        SPI_write(0b11001100);
        __delay_ms(1000);
    }
}

void main(void) {
    TRISB = 0b00000000;
    
    slave();
    //master();
}