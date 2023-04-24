# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\sources\\c90\\pic\\__eewrite.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\sources\\c90\\pic\\__eewrite.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 3
extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\xc8debug.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\xc8debug.h" 3
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);
# 23 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 2 3

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\builtins.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef signed char int8_t;






typedef signed int int16_t;







typedef __int24 int24_t;







typedef signed long int int32_t;
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint8_t;





typedef unsigned int uint16_t;






typedef __uint24 uint24_t;






typedef unsigned long int uint32_t;
# 88 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_least8_t;







typedef signed int int_least16_t;
# 109 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_least24_t;
# 118 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef signed long int int_least32_t;
# 136 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_least8_t;






typedef unsigned int uint_least16_t;
# 154 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_least24_t;







typedef unsigned long int uint_least32_t;
# 181 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_fast8_t;






typedef signed int int_fast16_t;
# 200 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_fast24_t;







typedef signed long int int_fast32_t;
# 224 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
# 240 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_fast24_t;






typedef unsigned long int uint_fast32_t;
# 268 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef int32_t intmax_t;
# 282 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\c90\\stdint.h" 3
typedef uint32_t uintmax_t;






typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\builtins.h" 2 3



#pragma intrinsic(__nop)
extern void __nop(void);


#pragma intrinsic(_delay)
extern __attribute__((nonreentrant)) void _delay(uint32_t);
#pragma intrinsic(_delaywdt)
extern __attribute__((nonreentrant)) void _delaywdt(uint32_t);
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 2 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 1 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\htc.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\htc.h" 2 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 2 3








# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic_chip_select.h" 1 3
# 2434 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic_chip_select.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 1 3
# 45 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\__at.h" 1 3
# 45 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 2 3








extern volatile unsigned char INDF __attribute__((address(0x000)));

__asm("INDF equ 00h");




extern volatile unsigned char TMR0 __attribute__((address(0x001)));

__asm("TMR0 equ 01h");




extern volatile unsigned char PCL __attribute__((address(0x002)));

__asm("PCL equ 02h");




extern volatile unsigned char STATUS __attribute__((address(0x003)));

__asm("STATUS equ 03h");


typedef union {
    struct {
        unsigned C :1;
        unsigned DC :1;
        unsigned Z :1;
        unsigned nPD :1;
        unsigned nTO :1;
        unsigned RP :2;
        unsigned IRP :1;
    };
    struct {
        unsigned :5;
        unsigned RP0 :1;
        unsigned RP1 :1;
    };
    struct {
        unsigned CARRY :1;
        unsigned :1;
        unsigned ZERO :1;
    };
} STATUSbits_t;
extern volatile STATUSbits_t STATUSbits __attribute__((address(0x003)));
# 160 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char FSR __attribute__((address(0x004)));

__asm("FSR equ 04h");




extern volatile unsigned char PORTA __attribute__((address(0x005)));

__asm("PORTA equ 05h");


typedef union {
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
    };
} PORTAbits_t;
extern volatile PORTAbits_t PORTAbits __attribute__((address(0x005)));
# 217 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PORTC __attribute__((address(0x007)));

__asm("PORTC equ 07h");


typedef union {
    struct {
        unsigned RC0 :1;
        unsigned RC1 :1;
        unsigned RC2 :1;
        unsigned RC3 :1;
        unsigned RC4 :1;
        unsigned RC5 :1;
    };
} PORTCbits_t;
extern volatile PORTCbits_t PORTCbits __attribute__((address(0x007)));
# 267 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PCLATH __attribute__((address(0x00A)));

__asm("PCLATH equ 0Ah");


typedef union {
    struct {
        unsigned PCLATH :5;
    };
} PCLATHbits_t;
extern volatile PCLATHbits_t PCLATHbits __attribute__((address(0x00A)));
# 287 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char INTCON __attribute__((address(0x00B)));

__asm("INTCON equ 0Bh");


typedef union {
    struct {
        unsigned RAIF :1;
        unsigned INTF :1;
        unsigned T0IF :1;
        unsigned RAIE :1;
        unsigned INTE :1;
        unsigned T0IE :1;
        unsigned PEIE :1;
        unsigned GIE :1;
    };
    struct {
        unsigned :2;
        unsigned TMR0IF :1;
        unsigned :2;
        unsigned TMR0IE :1;
    };
} INTCONbits_t;
extern volatile INTCONbits_t INTCONbits __attribute__((address(0x00B)));
# 365 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PIR1 __attribute__((address(0x00C)));

__asm("PIR1 equ 0Ch");


