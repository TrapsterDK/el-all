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

/* USER CONFIGURATION */
#define MISO C4
#define MOSI C5
#define SCK C3

/* MACROS */
// work around for X ## Y which would normally be concatenated before expansion
#define UNWRAP_CONCAT(X, Y) X##Y

// macro to get the pin and tris register for a given pin
#define PIN(PIN) UNWRAP_CONCAT(R, PIN)
#define TRIS(PIN) UNWRAP_CONCAT(TRIS, PIN)

    // initialize the spi, as master
    void SPI_init_master()
    {
        SSPCON = 0b01100001; // pg 75/234
        SSPSTAT = 0b01000000; // CKE = 1 must be rising edge
        TRIS(MISO) = 1;
        TRIS(MOSI) = 0;
        TRIS(SCK) = 0;
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
