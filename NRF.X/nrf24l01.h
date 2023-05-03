/*
 * File:   nrf24l01.h
 * Author: marti
 *
 * Created on March 27, 2023, 8:52 PM
 */

#ifndef NRF24L01_H
#define NRF24L01_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <xc.h>

/* USER CONFIGURATION */
#define _XTAL_FREQ 8000000UL

#define CE D2
#define CSN D3

/* MACROS */
// work around for X ## Y which would normally be concatenated before expansion
#define UNWRAP_CONCAT(X, Y) X##Y

// macro to get the pin and tris register for a given pin
#define PIN(X) UNWRAP_CONCAT(R, X)
#define TRIS(X) UNWRAP_CONCAT(TRIS, X)

/* CONFIGURATION REGISTER */
#define NRF_REGISTER_CONFIG 0x00
#define NRF_REGISTER_EN_AA 0x01
#define NRF_REGISTER_EN_RXADDR 0x02
#define NRF_REGISTER_SETUP_AW 0x03
#define NRF_REGISTER_SETUP_RETR 0x04
#define NRF_REGISTER_RF_CH 0x05
#define NRF_REGISTER_RF_SETUP 0x06
#define NRF_REGISTER_STATUS 0x07
#define NRF_REGISTER_OBSERVE_TX 0x08
#define NRF_REGISTER_RPD 0x09
#define NRF_REGISTER_RX_ADDR_P0 0x0A
#define NRF_REGISTER_RX_ADDR_P1 0x0B
#define NRF_REGISTER_RX_ADDR_P2 0x0C
#define NRF_REGISTER_RX_ADDR_P3 0x0D
#define NRF_REGISTER_RX_ADDR_P4 0x0E
#define NRF_REGISTER_RX_ADDR_P5 0x0F
#define NRF_REGISTER_TX_ADDR 0x10
#define NRF_REGISTER_PX_PW_P0 0x11
#define NRF_REGISTER_PX_PW_P1 0x12
#define NRF_REGISTER_PX_PW_P2 0x13
#define NRF_REGISTER_PX_PW_P3 0x14
#define NRF_REGISTER_PX_PW_P4 0x15
#define NRF_REGISTER_PX_PW_P5 0x16
#define NRF_REGISTER_FIFO_STATUS 0x17
#define NRF_REGISTER_DYNPD 0x1C
#define NRF_REGISTER_FEATURE 0x1D

// follwed by 1 to 5 LSByte
// 000A AAAA
#define NRF_COMMAND_R_REGISTER 0b00000000
#define NRF_COMMAND_W_REGISTER 0b00100000

// followed by 1 to 32 LSByte
#define NRF_COMMAND_RX_PAYLOAD 0b01100001
#define NRF_COMMAND_TX_PAYLOAD 0b10100000

// followed by 0 bytes
#define NRF_COMMAND_FLUSH_RX 0b11100010
#define NRF_COMMAND_FLUSH_TX 0b11100001

// followed by 0 bytes
#define NRF_COMMAND_REUSE_TX_PL 0b11100011
#define NRF_COMMAND_REUSE_TX_PL 0b11100011

// followed by 1 byte
#define NRF_COMMAND_R_RX_PL_WID 0b01100000

// followed by 1 to 32 LSByte
// 1010 1PPP
#define NRF_COMMAND_W_ACK_PAYLOAD 0b10101000

// followed by 1 to 32 LSByte
#define NRF_COMMAND_W_TX_PAYLOAD_NO_ATK 0b10110000

// followed by 0 bytes
#define NRF_COMMAND_NOP 0b11111111

// CONFIG
#define NRF_CONFIG_PRIM_RX 0x01

    /* General functions */
    // copy an array
    void arrcpy(uint8_t *dst, uint8_t *src, uint8_t len)
    {
        for (uint8_t i = 0; i < len; i++)
        {
            dst[i] = src[i];
        }
    }

/* Internal functions */
// write a command followed by data, internal only, returns status
#define _NRF_COMMAND(X)                  \
    PIN(CSN) = 0;                        \
    uint8_t status = SPI_write(command); \
    for (uint8_t i = 0; i < len; i++)    \
    {                                    \
        X;                               \
    }                                    \
    PIN(CSN) = 1;                        \
    return status;

    // write a command followed by data, internal only, returns status, data is overwritten with response
    uint8_t nrf_command_with_data_overwrite(uint8_t command, uint8_t *data, uint8_t len){
        _NRF_COMMAND(data[i] = SPI_write(data[i]))}

    // write a command followed by data, internal only, returns status
    uint8_t nrf_command_with_data(uint8_t command, uint8_t *data, uint8_t len){
        _NRF_COMMAND(SPI_write(data[i]))}

    // write to a register, internal only, returns status
    uint8_t nrf_write_register(uint8_t reg, uint8_t *data, uint8_t len)
    {
        return nrf_command_with_data(reg | NRF_COMMAND_W_REGISTER, data, len);
    }

    // read from a register, internal only, returns status, data is overwritten with response
    uint8_t nrf_read_register(uint8_t reg, uint8_t *data, uint8_t len)
    {
        return nrf_command_with_data_overwrite(reg | NRF_COMMAND_R_REGISTER, data, len);
    }

    // write payload, internal only, returns status
    uint8_t nrf_write_payload(uint8_t *data, uint8_t len)
    {
        uint8_t status = nrf_command_with_data(NRF_COMMAND_TX_PAYLOAD, data, len);
        PIN(CE) = 1;
        __delay_us(20);
        PIN(CE) = 0;
        return status;
    }

    // write a command, internal only, returns status
    uint8_t nrf_write_command(uint8_t command)
    {
        PIN(CSN) = 0;
        uint8_t status = SPI_write(command);
        PIN(CSN) = 1;
        return status;
    }

