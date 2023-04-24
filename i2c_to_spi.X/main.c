#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config PWRTE = ON

#include <xc.h>
#include "softwarei2c.h"
#include "softwarespi.h"

#define _XTAL_FREQ 4000000UL

void __interrupt() ISR(void)
{
    if (INTCONbits.GPIF)
    {
        // I2C bit recieved
        uint8_t data = I2C_Read(0);

        // send to SPI
        uint8_t resp = SPI_write(data);

        // send response back to I2C
        I2C_Write(resp);

        INTCONbits.GPIF = 0;
    }
}

void main(void)
{
    ANSEL = 0;    // set ports as IO
    ADCON0 = 0;   // shutdown ad converter
    CMCON = 0x07; // turn off comparator
    VRCON = 0;    // turn off voltage reference

    TRISIO = 0;
    GPIO = 0;

    SPI_init_master();
    
    INTCONbits.GPIE = 1;       // enable interrupt on change
    OPTION_REGbits.INTEDG = 0; // interrupt on falling edge

    while (1)
    {
    }
}