#define _XTAL_FREQ 10000000
#define RS RE1
#define EN RE0
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#include <xc.h>
#pragma config FOSC = HS // Oscillator Selection bits (HSoscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit(Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits(Write protection off; all program memory may be written to by EECONcontrol)
#pragma config CP = OFF // Flash Program Memory Code Protection bit(Code protection off)
//LCD Functions Developed by Circuit Digest.
int main()
{
 unsigned int a;
 TRISD = 0x00;
 TRISE = 0x00;
 CMCON = 0b00000111;
 ADCON1 = 0x4E;
 Lcd_Start();
 while(1)
 {
 Lcd_Clear();
 Lcd_Set_Cursor(1,1);
 Lcd_Print_String("Circuit Digest");
 Lcd_Set_Cursor(2,4);
 //Lcd_Print_String("WORKING!!");
 Lcd_Print_Char(0b00111111);
 __delay_ms(2000);
 }
 return 0;
}