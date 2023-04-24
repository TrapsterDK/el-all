#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config PWRTE = ON 

#include <xc.h>
#define _XTAL_FREQ 4000000UL

void ADC_Init()
{
   ADCON0 = 0b00001001;           // sampling freq=osc_freq/2,ADC er ON, AN0 er valgt 
}


uint8_t ADC_Read()
 {  
    GO_DONE = 1;                // Start ADC
    while(GO_DONE == 1);        // Vent til ADC er færdig    
    return(ADRESH);             // returnér resultatet
 }

    
void main(void) {
    ANSEL = 0; // set ports as IO
    ADCON0 = 0; //shutdown ad converter
    CMCON = 0x07; // turn off comparator
    VRCON = 0; // turn off voltage reference
    
    TRISIO = 0b00000100;
    ADC_Init();

    __delay_ms(10);

    uint8_t avg = 0;
    
    // read 2 seconds
    for (int i = 0; i<400; i++){
        uint8_t read = ADC_Read();
        if (read > avg) {
            avg++;
        }else{
            avg--;
        }
        __delay_ms(5);
    }
    
    avg+=2;
    
    while(1){
        if(ADC_Read()> avg){
            GP4 = 1;
        }
        else{
            GP4 = 0;
        }
        __delay_ms(100);
        
    }
        
}
