#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config PWRTE = ON

#include <xc.h>
#include "softwarespi.h"
#include "nrf24l01.h"

#define _XTAL_FREQ 4000000UL

#define ADDR_SIZE 5
uint8_t RADIO_ADDR[ADDR_SIZE] = {0x01, 0x04, 0x06, 0x04, 0x05};

#define PAYLOAD_SIZE 3

void send_data(uint8_t data){
    GPIO2 = 1;
    __delay_ms(10);

    // send data over IO2 pin
    for (int i = 0; i < 8; i++)
    {
        GPIO2 = (data >> i) & 1;
        __delay_ms(10);
    }

    GPIO2 = 0;
    __delay_ms(50);
}

void main(void)
{
    ANSEL = 0;    // set ports as IO
    ADCON0 = 0;   // shutdown ad converter
    CMCON = 0x07; // turn off comparator
    VRCON = 0;    // turn off voltage reference

    TRISIO = 0;
    GPIO = 0;
    
    // start spi
    SPI_init_master();

    // start nrf with address and payload size
    nrf_setup(RADIO_ADDR, ADDR_SIZE, PAYLOAD_SIZE);

    nrf_set_tx_mode();

    while (1)
    {
        GPIO2 = 1;  
        uint8_t data[PAYLOAD_SIZE] = "EE";
        nrf_send(data, PAYLOAD_SIZE);
        __delay_ms(100);
        GPIO2 = 0;
        __delay_ms(100);

        
        //send_data(data);
        /*
        uint8_t data[PAYLOAD_SIZE] = "AB";
        nrf_send(data, PAYLOAD_SIZE);
        send_data(0b00110011);
        __delay_ms(200);
        continue;
        */
        
        /*
        uint8_t status = nrf_get_status();
        send_data(status);
        */
    }
}