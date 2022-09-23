/* 
 * File:   spi.h
 * Author: marti
 *
 * Created on 24. august 2022, 13:27
 */


#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

//maybe use SSPIF for transmission reception
//this library does not handle SS, CS, SSN or CSN

void SPI_init_slave(){
    SSPCON = 0b00100101; //enable serial port, SPI slave mode disable 
    TRISC5 = 0; //p77
    TRISC3 = 1; //p77
}

void SPI_init_master(){
    SSPCON = 0b00100000; //enable serial port, SPI master mode, Fosc/4
    TRISC5 = 0; //p77
    TRISC3 = 0; //p77
}

void SPI_write(uint8_t write){
    SSPBUF = write;
   
    while(!SSPSTATbits.BF);
}

uint8_t SPI_data_ready(){
    return SSPSTATbits.BF;
}

void SPI_wait_data_ready(){
    while(!SSPSTATbits.BF);
}

uint8_t SPI_read(){
    return SSPBUF;
}

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

