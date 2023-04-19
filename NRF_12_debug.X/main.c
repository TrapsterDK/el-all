/*
 * File:   spi_test.c
 * Author: marti
 *
 * Created on 26. august 2022, 11:23
 */

#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF    // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "uart.h"

#define _XTAL_FREQ 8000000UL

// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    (byte & 0x80 ? '1' : '0'),     \
        (byte & 0x40 ? '1' : '0'), \
        (byte & 0x20 ? '1' : '0'), \
        (byte & 0x10 ? '1' : '0'), \
        (byte & 0x08 ? '1' : '0'), \
        (byte & 0x04 ? '1' : '0'), \
        (byte & 0x02 ? '1' : '0'), \
        (byte & 0x01 ? '1' : '0')

// convert a char to a binary string
char *char_to_binary_string(char character)
{
    static char output[10];

    sprintf(output, BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(character));

    return output;
}

int main()
{
    // set clock to 8MHz
    OSCCONbits.IRCF = 0x07;

    // start uart
    UART_init(9600, _XTAL_FREQ);

    // print a message to the uart
    UART_printf("BOOTED\n");

    TRISD4 = 1; // set RC4 as output

    while (1)
    {
        // wait for data on pin RC4
        while (RD4 == 0)
            ;

        __delay_ms(12);

        // read data
        uint8_t data = 0;
        for (int i = 0; i < 8; i++)
        {
            data |= (RD4 << i);
            __delay_ms(10);
        }
        UART_printf("Recieved %s\n", char_to_binary_string(data));
    }
}