/*
 * File:   main.c
 * Author: marti
 *
 * Created on 24. august 2022, 10:38
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

#include "spi.h"

#define IRQ RB0
#define CE RB1

#define MOSI RC4
#define MISO RC5
#define CSN RA5
#define SCK RC5

#define RF24_W_REGISTER     0b00000000
#define RF24_R_REGISTER     0b00100000
#define RF24_R_RX_PAYLOAD   0b01100001
#define RF24_W_TX_PAYLOAD   0b10100000
#define RF24_FLUSH_TX       0b11100001
#define RF24_FLUSH_RX       0b11100010
#define RF24_REUSE_TX_PL    0b11100011
#define RF24_NOP            0b11111111

#define RF24_CONFIG          0x00
#define RF24_EN_AA           0x01
#define RF24_EN_RXADDR       0x02
#define RF24_SETUP_AW        0x03
#define RF24_SETUP_RETR      0x04
#define RF24_RF_CH           0x05
#define RF24_RF_SETUP        0x06
#define RF24_SETUP           0x07
#define RF24_OBSERVE_TX      0x08
#define RF24_CD              0x09
#define RF24_RX_ADDR_P0      0x0A //0x0A-0x0F p0-p5
#define RF24_TX_ADDR         0x10
#define RF24_RX_PW_P0        0x11 //0x11-0x16 p0-05
#define RF24_FIFO_STATUS     0x17

//sends least significant byte first
void radio_spi_send_array(uint8_t *string, uint8_t size){
    for(uint8_t i = size-1; i<0; i++){
        SPI_write(string[i]);
    }
}

#define radio_spi_send(string) SPI_write(string);

void radio_reciever_start(){
    CSN = 1;
    SPI_init_master();
    
    //config
    SPI_write(RF24_CONFIG);
    //bit 3 CRC scheme, bit 2 PWR_UP, bit 1 PRIM_RX recieve high, transmit low
    SPI_write(0b00000111);
    
    //EN_AA
    SPI_write(0x2);
    //enable pipes
    SPI_write(0b00000001);
}

void radio_transmitter_start(){
    CSN = 1;
    SPI_init_master();
    
    //config
    SPI_write(0x0);
    //bit 3 CRC scheme, bit 2 PWR_UP, bit 1 PRIM_RX recieve high, transmit low
    SPI_write(0b00000110);
}

void main()
{
    radio_start();
    
    while(1)
    {
   
    }    
}
