/* 
 * File:   softwarespi.h
 * Author: marti
 *
 * Created on March 27, 2023, 10:29 PM
 */

#ifndef SOFTWARESPI_H
#define	SOFTWARESPI_H

#ifdef	__cplusplus
extern "C" {
#endif

/* USER CONFIGURATION */
#define MISO IO3    
#define MOSI IO4
#define SCK IO1

    /* MACROS */
    // work around for X ## Y which would normally be concatenated before expansion
    #define UNWRAP_CONCAT(X, Y) X##Y

    // macro to get the pin and tris register for a given pin
    #define PIN(X) UNWRAP_CONCAT(GP, X)
    #define TRIS(X) UNWRAP_CONCAT(TRIS, X)

    void SPI_init_master(){
        // Set pins as output
        TRIS(SCK) = 0;
        TRIS(MOSI) = 0;
        TRIS(MISO) = 1;

        // low idle
        PIN(SCK) = 0;
        PIN(MOSI) = 0;
    }

    uint8_t SPI_write(uint8_t data){
        uint8_t read = 0;
        PIN(SCK) = 0;

        // Data transmit on rising edge of clock
        for(uint8_t i = 0; i < 8; i++){
            if(data & 0x80){
                PIN(MOSI) = 1;
            }else{
                PIN(MOSI) = 0;
            }
            PIN(SCK) = 1;
            PIN(SCK) = 0;
            
            read <<= 1;
            read |= PIN(MISO);
            data <<= 1;
        }
        read >>= 1;

        return read;
    }

#ifdef	__cplusplus
}
#endif

#endif	/* SOFTWARESPI_H */

