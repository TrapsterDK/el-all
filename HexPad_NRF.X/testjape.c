#define _XTAL_FREQ 4000000


#pragma config FOSC = INTOSCIO	        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config MCLRE = ON
#pragma config FCMEN  = OFF
#pragma config CPD = OFF 
#pragma config IESO  = OFF


#include<xc.h>




        

#define X4 RC0
#define X3 RC1
#define X2 RC2
#define X1 RA4
#define Y1 RA2
#define Y2 RA1
#define Y3 RA0



void main()
{
    ANSEL = 0;
    TRISC = 0b00000000;
    TRISA = 0b0001000;
    
    
    
    while(1){
        
        /*for(int ypos=0; ypos < 4; ypos++){
            switch(ypos){
                case 0:
                    RC0 = 1;
                    break;
                case 1:
                    RC1 = 1;
                    break;
                case 2:
                    RC2 = 1;
                    break;
                case 3:
                    RA3 = 1;
                    break;
            }*/
        Y1 = 0;
        
        if (X2){
            RC3 = 1;
            RC4 = 1;
            RC5 = 1;
            RA5 = 1;
        }
        
        
            /*
            break;
            
            
            
            if (RA0 || RA1 || RA2){
                xpos = RA0 * 3;
                xpos += RA1 * 2;
                xpos += RA2 * 1;
                
                int newpos = ypos * 3 + xpos - 1;
                int number = hexkeys[newpos];

                RC3 = BIT_X(number,0);
                RC4 = BIT_X(number,1);
                RC5 = BIT_X(number,2);
                RA5 = BIT_X(number,3);
            }
            else{
                RC3 = 0;
                RC4 = 0;
                RC5 = 0;
                RA5 = 0;
            }
            
            switch(ypos){
                case 0:
                    RC0 = 0;
                    break;
                case 1:
                    RC1 = 0;
                    break;
                case 2:
                    RC2 = 0;
                    break;
                case 3:
                    RC3 = 0;
                    break;
            }*/
        //}
    }
}

