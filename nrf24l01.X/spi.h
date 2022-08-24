/* 
 * File:   spi.h
 * Author: marti
 *
 * Created on 24. august 2022, 13:27
 */

#ifndef SPI_H
#define	SPI_H

void SPI_init_slave(){
    SSPCONbits.SSPEN = 1; //p75 SSPEN enable serial ports
    //SSPSTAT = 0b00000000; //p74 SMP and CKE no idea
    TRISC5 = 0; //p77
    TRISC3 = 0; //p77
    TRISC4 = 1; //p77 SS use
}

void SPI_init_master(){
    SSPCONbits.SSPEN = 1; //75 SSPEN enable serial ports
    //SSPSTAT = 0b00000000; //74 SMP and CKE no idea
    TRISC5 = 0; //p77
    TRISC3 = 1; //p77
    TRISC4 = 1; //p77 SS use
    
}

//resets SPO mode to enable reconfigure
void SPI_reset(){
    SSPCONbits.SSPEN = 0; //SSPEN enable serial ports
}

void SPI_write(char write){
    SSPBUF = write;
    
    if(SSPCONbits.WCOL){//clear if write was a write collision
        SSPCONbits.WCOL = 0; 
    }
}

uint8_t SPI_data_ready(){
    return SSPSTATbits.BF; //check bit 8
}

void SPI_wait_data_ready(){
    while(!SSPSTATbits.BF);
}

char SPI_read(){
    return SSPBUF;
}

#endif	/* SPI_H */

