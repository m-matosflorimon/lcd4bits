//;************************************
//; written by: theWig
//; date: <2019|01|22>
//; version: 1.0
//; file saved as: lcd.c
//; for AVR: atmega328p
//; clock frequency: 16MHz (optional)
//;************************************
//
//; Program funcion:---------------------
//;--------------------------------------


// Instructions

// Function Set instructions
// 4-bit data bus, 2 line, 5x7 font
#define fSet8 0b0011
#define fSet4 0b0010
#define fSetLine 0b1000

// Entry mode
// Inc address, no scroll
#define eModeSet1 0b0000
#define eModeSet2 0b0110

// Display control
// Cursor on, display on, blink on
#define dON 0b0000
#define dBlink 0b1111

// Clear display instruction
#define dClear1 0b0000
#define dClear2 0b0001


// Definitions
#define FOSC 16000000 // Clock Speed 
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


// Pin config
#define RS PC4
// #define RW PC1
#define E PC5

#define lcd PORTC
#define _lcd DDRC
#define _lcd_ PINC


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Global variables


//Prototypes
void lcd_ecrire( unsigned char data );
int lcd_lire( int _RS );
void lcd_initializer4();
int lcd_occupe();
void setCursor( int pos );
void habiliter();
void charger(unsigned char data);
void lcd_print( unsigned char data);

void lcd_ecrire( unsigned char data ){
    // lcd &= ~(1<<E);
    // charger(data >> 4);
    // charger(data);
}

// Carga el nibble menos significativo a la lcd
void charger(unsigned char data){
    lcd |= data & 0x0F;
    habiliter();
}

void habiliter(){
    lcd |= (1<<E);
    _delay_us(1);
    lcd &= ~(1<<E);
    _delay_us(1);
}

void lcd_initializer4(){
    _delay_ms(30);
    lcd &= ~(1<<RS);
    
    // Init
    charger(fSet8);
    _delay_ms(10);
    charger(fSet8);
    _delay_ms(10);
    charger(fSet8);
    _delay_ms(10);
    charger(fSet4);
    _delay_ms(10);

    // Function set
    charger(fSet4);
    charger(fSetLine);
    _delay_ms(10);

    // Entry Mode set
    charger(eModeSet1);
    charger(eModeSet2);
    _delay_ms(10);

    // Display control
    charger(dON);
    charger(dBlink);
    _delay_ms(10);

    // Display clear
    charger(dClear1);
    charger(dClear2);
    _delay_ms(10);

}


void setup(){
    _lcd = 0xFF; 
    lcd = 0;
}

int main(void) {

    setup();
    lcd_initializer4();
    while (1) {
    
    }
}