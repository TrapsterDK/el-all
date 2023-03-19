
#define _XTAL_FREQ 8000000
#include <xc.h>

#pragma config FOSC = INTOSCCLK	        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config MCLRE = ON
#pragma config FCMEN  = OFF
#pragma config CPD = OFF 
#pragma config IESO  = OFF

void setup()
{
    CMCON0 = 0b00000111;
    ANSEL = 0b00000000;
}
int main()
{
    setup();
    
    TRISA = 0;
    
    while(1)
    {
        RA5 = 1;
    }
}
