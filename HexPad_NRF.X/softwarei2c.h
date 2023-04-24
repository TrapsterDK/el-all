/*
 * File:   SOFTWAREI2C.h
 * Author: marti
 *
 * Created on March 27, 2023, 10:29 PM
 */

#ifndef SOFTWAREI2C_H
#define SOFTWAREI2C_H

#ifdef __cplusplus
extern "C"
{
#endif

/* USER CONFIGURATION */
#define SDA A5
#define SCL A4

/* MACROS */
// work around for X ## Y which would normally be concatenated before expansion
#define UNWRAP_CONCAT(X, Y) X##Y

// macro to get the pin and tris register for a given pin
#define PIN(X) UNWRAP_CONCAT(R, X)
#define TRIS(X) UNWRAP_CONCAT(TRIS, X)

#define _XTAL_FREQ 8000000UL
    
    uint8_t I2C_Write(uint8_t data)
    {
        uint8_t i;
        for (i = 0; i < 8; i++)
        {
            if (data & 0x80)
                PIN(SDA) = 1;
            else
                PIN(SDA) = 0;
            data <<= 1;
            PIN(SCL) = 1;
            __delay_us(1);
            PIN(SCL) = 0;
            __delay_us(1);
        }
        PIN(SDA) = 1;
        PIN(SCL) = 1;
        __delay_us(1);
        i = PIN(SDA);
        PIN(SCL) = 0;
        __delay_us(1);
        return i;
    }

    uint8_t I2C_Read(uint8_t ack)
    {
        uint8_t i, data = 0;
        PIN(SDA) = 1;
        for (i = 0; i < 8; i++)
        {
            data <<= 1;
            PIN(SCL) = 1;
            __delay_us(1);
            if (PIN(SDA))
                data |= 1;
            PIN(SCL) = 0;
            __delay_us(1);
        }
        if (ack)
            PIN(SDA) = 0;
        PIN(SCL) = 1;
        __delay_us(1);
        PIN(SCL) = 0;
        __delay_us(1);
        PIN(SDA) = 1;
        return data;
    }

    void I2C_Start()
    {
        PIN(SDA) = 1;
        PIN(SCL) = 1;
        __delay_us(1);
        PIN(SDA) = 0;
        __delay_us(1);
        PIN(SCL) = 0;
        __delay_us(1);
    }

    void I2C_Stop()
    {
        PIN(SDA) = 0;
        PIN(SCL) = 1;
        __delay_us(1);
        PIN(SDA) = 1;
        __delay_us(1);
    }

    void I2C_Ack()
    {
        PIN(SDA) = 0;
        PIN(SCL) = 1;
        __delay_us(1);
        PIN(SCL) = 0;
        __delay_us(1);
        PIN(SDA) = 1;
    }

    void I2C_Nak()
    {
        PIN(SDA) = 1;
        PIN(SCL) = 1;
        __delay_us(1);
        PIN(SCL) = 0;
        __delay_us(1);
    }

    void I2C_Init()
    {
        TRIS(SDA) = 1;
        TRIS(SCL) = 1;
        PIN(SDA) = 1;
        PIN(SCL) = 1;
    }

#ifdef __cplusplus
}
#endif

#endif /* SOFTWAREI2C_H */
