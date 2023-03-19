// PIC16F18344 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = XT     // FEXTOSC External Oscillator mode Selection bits (XT (crystal oscillator) from 100 kHz to 4 MHz)
#pragma config RSTOSC = EXT1X   // Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config WDTE = OFF       // Watchdog Timer Enable bits (WDT disabled; SWDTEN is ignored)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit (Brown-out voltage (Vbor) set to 2.45V)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a Reset)
#pragma config DEBUG = OFF      // Debugger enable bit (Background debugger disabled)

// CONFIG3
#pragma config WRT = OFF        // User NVM self-write protection bits (Write protection off)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (High Voltage on MCLR/VPP must be used for programming.)

// CONFIG4
#pragma config CP = OFF         // User NVM Program Memory Code Protection bit (User NVM code protection disabled)
#pragma config CPD = OFF        // Data NVM Memory Code Protection bit (Data NVM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define ACCELERATION_LIST_LENGTH 8
float ACCELERATION_MULTIPLER = 1/ACCELERATION_LIST_LENGTH;

//http://ww1.microchip.com/downloads/en/devicedoc/40001800c.pdf

struct race_info
{
    // 0, 1, 2 ,3 as it should stop on 3rd lap and start on first lap
    unsigned int    lap : 2;
};

struct road
{
    // 0 for straight, 1 for right turn, 2 for left turn
    unsigned int    direction : 2;

    // length of the road
    unsigned int    length : 30;
};

race_info current_info;
struct road roads[64];

uint8_t acceleration_front_x[ACCELERATION_LIST_LENGTH];
uint8_t acceleration_front_y[ACCELERATION_LIST_LENGTH];
uint8_t acceleration_back_x[ACCELERATION_LIST_LENGTH];
uint8_t acceleration_back_y[ACCELERATION_LIST_LENGTH];

uint8_t road_index = 0;
uint8_t wheel_turns = 0;

// no need for speed, as starting fast does not matter nor does ending fast
void interrupt tc_int(void) {
    // external interupt
    if(PIR0.INTF) {
        // clear flag
        PIR0.INTF = 0;

        // if 3rd loop stop car and run infinite loop
        if (current_info.lap == 3){
            while(1); // stop program
        }

        // update lap
        current_info.lap++;
    }
}

void setup(){
    //s99
    INTCON.GIE = 1; // enable global interupt
    INTCON.PEIE = 1; // enable peripheral interupt

    PIE0.INTE = 1;  //s100 enable external interupt
    
    //s160 select external interupt pin RC7
}

// 0 for straight, 1 for right turn, 2 for left turn
uint8_t direction(){
    
}

// brakes based on distance to next turn or speeds ip
uint16_t update_power(){
    // if need to brake

    // if need to speed up

    // if need to maintain speed
} 



void main(){
    setup();

    // wait for first lap to begin
    while (current_info.lap == 0);


    while (current_info.lap == 1) {
        // map
        uint8_t start_direction = direction();

        // length of road
        while(start_direction == direction());

        // add road to array
        struct road new_road = {start_direction, wheel_turns};
        roads[road_index] = new_road;
        wheel_turns = 0;
    }

    current_info.lap += 1;
    /*
    while (inf.lap == 2) {
        // adjust mapping
    }
    */

    while (current_info.lap == 3) {
        // run based on mapping
    }
}