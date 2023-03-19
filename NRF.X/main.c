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
#include <stdio.h>
#include "uart.h"
#include "spi.h"

//https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

#define _XTAL_FREQ 8000000

#define CE RD2
#define CSN RD3

#define REGISTER_CONFIG 0x00
#define REGISTER_EN_AA 0x01
#define REGISTER_EN_RXADDR 0x02
#define REGISTER_SETUP_AW 0x03
#define REGISTER_SETUP_RETR 0x04
#define REGISTER_RF_CH 0x05
#define REGISTER_RF_SETUP 0x06
#define REGISTER_STATUS 0x07
#define REGISTER_OBSERVE_TX 0x08
#define REGISTER_RPD 0x09
#define REGISTER_RX_ADDR_P0 0x0A
#define REGISTER_RX_ADDR_P1 0x0B
#define REGISTER_RX_ADDR_P2 0x0C
#define REGISTER_RX_ADDR_P3 0x0D
#define REGISTER_RX_ADDR_P4 0x0E
#define REGISTER_RX_ADDR_P5 0x0F
#define REGISTER_TX_ADDR 0x10
#define REGISTER_PX_PW_P0 0x11
#define REGISTER_PX_PW_P1 0x12
#define REGISTER_PX_PW_P2 0x13
#define REGISTER_PX_PW_P3 0x14
#define REGISTER_PX_PW_P4 0x15
#define REGISTER_PX_PW_P5 0x16
#define REGISTER_FIFO_STATUS 0x17
#define REGISTER_DYNPD 0x1C
#define REGISTER_FEATURE 0x1D

// follwed by 1 to 5 LSByte
// 000A AAAA
#define COMMAND_R_REGISTER 0b00000000
#define COMMAND_W_REGISTER 0b00100000

// followed by 1 to 32 LSByte
#define COMMAND_RX_PAYLOAD 0b01100001
#define COMMAND_TX_PAYLOAD 0b10100000

// followed by 0 bytes
#define COMMAND_FLUSH_RX 0b11100010
#define COMMAND_FLUSH_TX 0b11100001

// followed by 0 bytes
#define COMMAND_REUSE_TX_PL 0b11100011
#define COMMAND_REUSE_TX_PL 0b11100011

// followed by 1 byte
#define COMMAND_R_RX_PL_WID 0b01100000

// followed by 1 to 32 LSByte
// 1010 1PPP
#define COMMAND_W_ACK_PAYLOAD 0b10101000

// followed by 1 to 32 LSByte
#define COMMAND_W_TX_PAYLOAD_NO_ATK 0b10110000

// followed by 0 bytes
#define COMMAND_NOP 0b11111111 

#define READ_REGISTER(regi) (COMMAND_R_REGISTER | regi)
#define WRITE_REGISTER(regi) (COMMAND_W_REGISTER | regi)

char* char_to_binary_string(char character){
    static char output[10];
    
    sprintf(output, BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(character));
    
    return output;
}

void send(){
    CSN = 0;
    
    SPI_write(READ_REGISTER(REGISTER_CONFIG));
    
    //UART_Write_Text((char *)char_to_binary_string((char)SPI_read()));
    
    __delay_us(20);
    
    SSPBUF = 0b1001100;
    
    while(!SSPSTATbits.BF);
    
    UART_Write_Text((char *)char_to_binary_string((char)SSPBUF));

    CSN = 1;
    __delay_ms(10);
    
    CSN = 0;
    
    SPI_write(WRITE_REGISTER(REGISTER_CONFIG));
    
    __delay_us(20);
    
    SPI_write(0b00110011);
    
    CSN = 1;
}

int main()
{   
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;

    CSN = 1;
    
    OSCCONbits.IRCF = 111;
    
    UART_Init(9600, _XTAL_FREQ);
 
    SPI_init_master();
    while(1){
        send();
        UART_Write_Text("New\n");

        __delay_ms(1000);
    }
}