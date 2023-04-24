#pragma config FOSC = INTOSCIO // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF      // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF     // Brown-out Reset Enable bit (BOR enabled)
#pragma config CPD = OFF       // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config CP = OFF        // Flash Program Memory Code Protection bit (Code protection off)
#pragma config MCLRE = OFF
#pragma config FCMEN = OFF
#pragma config CPD = OFF
#pragma config IESO = OFF

#include <xc.h>
#define _XTAL_FREQ 4000000UL

#define Y1 C2
#define Y2 C1
#define Y3 C0
#define Y4 A2

#define X1 A1
#define X2 A0
#define X3 A3

// work around for X ## Y which would normally be concatenated before expansion
#define UNWRAP_CONCAT(X, Y) X##Y

// macro to get the pin and tris register for a given pin
#define PIN(X) UNWRAP_CONCAT(R, X)
#define TRIS(X) UNWRAP_CONCAT(TRIS, X)

#define PASSWORD_SIZE 4
#define PASWORD_ADR 0

#define BIT_X(byte, x) ((byte >> x) & 1)

uint8_t hexkeys[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9,
    10, 0, 11};

uint8_t password[PASSWORD_SIZE];

void arrcpy(uint8_t *dest, uint8_t *src, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

uint8_t arrequal(uint8_t *arr1, uint8_t *arr2, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }

    return 1;
}

void eeprom_write_arr(uint8_t adr, uint8_t *arr, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        eeprom_write(adr + i, arr[i]);
    }
}

void eeprom_read_arr(uint8_t adr, uint8_t *arr, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        arr[i] = eeprom_read(adr + i);
    }
}

void press()
{
    PR2 = 0b10000000;
    T2CON = 0b00000111;
    __delay_ms(200);
    T2CON = 0b00000000;
}

void clear()
{
    PR2 = 0b11111111;
    T2CON = 0b00000100;
    __delay_ms(50);
    T2CON = 0b00000000;
    __delay_ms(50);
    T2CON = 0b00000100;
    __delay_ms(50);
    T2CON = 0b00000000;
    __delay_ms(50);
    T2CON = 0b00000100;
    __delay_ms(50);
    T2CON = 0b00000000;
}

void set_password_sound()
{
    // TODO PROPER SOUND
    PR2 = 0b11110011;
    T2CON = 0b00000110;
    __delay_ms(100);
    T2CON = 0b00000000;
    __delay_ms(50);
    T2CON = 0b00000110;
    __delay_ms(100);
    T2CON = 0b00000000;
}

void success()
{
    PR2 = 0b11110000;
    T2CON = 0b00000100;
    __delay_ms(100);
    T2CON = 0b00000000;
    __delay_ms(50);
    T2CON = 0b00000100;
    __delay_ms(100);
    T2CON = 0b00000000;
}

void wrong()
{
    PR2 = 0b11111111;
    T2CON = 0b00000111;
    __delay_ms(400);
    T2CON = 0b00000000;
}

void reset()
{
    PR2 = 0b11111111;
    T2CON = 0b00000101;
    __delay_ms(50);
    T2CON = 0b00000000;
    __delay_ms(50);
    T2CON = 0b00000101;
    __delay_ms(200);
    T2CON = 0b00000000;
}

uint8_t get_key()
{
    while (1)
    {
        for (uint8_t ypos = 0; ypos < 4; ypos++)
        {
            PIN(Y1) = 0;
            PIN(Y2) = 0;
            PIN(Y3) = 0;
            PIN(Y4) = 0;

            switch (ypos)
            {
            case 0:
                PIN(Y1) = 1;
                break;
            case 1:
                PIN(Y2) = 1;
                break;
            case 2:
                PIN(Y3) = 1;
                break;
            case 3:
                PIN(Y4) = 1;
                break;
            }

            uint8_t x1 = PIN(X1);
            uint8_t x2 = PIN(X2);
            uint8_t x3 = PIN(X3);
            if (x1 || x2 || x3)
            {
                uint8_t xpos = x1 * 1 + x2 * 2 + x3 * 3;
                uint8_t newpos = ypos * 3 + xpos - 1;
                uint8_t number = hexkeys[newpos];

                switch (number)
                {
                case 11:
                    clear();
                    break;
                case 10:
                    reset();
                    break;
                default:
                    press();
                    break;
                }

                uint8_t checkpos = x1 + x2 * 2 + x3 * 4;
                while (1)
                {
                    uint8_t tpos = PIN(X1) * 1 + PIN(X2) * 2 + PIN(X3) * 4;
                    if (tpos != checkpos &&
                        (tpos == 0 || tpos == 1 || tpos == 2 || tpos == 4))
                        break;
                }

                return number;
            }
        }
    }
}

void set_password()
{
    uint8_t digit = 0;
    uint8_t old_password[PASSWORD_SIZE];
    arrcpy(old_password, password, PASSWORD_SIZE);

    while (1)
    {
        uint8_t key = get_key();
        switch (key)
        {
        case 11:
            digit = 0;
            break;
        case 10:
            arrcpy(password, old_password, PASSWORD_SIZE);
            wrong();
            return;
        default:
            password[digit++] = key;
            if (digit >= PASSWORD_SIZE)
            {
                eeprom_write_arr(PASWORD_ADR, password, PASSWORD_SIZE);
                success();
                return;
            }
            break;
        }
    }
}

uint8_t check_password()
{
    uint8_t digit = 0;
    uint8_t current_password[PASSWORD_SIZE];

    while (1)
    {
        uint8_t key = get_key();
        switch (key)
        {
        case 11:
            digit = 0;
            break;
        case 10:
            return 2;
        default:
            current_password[digit++] = key;
            if (digit >= PASSWORD_SIZE)
            {
                if (arrequal(current_password, password, PASSWORD_SIZE))
                {
                    success();
                    return 1;
                }

                wrong();
                return 0;
            }
            break;
        }
    }
}

// set password max 8 bytes to 0 when programming
__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

void main()
{
    ANSEL = 0;
    
    TRISC = 0;
    TRISA = 0;
    
    TRIS(X1) = 1;
    TRIS(X2) = 1;
    TRIS(X3) = 1;

    TRIS(Y1) = 0;
    TRIS(Y2) = 0;
    TRIS(Y3) = 0;
    TRIS(Y4) = 0;

    CMCON0bits.CM = 111;
    CCP1CON = 0b00001100;
    CCPR1L = 0b10000000;
    PIE1bits.TMR2IE = 1;
    
    eeprom_read_arr(PASWORD_ADR, password, PASSWORD_SIZE);

    while (1)
    {
        switch (check_password())
        {
        case 0:
            break;

        case 1:
            break;

        case 2:
            if (check_password() == 1)
            {
                set_password_sound();
                set_password();
            }
        }
    }
}
