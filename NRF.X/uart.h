/* 
 * File:   uart.h
 * Author: marti
 *
 * Created on March 13, 2023, 1:09 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void UART_Init(const long int baudrate, long _XTAL_FREQ)
{
    BRGH = 1;                                     //Setting High Baud Rate
    SPBRG = (_XTAL_FREQ - baudrate*16)/(baudrate*16);                                    //Writing SPBRG Register
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port
    TRISC7 = 1;                                   //As Prescribed in Datasheet
    TRISC6 = 1;                                   //As Prescribed in Datasheet
    CREN = 1;                                     //Enables Continuous Reception
    TXEN = 1;                                     //Enables Transmission
}

void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
}

void UART_Write_Text(char *text)
{
  for(int i=0;text[i]!='\0';i++)
    UART_Write(text[i]);
}

char UART_Data_Ready()
{
  return RCIF;
}

char UART_Read()
{
  while(!RCIF);
  return RCREG;
}

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