typedef union {
    struct {
        unsigned TMR1IF :1;
        unsigned TMR2IF :1;
        unsigned OSFIF :1;
        unsigned C1IF :1;
        unsigned C2IF :1;
        unsigned CCP1IF :1;
        unsigned ADIF :1;
        unsigned EEIF :1;
    };
    struct {
        unsigned T1IF :1;
        unsigned T2IF :1;
        unsigned :3;
        unsigned ECCPIF :1;
    };
} PIR1bits_t;
extern volatile PIR1bits_t PIR1bits __attribute__((address(0x00C)));
# 448 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned short TMR1 __attribute__((address(0x00E)));

__asm("TMR1 equ 0Eh");




extern volatile unsigned char TMR1L __attribute__((address(0x00E)));

__asm("TMR1L equ 0Eh");




extern volatile unsigned char TMR1H __attribute__((address(0x00F)));

__asm("TMR1H equ 0Fh");




extern volatile unsigned char T1CON __attribute__((address(0x010)));

__asm("T1CON equ 010h");


typedef union {
    struct {
        unsigned TMR1ON :1;
        unsigned TMR1CS :1;
        unsigned nT1SYNC :1;
        unsigned T1OSCEN :1;
        unsigned T1CKPS :2;
        unsigned TMR1GE :1;
        unsigned T1GINV :1;
    };
    struct {
        unsigned :4;
        unsigned T1CKPS0 :1;
        unsigned T1CKPS1 :1;
    };
} T1CONbits_t;
extern volatile T1CONbits_t T1CONbits __attribute__((address(0x010)));
# 540 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char TMR2 __attribute__((address(0x011)));

__asm("TMR2 equ 011h");




extern volatile unsigned char T2CON __attribute__((address(0x012)));

__asm("T2CON equ 012h");


typedef union {
    struct {
        unsigned T2CKPS :2;
        unsigned TMR2ON :1;
        unsigned TOUTPS :4;
    };
    struct {
        unsigned T2CKPS0 :1;
        unsigned T2CKPS1 :1;
        unsigned :1;
        unsigned TOUTPS0 :1;
        unsigned TOUTPS1 :1;
        unsigned TOUTPS2 :1;
        unsigned TOUTPS3 :1;
    };
} T2CONbits_t;
extern volatile T2CONbits_t T2CONbits __attribute__((address(0x012)));
# 618 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned short CCPR1 __attribute__((address(0x013)));

__asm("CCPR1 equ 013h");




extern volatile unsigned char CCPR1L __attribute__((address(0x013)));

__asm("CCPR1L equ 013h");




extern volatile unsigned char CCPR1H __attribute__((address(0x014)));

__asm("CCPR1H equ 014h");




extern volatile unsigned char CCP1CON __attribute__((address(0x015)));

__asm("CCP1CON equ 015h");


typedef union {
    struct {
        unsigned CCP1M :4;
        unsigned DCB :2;
        unsigned PM :2;
    };
    struct {
        unsigned CCP1M0 :1;
        unsigned CCP1M1 :1;
        unsigned CCP1M2 :1;
        unsigned CCP1M3 :1;
        unsigned DC1B0 :1;
        unsigned DC1B1 :1;
        unsigned P1M0 :1;
        unsigned P1M1 :1;
    };
} CCP1CONbits_t;
extern volatile CCP1CONbits_t CCP1CONbits __attribute__((address(0x015)));
# 721 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PWM1CON __attribute__((address(0x016)));

__asm("PWM1CON equ 016h");


typedef union {
    struct {
        unsigned PDC :7;
        unsigned PRSEN :1;
    };
    struct {
        unsigned PDC0 :1;
        unsigned PDC1 :1;
        unsigned PDC2 :1;
        unsigned PDC3 :1;
        unsigned PDC4 :1;
        unsigned PDC5 :1;
        unsigned PDC6 :1;
    };
} PWM1CONbits_t;
extern volatile PWM1CONbits_t PWM1CONbits __attribute__((address(0x016)));
# 791 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char ECCPAS __attribute__((address(0x017)));

__asm("ECCPAS equ 017h");


typedef union {
    struct {
        unsigned PSSBD :2;
        unsigned PSSAC :2;
        unsigned ECCPAS :3;
        unsigned ECCPASE :1;
    };
    struct {
        unsigned PSSBD0 :1;
        unsigned PSSBD1 :1;
        unsigned PSSAC0 :1;
        unsigned PSSAC1 :1;
        unsigned ECCPAS0 :1;
        unsigned ECCPAS1 :1;
        unsigned ECCPAS2 :1;
    };
} ECCPASbits_t;
extern volatile ECCPASbits_t ECCPASbits __attribute__((address(0x017)));
# 873 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char WDTCON __attribute__((address(0x018)));

