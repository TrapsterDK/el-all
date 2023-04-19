#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config PWRTE = ON

#include <xc.h>

#define _XTAL_FREQ 4000000UL

#define SDA IO0
#define SCL IO1

#define MISO IO3
#define MOSI IO4
#define SCK IO5

void main(void)
{
    ANSEL = 0;    // set ports as IO
    ADCON0 = 0;   // shutdown ad converter
    CMCON = 0x07; // turn off comparator
    VRCON = 0;    // turn off voltage reference

    TRISIO = 0;
    GPIO = 0;
    
    while (1)
    {
    }
}