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

#define SOFTWARE_SPI

#include <xc.h>

#ifdef SOFTWARE_SPI
#include "softwarespi.h"
#else
#include "spi.h"
#endif

#include "uart.h"
#include "nrf24l01.h"

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

#define ADDR_SIZE 5
uint8_t RADIO_ADDR[ADDR_SIZE] = {0x01, 0x04, 0x06, 0x04, 0x05};

#define sender
#define PAYLOAD_SIZE 3

int main()
{
    // set clock to 8MHz
    OSCCONbits.IRCF = 0x07;

    // start uart
    UART_init(9600, _XTAL_FREQ);

    // print a message to the uart
    UART_printf("BOOTED\n");

    // start spi
    SPI_init_master();

    // start nrf with address and payload size
    nrf_setup(RADIO_ADDR, ADDR_SIZE, PAYLOAD_SIZE);

    // set the nrf to tx or rx mode
#ifdef sender
    nrf_set_tx_mode();
#else
    nrf_set_rx_mode();
#endif

    while (1)
    {
        // send data if sender is defined
#ifdef sender
        
        uint8_t data[PAYLOAD_SIZE] = "AB";
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < PAYLOAD_SIZE-1; j++)
            {  
                data[j] += 1;
            }
            nrf_send(data, PAYLOAD_SIZE);
            __delay_ms(500);
            UART_printf("Sent\n");
        }
#else
        // wait for data
        while (!nrf_data_available())
            ;

        // read data
        uint8_t data[PAYLOAD_SIZE];
        nrf_read(data, PAYLOAD_SIZE);
        UART_printf("Recieved %s\n", data);
#endif
    }
}