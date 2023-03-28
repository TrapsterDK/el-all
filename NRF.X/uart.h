/*
 * File:   uart.h
 * Author: marti
 *
 * Created on March 13, 2023, 1:09 PM
 */

#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

	// initialize the uart
	void UART_init(const long int baudrate, long _XTAL_FREQ)
	{
		BRGH = 1;												// Setting High Baud Rate
		SPBRG = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16); // Writing SPBRG Register
		SYNC = 0;												// Setting Asynchronous Mode, ie UART
		SPEN = 1;												// Enables Serial Port
		TRISC7 = 1;												// As Prescribed in Datasheet
		TRISC6 = 1;												// As Prescribed in Datasheet
		CREN = 1;												// Enables Continuous Reception
		TXEN = 1;												// Enables Transmission
	}

    
	// write a char to the uart
	void UART_write(char data)
	{
		while (!TRMT)
			;
		TXREG = data;
	}
    
    // write a string to the uart, null terminated
	void UART_write_text(char *text)
	{
		for (int i = 0; text[i] != '\0'; i++)
			UART_write(text[i]);
	}
    
	// macro printf wrapper, as vsprintf is not available
	#define UART_printf(...) \
	{ \
		char buffer[64]; \
		sprintf(buffer, __VA_ARGS__); \
		UART_write_text(buffer); \
	}

	// check if data is available
	char UART_data_ready()
	{
		return RCIF;
	}

	// read a char from the uart
	char UART_read()
	{
		while (!RCIF)
			;
		return RCREG;
	}

#ifdef __cplusplus
}
#endif

#endif /* UART_H */
