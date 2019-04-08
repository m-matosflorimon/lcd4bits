


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define lcd PORTC
#define _lcd DDRC

#define rs 4
#define en 5
#define d4 0
#define d5 1
#define d6 2
#define d7 3

void charger( char a );
void chargerInst( char a);
void lcdEcrire( char a);
void habiliter();
void lcdInitialiser4();
void lcdPrint(const char *p);
void lcdCursor(int a, int b);

// Carga una instruccion a la lcd en 4 bits
void chargerInst( char a){
	charger((a >> 4) & 0x0F);
    charger(a & 0x0F);
}

// Carga la lcd con una instruccion
void charger( char a ){
    lcd = a;
	lcd &=~(1<<rs);
    habiliter();
}

// Carga la lcd con un dato
void chargerD( char a ){
    lcd = a;
    lcd |=(1<<rs);
	habiliter();
}

// Carga un dato a la lcd en 4 bits
void lcdEcrire( char a){
	chargerD((a >> 4) & 0x0F);
    chargerD(a & 0x0F);
}

// Da un pulso al Enable
void habiliter(){
    lcd |=(1<<en);
	_delay_ms(2);
	lcd &=~(1<<en);
    _delay_ms(2);
}

// Inicializa la lcd en 4 bits
void lcdInitialiser4(){
	_lcd |= ((1<<rs)|(1<<en));
	_lcd |= ((1<<d7)|(1<<d6)|(1<<d5)|(1<<d4));
    char commands[6] = {0x01,0x02,0x28,0x06,0x0F,0x80};
	_delay_ms(2);

    for(int i = 0 ; i < 6 ; i++){
        chargerInst(commands[i]);
    }
}

// Imprime un string en la lcd
void lcdPrint(const char *p){
	while(*p != '\0'){
		lcdEcrire(*p);
		p++; 
        _delay_ms(2);
	}
}

// Setea el cursor de la lcd (solo funciona para 16x2)
void lcdCursor(int a, int b){
    chargerInst((0x80 + b*0x40) | a);
}

int main(){

    lcdInitialiser4();

	lcdCursor(0,0);
	lcdPrint("Miguel");
	lcdCursor(0,1);
	lcdPrint("Ta pile jalto!");
    lcdCursor(0,0);
	while(1);	

}