__asm("WDTCON equ 018h");


typedef union {
    struct {
        unsigned SWDTEN :1;
        unsigned WDTPS :4;
    };
    struct {
        unsigned :1;
        unsigned WDTPS0 :1;
        unsigned WDTPS1 :1;
        unsigned WDTPS2 :1;
        unsigned WDTPS3 :1;
    };
} WDTCONbits_t;
extern volatile WDTCONbits_t WDTCONbits __attribute__((address(0x018)));
# 926 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char CMCON0 __attribute__((address(0x019)));

__asm("CMCON0 equ 019h");


typedef union {
    struct {
        unsigned CM :3;
        unsigned CIS :1;
        unsigned C1INV :1;
        unsigned C2INV :1;
        unsigned C1OUT :1;
        unsigned C2OUT :1;
    };
    struct {
        unsigned CM0 :1;
        unsigned CM1 :1;
        unsigned CM2 :1;
    };
} CMCON0bits_t;
extern volatile CMCON0bits_t CMCON0bits __attribute__((address(0x019)));
# 996 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char CMCON1 __attribute__((address(0x01A)));

__asm("CMCON1 equ 01Ah");


typedef union {
    struct {
        unsigned C2SYNC :1;
        unsigned T1GSS :1;
    };
} CMCON1bits_t;
extern volatile CMCON1bits_t CMCON1bits __attribute__((address(0x01A)));
# 1022 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char ADRESH __attribute__((address(0x01E)));

__asm("ADRESH equ 01Eh");




extern volatile unsigned char ADCON0 __attribute__((address(0x01F)));

__asm("ADCON0 equ 01Fh");


typedef union {
    struct {
        unsigned ADON :1;
        unsigned GO_nDONE :1;
        unsigned CHS :3;
        unsigned :1;
        unsigned VCFG :1;
        unsigned ADFM :1;
    };
    struct {
        unsigned :1;
        unsigned GO :1;
        unsigned CHS0 :1;
        unsigned CHS1 :1;
        unsigned CHS2 :1;
    };
    struct {
        unsigned :1;
        unsigned nDONE :1;
    };
    struct {
        unsigned :1;
        unsigned GO_DONE :1;
    };
} ADCON0bits_t;
extern volatile ADCON0bits_t ADCON0bits __attribute__((address(0x01F)));
# 1119 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char OPTION_REG __attribute__((address(0x081)));

__asm("OPTION_REG equ 081h");


typedef union {
    struct {
        unsigned PS :3;
        unsigned PSA :1;
        unsigned T0SE :1;
        unsigned T0CS :1;
        unsigned INTEDG :1;
        unsigned nRAPU :1;
    };
    struct {
        unsigned PS0 :1;
        unsigned PS1 :1;
        unsigned PS2 :1;
    };
} OPTION_REGbits_t;
extern volatile OPTION_REGbits_t OPTION_REGbits __attribute__((address(0x081)));
# 1189 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char TRISA __attribute__((address(0x085)));

__asm("TRISA equ 085h");


typedef union {
    struct {
        unsigned TRISA0 :1;
        unsigned TRISA1 :1;
        unsigned TRISA2 :1;
        unsigned TRISA3 :1;
        unsigned TRISA4 :1;
        unsigned TRISA5 :1;
    };
} TRISAbits_t;
extern volatile TRISAbits_t TRISAbits __attribute__((address(0x085)));
# 1239 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char TRISC __attribute__((address(0x087)));

__asm("TRISC equ 087h");


typedef union {
    struct {
        unsigned TRISC0 :1;
        unsigned TRISC1 :1;
        unsigned TRISC2 :1;
        unsigned TRISC3 :1;
        unsigned TRISC4 :1;
        unsigned TRISC5 :1;
    };
} TRISCbits_t;
extern volatile TRISCbits_t TRISCbits __attribute__((address(0x087)));
# 1289 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PIE1 __attribute__((address(0x08C)));

__asm("PIE1 equ 08Ch");


typedef union {
    struct {
        unsigned TMR1IE :1;
        unsigned TMR2IE :1;
        unsigned OSFIE :1;
        unsigned C1IE :1;
        unsigned C2IE :1;
        unsigned CCP1IE :1;
        unsigned ADIE :1;
        unsigned EEIE :1;
    };
    struct {
        unsigned T1IE :1;
        unsigned T2IE :1;
        unsigned :3;
        unsigned ECCPIE :1;
    };
} PIE1bits_t;
extern volatile PIE1bits_t PIE1bits __attribute__((address(0x08C)));
# 1372 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PCON __attribute__((address(0x08E)));

