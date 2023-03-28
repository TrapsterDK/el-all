/*
 * File:   spi.h
 * Author: marti
 *
 * Created on 24. august 2022, 13:27
 */

#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C"
{
#endif
    // initialize the spi, as master
    void SPI_init_master()
    {
        SSPCON = 0b01100001; // SSPEN = 1, CKP = 0, SSPM = 0b0010
        SSPSTAT = 0b01000000; // CKE = 1 must be rising edge
        TRISC4 = 1;
        TRISC5 = 0;
        TRISC3 = 0;
    }

    // write a byte to the spi
    uint8_t SPI_write(uint8_t data)
    {
        SSPBUF = data;
        while (!BF)
            ; 
        return SSPBUF;
    }

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */
