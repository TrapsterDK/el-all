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

#define _XTAL_FREQ 8000000UL

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

#define DELAY_SPI __delay_us(20);

char* char_to_binary_string(char character){
    static char output[10];
    
    sprintf(output, BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(character));
    
    return output;
}

uint8_t execute_command(uint8_t reg, uint8_t val)
{
    CSN = 0;
    SPI_write(reg);
    DELAY_SPI
    char ret = SPI_write(val);
    CSN = 1;
    return ret;
}

uint8_t write_command(uint8_t command)
{
    CSN = 0;
    uint8_t ret = SPI_write(command);
    CSN = 1;
    return ret;
}

void write_register(uint8_t reg, uint8_t val)
{
    execute_command(reg | COMMAND_W_REGISTER, val);
}

uint8_t read_register(uint8_t reg)
{
    return execute_command(reg | COMMAND_R_REGISTER, COMMAND_NOP);
}

void write_address(uint8_t reg, uint8_t* addr, uint8_t num)
{
    CSN = 0;
    SPI_write(reg | COMMAND_W_REGISTER);
    for (uint8_t i=0; i<num; i++)
    {
      DELAY_SPI
      SPI_write(addr[i]);
    }
    CSN = 1;
}

void read_address(uint8_t reg, uint8_t* retaddr, uint8_t num)
{
    CSN = 0;
    SPI_write(reg);
    for (uint8_t i=0; i<num; i++)
        retaddr[i] = SPI_write(0);
    CSN = 1;   
}

void flush_TXRX()
{
  //Clear: data RX ready, data sent TX, Max TX retransmits
  write_register(STATUS, 0x70);
  write_command(COMMAND_FLUSH_RX);
  write_command(COMMAND_FLUSH_TX);
}


uint8_t RXTX_ADDR[3] = { 0xB5, 0x23, 0xA5 };

void rf_setup(){
    CSN = 1;
    CE = 0;
    
    __delay_ms(2);
        
    write_register(REGISTER_CONFIG, 0x0B);         //1 BYTE CRC, POWER UP, PRX
    write_register(REGISTER_EN_AA, 0x00);          //Disable auto ack
    write_register(REGISTER_EN_RXADDR, 0x01);      //Enable data pipe 0
    write_register(REGISTER_SETUP_AW, 0x01);       //3 BYTE address
    write_register(REGISTER_SETUP_RETR, 0x00);     //Retransmit disabled
    write_register(REGISTER_RF_CH, 0x01);          //Randomly chosen RF channel
    write_register(REGISTER_RF_SETUP, 0x26);       //250kbps, 0dBm
    write_register(REGISTER_PX_PW_P0, 0x01);       //RX payload = 1 BYTE
   
    write_address(REGISTER_RX_ADDR_P0, RXTX_ADDR, 3);
    write_address(REGISTER_TX_ADDR, RXTX_ADDR, 3);

    flush_TXRX();
    UART_Write_Text("Init\n");
}

void RX_mode()
{
    write_register(REGISTER_CONFIG, 0x0B);         //1 byte CRC, POWER UP, PRX
    CE = 1;
}

void TX_mode()
{
    CE = 0;
    write_register(REGISTER_CONFIG, 0x0A);         //1 byte CRC, POWER UP, PTX
}

void write_tx_payload(uint8_t num, uint8_t* data)
{
    write_address(COMMAND_TX_PAYLOAD, data, num);

    CE = 1;
    __delay_us(11);
    CE = 0;
}

uint8_t RXChar()
{
    uint8_t data;
    read_address(COMMAND_RX_PAYLOAD, &data, 1);
    //Clear status bit
    write_register(REGISTER_STATUS, 0x40);
    return data;
}

void TXChar(uint8_t ch)
{
    write_tx_payload(1, &ch);

    //Wait for char to be sent
    uint8_t stat;
    do
    {
        stat = write_command(COMMAND_NOP);
    } while ((stat & 0x20) == 0);

    //Clear status bit
    write_register(STATUS, 0x20);
}

uint8_t ReadDataAvailable()
{
    if (CE == 0)
        return 0;

    uint8_t stat = write_command(COMMAND_NOP);
    return (stat & 0x40) != 0;
}

uint8_t SendChar(char* args)
{
    uint8_t charReceived = 0;
    TXChar(args[0]);
    TX_mode();
    UART_Write_Text("SENT\n");
    return charReceived;
}

void ReceiveChar()
{
    RX_mode();  
    uint8_t ch = RXChar();
    UART_Write(ch);
    UART_Write_Text("R\n");
}



int main()
{   
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;

    UART_Write_Text("BOOTED\n");

    OSCCONbits.IRCF = 111;
    
    UART_Init(9600, _XTAL_FREQ);
 
    SPI_init_master();
    
    rf_setup();
    
    __delay_ms(2);
    while(1){
        SendChar("a");
        //ReceiveChar();
        __delay_ms(500);
    }
}