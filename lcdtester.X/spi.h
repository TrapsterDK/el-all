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
    SSPCONbits.SSPEN = 1; //p75 SSPEN enable serial ports
    //SSPSTAT = 0b00000000; //p74 SMP and CKE no idea
    TRISC5 = 0; //p77
    TRISC3 = 1; //p77
}

void SPI_init_master(){
    SSPCONbits.SSPEN = 1; //75 SSPEN enable serial ports
    //SSPSTAT = 0b00000000; //74 SMP and CKE no idea
    TRISC5 = 0; //p77
    TRISC3 = 0; //p77
}

void SPI_write(uint8_t write){
    SSPSTATbits.BF = 0;
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

