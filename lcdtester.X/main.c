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

#define IRQ RC0
#define CE RC1
#define CSN RC2
#define SCK RC3
#define MOSI RC4
#define MISO RC5

#define IRQ_TRIS TRISC0     //input
#define CE_TRIS TRISC1      //output
#define CSN_TRIS TRISC2     //output
// trisc 3, 4, 5 setup by spi.h

#define RF24_W_REGISTER     0b00000000
#define RF24_R_REGISTER     0b00100000
#define RF24_R_RX_PAYLOAD   0b01100001
#define RF24_W_TX_PAYLOAD   0b10100000
#define RF24_FLUSH_TX       0b11100001
#define RF24_FLUSH_RX       0b11100010
#define RF24_REUSE_TX_PL    0b11100011
#define RF24_NOP            0b11111111

#define RF24_CONFIG         0x00
#define RF24_EN_AA          0x01
#define RF24_EN_RXADDR      0x02
#define RF24_SETUP_AW       0x03
#define RF24_SETUP_RETR     0x04
#define RF24_RF_CH          0x05
#define RF24_RF_SETUP       0x06
#define RF24_STATUS         0x07
#define RF24_OBSERVE_TX     0x08
#define RF24_CD             0x09
#define RF24_RX_ADDR_P0     0x0A //0x0A-0x0F p0-p5
#define RF24_TX_ADDR        0x10
#define RF24_RX_PW_P0       0x11 //0x11-0x16 p0-05
#define RF24_FIFO_STATUS    0x17

#define RF24_WRITE_REGISTER(register_) (RF24_W_REGISTER | register_)
#define RF24_READ_REGISTER(register_) (RF24_R_REGISTER | register_)

void radio_spi_command_array(uint8_t command, uint8_t *args, uint8_t size){
    CSN = 0;
    
    SPI_write(command);
    
    for(int8_t i = 0; i<size; i++){
        SPI_write(args[i]);
    }
    
    CSN = 1;
}

void radio_spi_command_single(uint8_t command, uint8_t arg){
    CSN = 0;
    
    SPI_write(command);
    
    SPI_write(arg);
    
    CSN = 1;
}

void radio_reciever_start(){
    IRQ_TRIS = 1;
    CE_TRIS = 0;
    CSN_TRIS = 0;
    CE = 1; //listen
    CSN = 1;
    SPI_init_master();
    
    //bit 3 CRC scheme, bit 2 PWR_UP, bit 1 PRIM_RX recieve high, transmit low
    radio_spi_command_single(RF24_WRITE_REGISTER(RF24_CONFIG), 0b00000111);
    //enable pipe
    radio_spi_command_single(RF24_WRITE_REGISTER(RF24_EN_RXADDR), 0b00000001);
    //set adress
    radio_spi_command_array(RF24_WRITE_REGISTER(RF24_RX_ADDR_P0), (uint8_t *)"myadr", 5);
}

void radio_transmitter_start(){
    IRQ_TRIS = 1;
    CE_TRIS = 0;
    CSN_TRIS = 0;
    CE = 0; //do not listen
    CSN = 1;
    SPI_init_master();
    
    //bit 3 CRC scheme, bit 2 PWR_UP, bit 1 PRIM_RX recieve high, transmit low
    radio_spi_command_single(RF24_WRITE_REGISTER(RF24_CONFIG), 0b00000110);
    //set adress
    radio_spi_command_array(RF24_WRITE_REGISTER(RF24_TX_ADDR), (uint8_t *)"myadr", 5);
    radio_spi_command_array(RF24_WRITE_REGISTER(RF24_RX_ADDR_P0), (uint8_t *)"myadr", 5);
}

//transmission must be 32 bytes or less
void radio_transmit_single(uint8_t *transmission, uint8_t size){
    radio_spi_command_array(RF24_WRITE_REGISTER(RF24_W_TX_PAYLOAD), transmission, size);
    CE = 1;
    __delay_us(11); //at least 10 us
    CE = 0;
}

uint8_t radio_has_recieved_packet(){
    if(IRQ){
        radio_spi_command_single(RF24_READ_REGISTER(RF24_STATUS), 0b00000000);
        uint8_t status = SPI_read();
        //bit 6 for RX_DR
        uint8_t RX_DR = status & 0b01000000;
        if(RX_DR){
            radio_spi_command_single(RF24_WRITE_REGISTER(RF24_STATUS), 0b01000000);
            
            return 1;
        }
    }
    return 0;
}

uint8_t radio_get_packets(){
    radio_spi_command_single(RF24_R_RX_PAYLOAD, 0b00000000);
    uint8_t packet = SPI_read();
    return packet;
    //bit 6 for RX_DR
}

/*
//will transmit over multiple packets
void radio_transmit_array(uint8_t *transmission, uint8_t size){
    radio_spi_command_array(RF24_WRITE_REGISTER(RF24_W_TX_PAYLOAD), transmission, size);
    CE = 1;
    CE = 0;
    CE = 1;
    radio_spi_command_single(RF24_READ_REGISTER(FIFO_STATUS), 0b00000000);
}
*/

void main()
{  
    /*
    radio_reciever_start();
    TRISB = 0b11111111;
    TRISC7 = 1;
    
    while(1)
    {
        if(radio_has_recieved_packet()){
            RC7 = 1;
            __delay_ms(2000);
            RC7 = 0;
            
            {
                PORTB = radio_get_packets();
            }
        }
    } 
    */
    radio_transmitter_start();
    
    while(1){
        radio_transmit_single((uint8_t *)0b10101010, 1);
        __delay_ms(3000);
    }
}