// get status register, internal only
#define nrf_get_status() nrf_write_command(NRF_COMMAND_NOP)

    // flush RX and TX FIFOs, internal only
    void nrf_flush_rxtx()
    {
        uint8_t data = 0b01110000; // clear RX_DR, TX_DS, MAX_RT
        nrf_write_register(NRF_REGISTER_STATUS, &data, 1);
        nrf_write_command(NRF_COMMAND_FLUSH_TX);
        nrf_write_command(NRF_COMMAND_FLUSH_RX);
    }

    /* USER FUNCTIONS */
    // setup the nRF24L01
    void nrf_setup(uint8_t *addr, uint8_t addr_size, uint8_t payload_size)
    {
        TRIS(CSN) = 0;
        TRIS(CE) = 0;

        PIN(CSN) = 1;
        PIN(CE) = 0;

        __delay_ms(100);

        uint8_t data[5];

        data[0] = 0x0B;
        nrf_write_register(NRF_REGISTER_CONFIG, (uint8_t *)&data, 1); // 1 byte CRC, POWER UP, PRX
        data[0] = 0x00;
        nrf_write_register(NRF_REGISTER_EN_AA, (uint8_t *)&data, 1); // Disable auto ack
        data[0] = 0x01;
        nrf_write_register(NRF_REGISTER_EN_RXADDR, (uint8_t *)&data, 1); // Enable data pipe 0
        data[0] = 0b00000011;

        switch (addr_size)
        {
        case 3:
            data[0] = 0x01;
            break;
        case 4:
            data[0] = 0x02;
            break;
        case 5:
            data[0] = 0x03;
            break;
        }

        nrf_write_register(NRF_REGISTER_SETUP_AW, (uint8_t *)&data, 1); // 5 byte address
        data[0] = 0x00;
        nrf_write_register(NRF_REGISTER_SETUP_RETR, (uint8_t *)&data, 1); // Retransmit disabled
        data[0] = 0x01;
        nrf_write_register(NRF_REGISTER_RF_CH, (uint8_t *)&data, 1); // Randomly chosen RF channel
        data[0] = 0x26;
        nrf_write_register(NRF_REGISTER_RF_SETUP, (uint8_t *)&data, 1); // 250kbps, 0dBm
        data[0] = payload_size;
        nrf_write_register(NRF_REGISTER_PX_PW_P0, (uint8_t *)&data, 1); // RX payload = 1 byte

        arrcpy(data, addr, addr_size);
        nrf_write_register(NRF_REGISTER_RX_ADDR_P0, data, addr_size);

        arrcpy(data, addr, addr_size);
        nrf_write_register(NRF_REGISTER_TX_ADDR, data, addr_size);

        nrf_flush_rxtx();
    }

    // set as RX mode
    void nrf_set_rx_mode()
    {
        uint8_t config;
        nrf_read_register(NRF_REGISTER_CONFIG, &config, 1);

        PIN(CE) = 1;

        if (config & NRF_CONFIG_PRIM_RX)
            return;

        config |= NRF_CONFIG_PRIM_RX;
        nrf_write_register(NRF_REGISTER_CONFIG, &config, 1);
    }

    // set as TX mode
    void nrf_set_tx_mode()
    {
        uint8_t config;
        nrf_read_register(NRF_REGISTER_CONFIG, &config, 1);

        PIN(CE) = 0;

        if (!(config & NRF_CONFIG_PRIM_RX))
            return;

        config &= ~NRF_CONFIG_PRIM_RX;
        nrf_write_register(NRF_REGISTER_CONFIG, &config, 1);
    }

    // check if data is available
    uint8_t nrf_data_available()
    {
        uint8_t status = nrf_get_status();
        return (status & 0x40) != 0;
    }

    // send a char array, should be set to TX mode first
    void nrf_send(uint8_t *data, uint8_t len)
    {
        nrf_write_payload(data, len);

        // Wait for char to be sent
        uint8_t stat;
        do
        {
            stat = nrf_get_status();
        } while ((stat & 0x20) == 0);

        // Clear status bit
        uint8_t clear = 0x20;
        nrf_write_register(NRF_REGISTER_STATUS, &clear, 1);
    }

    // read a char array, should be set to RX mode first
    uint8_t nrf_read(uint8_t *data, uint8_t len)
    {
        uint8_t status = nrf_read_register(NRF_COMMAND_RX_PAYLOAD, data, len);

        // Clear status bit
        nrf_write_command(NRF_COMMAND_FLUSH_RX);
        uint8_t clear = 0x40;
        nrf_write_register(NRF_REGISTER_STATUS, &clear, 1);
        return status;
    }

#ifdef __cplusplus
}
#endif

#endif /* NRF24L01_H */
