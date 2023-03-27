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
#include <stdio.h>
#include "uart.h"
#include "spi.h"
#include "stdbool.h"

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



uint8_t RXTX_ADDR[3] = {0xB5, 0x23, 0xA5}; // Randomly chosen address





// convert a char to a binary string
char *char_to_binary_string(char character)
{
    static char output[10];

    sprintf(output, BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(character));

    return output;
}

// copy an array
void arrcpy(uint8_t *dst, uint8_t *src, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
}



// write a command followed by data, internal only, returns status
uint8_t nrf_command(uint8_t command, uint8_t *data, uint8_t len)
{
    CSN = 0;

    uint8_t status = SPI_write(command);
    for (uint8_t i = 0; i < len; i++)
        data[i] = SPI_write(data[i]);

    CSN = 1;

    return status;
}


// write to a register, internal only, returns status
uint8_t nrf_write_register(uint8_t reg, uint8_t *data, uint8_t len)
{
    return nrf_command(reg | COMMAND_W_REGISTER, data, len);
}


// read from a register, internal only, returns status
uint8_t nrf_read_register(uint8_t reg, uint8_t *data, uint8_t len)
{
    return nrf_command(reg | COMMAND_R_REGISTER, data, len);
}


// write payload, internal only, returns status
uint8_t nrf_write_payload(uint8_t *data, uint8_t len)
{
    uint8_t status = nrf_write_register(COMMAND_TX_PAYLOAD, data, len);
    CE = 1;
    __delay_us(20);
    CE = 0;
}


// write a command, internal only, returns status
uint8_t nrf_write_command(uint8_t command)
{
    CSN = 0;
    uint8_t status = SPI_write(command);
    CSN = 1;
    return status;
}


// get status register
#define nrf_get_status() nrf_write_command(COMMAND_NOP)


// flush RX and TX FIFOs
void nrf_flush_rxtx()
{
    uint8_t data = 0b01110000; // clear RX_DR, TX_DS, MAX_RT
    nrf_write_register(REGISTER_STATUS, &data, 1);
    nrf_write_command(COMMAND_FLUSH_TX);
    nrf_write_command(COMMAND_FLUSH_RX);
}


#define CONFIG_PRIM_RX 0x01


// set as RX mode
void nrf_set_rx_mode()
{
    uint8_t config;
    nrf_read_register(REGISTER_CONFIG, &config, 1);

    CE = 1; 

    if (config & CONFIG_PRIM_RX)
        return;

    config |= CONFIG_PRIM_RX;
    nrf_write_register(REGISTER_CONFIG, &config, 1);
}


// set as TX mode
void nrf_set_tx_mode()
{
    uint8_t config;
    nrf_read_register(REGISTER_CONFIG, &config, 1);

    if (!(config & CONFIG_PRIM_RX))
        return;

    config &= ~CONFIG_PRIM_RX;
    nrf_write_register(REGISTER_CONFIG, &config, 1);

    CE = 0;
}


// check if data is available
uint8_t nrf_data_available()
{
    uint8_t status = nrf_get_status();
    return (status & 0x40) != 0;
}


// setup the nRF24L01
void nrf_setup()
{
    CSN = 1;
    CE = 0;

    // give the nRF24L01 time to set up:
    __delay_ms(2);

    uint8_t data[5];

    data[0] = 0x0B;
    nrf_write_register(REGISTER_CONFIG, &data, 1); // 1 byte CRC, POWER UP, PRX
    data[0] = 0x00;
    nrf_write_register(REGISTER_EN_AA, &data, 1); // Disable auto ack
    data[0] = 0x01;
    nrf_write_register(REGISTER_EN_RXADDR, &data, 1); // Enable data pipe 0
    data[0] = 0x01;
    nrf_write_register(REGISTER_SETUP_AW, &data, 1); // 3 byte address
    data[0] = 0x00;
    nrf_write_register(REGISTER_SETUP_RETR, &data, 1); // Retransmit disabled
    data[0] = 0x01;
    nrf_write_register(REGISTER_RF_CH, &data, 1); // Randomly chosen RF channel
    data[0] = 0x26;
    nrf_write_register(REGISTER_RF_SETUP, &data, 1); // 250kbps, 0dBm
    data[0] = 0x01;
    nrf_write_register(REGISTER_PX_PW_P0, &data, 1); // RX payload = 1 byte

    arrcpy(data, RXTX_ADDR, sizeof(RXTX_ADDR));
    nrf_write_register(REGISTER_RX_ADDR_P0, data, sizeof(RXTX_ADDR));

    arrcpy(data, RXTX_ADDR, sizeof(RXTX_ADDR));
    nrf_write_register(REGISTER_TX_ADDR, data, sizeof(RXTX_ADDR));

    nrf_flush_rxtx();

    UART_Write_Text("Init\n");
}


// send a char
void nrf_tx_char(uint8_t ch)
{
    nrf_write_payload(&ch, 1);

    // Wait for char to be sent
    uint8_t stat;
    do
    {
        stat = nrf_get_status();
    } while ((stat & 0x20) == 0);

    // Clear status bit
    uint8_t data = 0x20;
    nrf_write_register(REGISTER_STATUS, &data, 1);
}

// receive a char
uint8_t nrf_rx_char()
{
    uint8_t data;
    nrf_read_register(COMMAND_RX_PAYLOAD, &data, 1);
    // Clear status bit
    uint8_t clear = 0x40;
    nrf_write_register(REGISTER_STATUS, &clear, 1);
    return data;
}


void SendChar(char *args)
{
    nrf_set_tx_mode();
    nrf_tx_char(args[0]);
    UART_Write_Text("Char sent\n");
}

void ReceiveChar()
{
    nrf_set_rx_mode();
    uint8_t ch = nrf_rx_char();
    UART_Write_Text("RX = ");
    UART_Write(ch);
    UART_Write_Text("\n");
}

int main()
{
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;

    OSCCONbits.IRCF = 111;

    UART_Init(9600, _XTAL_FREQ);

    UART_Write_Text("BOOTED\n");

    SPI_init_master();

    __delay_ms(10);
    nrf_setup();

    __delay_ms(2);
#define sender
    while (1)
    {
#ifdef sender
        SendChar("K");
        __delay_ms(500);
        SendChar("V");
        __delay_ms(500);
        SendChar("B");
        __delay_ms(500);
        SendChar("L");
        __delay_ms(500);

#else
        ReceiveChar();
        __delay_ms(500);
#endif
    }
}