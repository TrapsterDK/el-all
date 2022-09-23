/* 
 * File:   rf24l01.h
 * Author: marti
 *
 * Created on 25. august 2022, 22:18
 */

#ifndef RF24L01_H
#define	RF24L01_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "spi.h"

#define IRQ_TRIS TRISC0     //input
#define CE_TRIS TRISC1      //output
#define CSN_TRIS TRISC2     //output
#define IRQ RC0
#define CE RC1
#define CSN RC2

// trisc 3, 4, 5 setup by spi.h
#define SCK RC3
#define MOSI RC4
#define MISO RC5
    
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

//writes to spi
void radio_spi_write(uint8_t command, uint8_t *data, uint8_t size){
    CSN = 0;
    
    SPI_write(command);
    
    for(int8_t i = 0; i<size; i++){
        SPI_write(data[i]);
    }
    
    CSN = 1;
}

//write then reads from spi, fills data with data
void radio_spi_read(uint8_t command, uint8_t *data, uint8_t size){
    CSN = 0;
    
    SPI_write(command);
    
    for(int8_t i = 0; i<size; i++){
        SPI_write(data[i]);
        data[i] = SPI_read();
    }
    
    CSN = 1;
}

void radio_reciever_start(){
    
}

#ifdef	__cplusplus
}
#endif

#endif	/* RF24L01_H */