__asm("PCON equ 08Eh");


typedef union {
    struct {
        unsigned nBOR :1;
        unsigned nPOR :1;
        unsigned :2;
        unsigned SBOREN :1;
        unsigned ULPWUE :1;
    };
    struct {
        unsigned nBOD :1;
        unsigned :3;
        unsigned SBODEN :1;
    };
} PCONbits_t;
extern volatile PCONbits_t PCONbits __attribute__((address(0x08E)));
# 1426 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char OSCCON __attribute__((address(0x08F)));

__asm("OSCCON equ 08Fh");


typedef union {
    struct {
        unsigned SCS :1;
        unsigned LTS :1;
        unsigned HTS :1;
        unsigned OSTS :1;
        unsigned IOSCF :3;
    };
    struct {
        unsigned :4;
        unsigned IRCF0 :1;
        unsigned IRCF1 :1;
        unsigned IRCF2 :1;
    };
} OSCCONbits_t;
extern volatile OSCCONbits_t OSCCONbits __attribute__((address(0x08F)));
# 1491 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char OSCTUNE __attribute__((address(0x090)));

__asm("OSCTUNE equ 090h");


typedef union {
    struct {
        unsigned TUN :5;
    };
    struct {
        unsigned TUN0 :1;
        unsigned TUN1 :1;
        unsigned TUN2 :1;
        unsigned TUN3 :1;
        unsigned TUN4 :1;
    };
} OSCTUNEbits_t;
extern volatile OSCTUNEbits_t OSCTUNEbits __attribute__((address(0x090)));
# 1543 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char ANSEL __attribute__((address(0x091)));

__asm("ANSEL equ 091h");


typedef union {
    struct {
        unsigned ANS0 :1;
        unsigned ANS1 :1;
        unsigned ANS2 :1;
        unsigned ANS3 :1;
        unsigned ANS4 :1;
        unsigned ANS5 :1;
        unsigned ANS6 :1;
        unsigned ANS7 :1;
    };
} ANSELbits_t;
extern volatile ANSELbits_t ANSELbits __attribute__((address(0x091)));
# 1605 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char PR2 __attribute__((address(0x092)));

__asm("PR2 equ 092h");




extern volatile unsigned char WPUA __attribute__((address(0x095)));

__asm("WPUA equ 095h");


extern volatile unsigned char WPU __attribute__((address(0x095)));

__asm("WPU equ 095h");


typedef union {
    struct {
        unsigned WPUA0 :1;
        unsigned WPUA1 :1;
        unsigned WPUA2 :1;
        unsigned :1;
        unsigned WPUA4 :1;
        unsigned WPUA5 :1;
    };
    struct {
        unsigned WPU0 :1;
        unsigned WPU1 :1;
        unsigned WPU2 :1;
        unsigned :1;
        unsigned WPU4 :1;
        unsigned WPU5 :1;
    };
} WPUAbits_t;
extern volatile WPUAbits_t WPUAbits __attribute__((address(0x095)));
# 1693 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
typedef union {
    struct {
        unsigned WPUA0 :1;
        unsigned WPUA1 :1;
        unsigned WPUA2 :1;
        unsigned :1;
        unsigned WPUA4 :1;
        unsigned WPUA5 :1;
    };
    struct {
        unsigned WPU0 :1;
        unsigned WPU1 :1;
        unsigned WPU2 :1;
        unsigned :1;
        unsigned WPU4 :1;
        unsigned WPU5 :1;
    };
} WPUbits_t;
extern volatile WPUbits_t WPUbits __attribute__((address(0x095)));
# 1766 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char IOCA __attribute__((address(0x096)));

__asm("IOCA equ 096h");


extern volatile unsigned char IOC __attribute__((address(0x096)));

__asm("IOC equ 096h");


typedef union {
    struct {
        unsigned IOCA0 :1;
        unsigned IOCA1 :1;
        unsigned IOCA2 :1;
        unsigned IOCA3 :1;
        unsigned IOCA4 :1;
        unsigned IOCA5 :1;
    };
    struct {
        unsigned IOC0 :1;
        unsigned IOC1 :1;
        unsigned IOC2 :1;
        unsigned IOC3 :1;
        unsigned IOC4 :1;
        unsigned IOC5 :1;
    };
} IOCAbits_t;
extern volatile IOCAbits_t IOCAbits __attribute__((address(0x096)));
# 1857 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
typedef union {
    struct {
        unsigned IOCA0 :1;
        unsigned IOCA1 :1;
        unsigned IOCA2 :1;
        unsigned IOCA3 :1;
        unsigned IOCA4 :1;
        unsigned IOCA5 :1;
    };
    struct {
        unsigned IOC0 :1;
        unsigned IOC1 :1;
        unsigned IOC2 :1;
        unsigned IOC3 :1;
        unsigned IOC4 :1;
        unsigned IOC5 :1;
    };
} IOCbits_t;
extern volatile IOCbits_t IOCbits __attribute__((address(0x096)));
# 1940 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char VRCON __attribute__((address(0x099)));

