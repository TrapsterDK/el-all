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
        SSPCON = 0b01100001; // pg 75/234
        SSPSTAT = 0b01000000; // CKE = 1 must be rising edge
        TRISCbits.TRISC5 = 0; // p77
        TRISCbits.TRISC4 = 1; // p77
        TRISCbits.TRISC3 = 0;
    }

    // write a byte to the spi
    uint8_t SPI_write(uint8_t data)
    {
        SSPBUF = data; // Put command into SPI buffer
        while (!BF)
            ;          // Wait for the transfer to finish
        return SSPBUF; // Save the read value
    }

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */
