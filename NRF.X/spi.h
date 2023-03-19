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

void SPI_init_master(){
    SSPCON = 0b00100010; //pg 75/234
    SSPSTAT = 0b00000000;
    TRISCbits.TRISC5 = 0; //p77
    TRISCbits.TRISC4 = 1; //p77
    TRISCbits.TRISC3 = 0;
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
    SSPSTATbits.BF = 0;
    return SSPBUF;
}

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