__asm("VRCON equ 099h");


typedef union {
    struct {
        unsigned VR :4;
        unsigned :1;
        unsigned VRR :1;
        unsigned :1;
        unsigned VREN :1;
    };
    struct {
        unsigned VR0 :1;
        unsigned VR1 :1;
        unsigned VR2 :1;
        unsigned VR3 :1;
    };
} VRCONbits_t;
extern volatile VRCONbits_t VRCONbits __attribute__((address(0x099)));
# 2000 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char EEDAT __attribute__((address(0x09A)));

__asm("EEDAT equ 09Ah");


extern volatile unsigned char EEDATA __attribute__((address(0x09A)));

__asm("EEDATA equ 09Ah");


typedef union {
    struct {
        unsigned EEDAT :8;
    };
} EEDATbits_t;
extern volatile EEDATbits_t EEDATbits __attribute__((address(0x09A)));







typedef union {
    struct {
        unsigned EEDAT :8;
    };
} EEDATAbits_t;
extern volatile EEDATAbits_t EEDATAbits __attribute__((address(0x09A)));
# 2038 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char EEADR __attribute__((address(0x09B)));

__asm("EEADR equ 09Bh");




extern volatile unsigned char EECON1 __attribute__((address(0x09C)));

__asm("EECON1 equ 09Ch");


typedef union {
    struct {
        unsigned RD :1;
        unsigned WR :1;
        unsigned WREN :1;
        unsigned WRERR :1;
    };
} EECON1bits_t;
extern volatile EECON1bits_t EECON1bits __attribute__((address(0x09C)));
# 2083 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile unsigned char EECON2 __attribute__((address(0x09D)));

__asm("EECON2 equ 09Dh");




extern volatile unsigned char ADRESL __attribute__((address(0x09E)));

__asm("ADRESL equ 09Eh");




extern volatile unsigned char ADCON1 __attribute__((address(0x09F)));

__asm("ADCON1 equ 09Fh");


typedef union {
    struct {
        unsigned :4;
        unsigned ADCS :3;
    };
    struct {
        unsigned :4;
        unsigned ADCS0 :1;
        unsigned ADCS1 :1;
        unsigned ADCS2 :1;
    };
} ADCON1bits_t;
extern volatile ADCON1bits_t ADCON1bits __attribute__((address(0x09F)));
# 2149 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\proc\\pic16f684.h" 3
extern volatile __bit ADCS0 __attribute__((address(0x4FC)));


extern volatile __bit ADCS1 __attribute__((address(0x4FD)));


extern volatile __bit ADCS2 __attribute__((address(0x4FE)));


extern volatile __bit ADFM __attribute__((address(0xFF)));


extern volatile __bit ADIE __attribute__((address(0x466)));


extern volatile __bit ADIF __attribute__((address(0x66)));


extern volatile __bit ADON __attribute__((address(0xF8)));


extern volatile __bit ANS0 __attribute__((address(0x488)));


extern volatile __bit ANS1 __attribute__((address(0x489)));


extern volatile __bit ANS2 __attribute__((address(0x48A)));


extern volatile __bit ANS3 __attribute__((address(0x48B)));


extern volatile __bit ANS4 __attribute__((address(0x48C)));


extern volatile __bit ANS5 __attribute__((address(0x48D)));


extern volatile __bit ANS6 __attribute__((address(0x48E)));


extern volatile __bit ANS7 __attribute__((address(0x48F)));


extern volatile __bit C1IE __attribute__((address(0x463)));


extern volatile __bit C1IF __attribute__((address(0x63)));


extern volatile __bit C1INV __attribute__((address(0xCC)));


extern volatile __bit C1OUT __attribute__((address(0xCE)));


extern volatile __bit C2IE __attribute__((address(0x464)));


extern volatile __bit C2IF __attribute__((address(0x64)));


extern volatile __bit C2INV __attribute__((address(0xCD)));


extern volatile __bit C2OUT __attribute__((address(0xCF)));


extern volatile __bit C2SYNC __attribute__((address(0xD0)));


extern volatile __bit CARRY __attribute__((address(0x18)));


extern volatile __bit CCP1IE __attribute__((address(0x465)));


extern volatile __bit CCP1IF __attribute__((address(0x65)));


extern volatile __bit CCP1M0 __attribute__((address(0xA8)));


extern volatile __bit CCP1M1 __attribute__((address(0xA9)));


extern volatile __bit CCP1M2 __attribute__((address(0xAA)));


extern volatile __bit CCP1M3 __attribute__((address(0xAB)));


extern volatile __bit CHS0 __attribute__((address(0xFA)));


extern volatile __bit CHS1 __attribute__((address(0xFB)));


extern volatile __bit CHS2 __attribute__((address(0xFC)));


extern volatile __bit CIS __attribute__((address(0xCB)));


extern volatile __bit CM0 __attribute__((address(0xC8)));


extern volatile __bit CM1 __attribute__((address(0xC9)));


extern volatile __bit CM2 __attribute__((address(0xCA)));


extern volatile __bit DC __attribute__((address(0x19)));


extern volatile __bit DC1B0 __attribute__((address(0xAC)));


extern volatile __bit DC1B1 __attribute__((address(0xAD)));


extern volatile __bit ECCPAS0 __attribute__((address(0xBC)));


extern volatile __bit ECCPAS1 __attribute__((address(0xBD)));


extern volatile __bit ECCPAS2 __attribute__((address(0xBE)));


extern volatile __bit ECCPASE __attribute__((address(0xBF)));


extern volatile __bit ECCPIE __attribute__((address(0x465)));


extern volatile __bit ECCPIF __attribute__((address(0x65)));


extern volatile __bit EEIE __attribute__((address(0x467)));


extern volatile __bit EEIF __attribute__((address(0x67)));


extern volatile __bit GIE __attribute__((address(0x5F)));


extern volatile __bit GO __attribute__((address(0xF9)));


extern volatile __bit GO_DONE __attribute__((address(0xF9)));


extern volatile __bit GO_nDONE __attribute__((address(0xF9)));


extern volatile __bit HTS __attribute__((address(0x47A)));


extern volatile __bit INTE __attribute__((address(0x5C)));


extern volatile __bit INTEDG __attribute__((address(0x40E)));


extern volatile __bit INTF __attribute__((address(0x59)));


extern volatile __bit IOC0 __attribute__((address(0x4B0)));


extern volatile __bit IOC1 __attribute__((address(0x4B1)));


extern volatile __bit IOC2 __attribute__((address(0x4B2)));


extern volatile __bit IOC3 __attribute__((address(0x4B3)));


extern volatile __bit IOC4 __attribute__((address(0x4B4)));


extern volatile __bit IOC5 __attribute__((address(0x4B5)));


extern volatile __bit IOCA0 __attribute__((address(0x4B0)));


extern volatile __bit IOCA1 __attribute__((address(0x4B1)));


extern volatile __bit IOCA2 __attribute__((address(0x4B2)));


extern volatile __bit IOCA3 __attribute__((address(0x4B3)));


extern volatile __bit IOCA4 __attribute__((address(0x4B4)));


extern volatile __bit IOCA5 __attribute__((address(0x4B5)));


extern volatile __bit IRCF0 __attribute__((address(0x47C)));


extern volatile __bit IRCF1 __attribute__((address(0x47D)));


extern volatile __bit IRCF2 __attribute__((address(0x47E)));


extern volatile __bit IRP __attribute__((address(0x1F)));


extern volatile __bit LTS __attribute__((address(0x479)));


extern volatile __bit OSFIE __attribute__((address(0x462)));


extern volatile __bit OSFIF __attribute__((address(0x62)));


extern volatile __bit OSTS __attribute__((address(0x47B)));


extern volatile __bit P1M0 __attribute__((address(0xAE)));


extern volatile __bit P1M1 __attribute__((address(0xAF)));


extern volatile __bit PDC0 __attribute__((address(0xB0)));


extern volatile __bit PDC1 __attribute__((address(0xB1)));


extern volatile __bit PDC2 __attribute__((address(0xB2)));


extern volatile __bit PDC3 __attribute__((address(0xB3)));


extern volatile __bit PDC4 __attribute__((address(0xB4)));


extern volatile __bit PDC5 __attribute__((address(0xB5)));


extern volatile __bit PDC6 __attribute__((address(0xB6)));


extern volatile __bit PEIE __attribute__((address(0x5E)));


extern volatile __bit PRSEN __attribute__((address(0xB7)));


extern volatile __bit PS0 __attribute__((address(0x408)));


extern volatile __bit PS1 __attribute__((address(0x409)));


extern volatile __bit PS2 __attribute__((address(0x40A)));


extern volatile __bit PSA __attribute__((address(0x40B)));


extern volatile __bit PSSAC0 __attribute__((address(0xBA)));


extern volatile __bit PSSAC1 __attribute__((address(0xBB)));


extern volatile __bit PSSBD0 __attribute__((address(0xB8)));


extern volatile __bit PSSBD1 __attribute__((address(0xB9)));


extern volatile __bit RA0 __attribute__((address(0x28)));


extern volatile __bit RA1 __attribute__((address(0x29)));


extern volatile __bit RA2 __attribute__((address(0x2A)));


extern volatile __bit RA3 __attribute__((address(0x2B)));


extern volatile __bit RA4 __attribute__((address(0x2C)));


extern volatile __bit RA5 __attribute__((address(0x2D)));


extern volatile __bit RAIE __attribute__((address(0x5B)));


extern volatile __bit RAIF __attribute__((address(0x58)));


extern volatile __bit RC0 __attribute__((address(0x38)));


extern volatile __bit RC1 __attribute__((address(0x39)));


extern volatile __bit RC2 __attribute__((address(0x3A)));


extern volatile __bit RC3 __attribute__((address(0x3B)));


extern volatile __bit RC4 __attribute__((address(0x3C)));


extern volatile __bit RC5 __attribute__((address(0x3D)));


extern volatile __bit RD __attribute__((address(0x4E0)));


extern volatile __bit RP0 __attribute__((address(0x1D)));


extern volatile __bit RP1 __attribute__((address(0x1E)));


extern volatile __bit SBODEN __attribute__((address(0x474)));


extern volatile __bit SBOREN __attribute__((address(0x474)));


extern volatile __bit SCS __attribute__((address(0x478)));


extern volatile __bit SWDTEN __attribute__((address(0xC0)));


extern volatile __bit T0CS __attribute__((address(0x40D)));


extern volatile __bit T0IE __attribute__((address(0x5D)));


extern volatile __bit T0IF __attribute__((address(0x5A)));


extern volatile __bit T0SE __attribute__((address(0x40C)));


extern volatile __bit T1CKPS0 __attribute__((address(0x84)));


extern volatile __bit T1CKPS1 __attribute__((address(0x85)));


extern volatile __bit T1GINV __attribute__((address(0x87)));


extern volatile __bit T1GSS __attribute__((address(0xD1)));


extern volatile __bit T1IE __attribute__((address(0x460)));


extern volatile __bit T1IF __attribute__((address(0x60)));


extern volatile __bit T1OSCEN __attribute__((address(0x83)));


extern volatile __bit T2CKPS0 __attribute__((address(0x90)));


extern volatile __bit T2CKPS1 __attribute__((address(0x91)));


extern volatile __bit T2IE __attribute__((address(0x461)));


extern volatile __bit T2IF __attribute__((address(0x61)));


extern volatile __bit TMR0IE __attribute__((address(0x5D)));


extern volatile __bit TMR0IF __attribute__((address(0x5A)));


extern volatile __bit TMR1CS __attribute__((address(0x81)));


extern volatile __bit TMR1GE __attribute__((address(0x86)));


extern volatile __bit TMR1IE __attribute__((address(0x460)));


extern volatile __bit TMR1IF __attribute__((address(0x60)));


extern volatile __bit TMR1ON __attribute__((address(0x80)));


extern volatile __bit TMR2IE __attribute__((address(0x461)));


extern volatile __bit TMR2IF __attribute__((address(0x61)));


extern volatile __bit TMR2ON __attribute__((address(0x92)));


extern volatile __bit TOUTPS0 __attribute__((address(0x93)));


extern volatile __bit TOUTPS1 __attribute__((address(0x94)));


extern volatile __bit TOUTPS2 __attribute__((address(0x95)));


extern volatile __bit TOUTPS3 __attribute__((address(0x96)));


extern volatile __bit TRISA0 __attribute__((address(0x428)));


extern volatile __bit TRISA1 __attribute__((address(0x429)));


extern volatile __bit TRISA2 __attribute__((address(0x42A)));


extern volatile __bit TRISA3 __attribute__((address(0x42B)));


extern volatile __bit TRISA4 __attribute__((address(0x42C)));


extern volatile __bit TRISA5 __attribute__((address(0x42D)));


extern volatile __bit TRISC0 __attribute__((address(0x438)));


extern volatile __bit TRISC1 __attribute__((address(0x439)));


extern volatile __bit TRISC2 __attribute__((address(0x43A)));


extern volatile __bit TRISC3 __attribute__((address(0x43B)));


extern volatile __bit TRISC4 __attribute__((address(0x43C)));


extern volatile __bit TRISC5 __attribute__((address(0x43D)));


extern volatile __bit TUN0 __attribute__((address(0x480)));


extern volatile __bit TUN1 __attribute__((address(0x481)));


extern volatile __bit TUN2 __attribute__((address(0x482)));


extern volatile __bit TUN3 __attribute__((address(0x483)));


extern volatile __bit TUN4 __attribute__((address(0x484)));


extern volatile __bit ULPWUE __attribute__((address(0x475)));


extern volatile __bit VCFG __attribute__((address(0xFE)));


extern volatile __bit VR0 __attribute__((address(0x4C8)));


extern volatile __bit VR1 __attribute__((address(0x4C9)));


extern volatile __bit VR2 __attribute__((address(0x4CA)));


extern volatile __bit VR3 __attribute__((address(0x4CB)));


extern volatile __bit VREN __attribute__((address(0x4CF)));


extern volatile __bit VRR __attribute__((address(0x4CD)));


extern volatile __bit WDTPS0 __attribute__((address(0xC1)));


extern volatile __bit WDTPS1 __attribute__((address(0xC2)));


extern volatile __bit WDTPS2 __attribute__((address(0xC3)));


extern volatile __bit WDTPS3 __attribute__((address(0xC4)));


extern volatile __bit WPU0 __attribute__((address(0x4A8)));


extern volatile __bit WPU1 __attribute__((address(0x4A9)));


extern volatile __bit WPU2 __attribute__((address(0x4AA)));


extern volatile __bit WPU4 __attribute__((address(0x4AC)));


extern volatile __bit WPU5 __attribute__((address(0x4AD)));


extern volatile __bit WPUA0 __attribute__((address(0x4A8)));


extern volatile __bit WPUA1 __attribute__((address(0x4A9)));


extern volatile __bit WPUA2 __attribute__((address(0x4AA)));


extern volatile __bit WPUA4 __attribute__((address(0x4AC)));


extern volatile __bit WPUA5 __attribute__((address(0x4AD)));


extern volatile __bit WR __attribute__((address(0x4E1)));


extern volatile __bit WREN __attribute__((address(0x4E2)));


extern volatile __bit WRERR __attribute__((address(0x4E3)));


extern volatile __bit ZERO __attribute__((address(0x1A)));


extern volatile __bit nBOD __attribute__((address(0x470)));


extern volatile __bit nBOR __attribute__((address(0x470)));


extern volatile __bit nDONE __attribute__((address(0xF9)));


extern volatile __bit nPD __attribute__((address(0x1B)));


extern volatile __bit nPOR __attribute__((address(0x471)));


extern volatile __bit nRAPU __attribute__((address(0x40F)));


extern volatile __bit nT1SYNC __attribute__((address(0x82)));


extern volatile __bit nTO __attribute__((address(0x1C)));
# 2434 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic_chip_select.h" 2 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 2 3
# 76 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 3
__attribute__((__unsupported__("The " "FLASH_READ" " macro function is no longer supported. Please use the MPLAB X MCC."))) unsigned char __flash_read(unsigned short addr);

__attribute__((__unsupported__("The " "FLASH_WRITE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_write(unsigned short addr, unsigned short data);

__attribute__((__unsupported__("The " "FLASH_ERASE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_erase(unsigned short addr);



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\eeprom_routines.h" 1 3
# 114 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\eeprom_routines.h" 3
extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);
# 83 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 2 3
# 118 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\pic.h" 3
extern __bank0 unsigned char __resetbits;
extern __bank0 __bit __powerdown;
extern __bank0 __bit __timeout;
# 28 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\include\\xc.h" 2 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.40\\pic\\sources\\c90\\pic\\__eewrite.c" 2




void
eeprom_write(unsigned char addr, unsigned char value)
{
 do{ while (EECON1bits.WR) { continue; } EEADR = (addr); EEDATA = (value); EECON1 &= 0x3F; STATUSbits.CARRY = 0; if (INTCONbits.GIE) { STATUSbits.CARRY = 1; } INTCONbits.GIE = 0; EECON1bits.WREN = 1; EECON2 = 0x55; EECON2 = 0xAA; EECON1bits.WR = 1; EECON1bits.WREN = 0; if (STATUSbits.CARRY) { INTCONbits.GIE = 1; } } while (0);
}
