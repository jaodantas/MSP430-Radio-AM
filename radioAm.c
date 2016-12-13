/*
 *  Simple AM Rádio
 * Author: João Dantas (jcfdantas@gmail.com)
 * 
 * http://jdantas.com/2016/12/12/simples-transmissao-am-com-msp430-launchpad/
 * 
 * Packages needed: msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
 * Usage:
 * 	make comp 
 *	make debug
 *  (mspdebug) prog freq.elf
 *  (mspdebug) run
 * 
 */


#include <msp430g2253.h>

volatile unsigned long tempo = 0;
volatile unsigned int compasso = 0;
volatile int i = 0;
volatile int j = 0;
volatile int bpm = 30000;

#define RED		  BIT0
#define GREEN     BIT6


/* Definição das notas, calculado com 8,000,000 Hz / frequência da nota */

#define C3 30578
#define Cs3 28862
#define Db3 28862
#define D3 27242
#define Ds3 25713
#define Eb3 25713
#define E3 24270
#define F3 22908
#define Fs3 21622
#define G3 20408
#define Gs3 19263
#define A3 18182
#define As3 17161
#define B3 16198

#define C4 15296
#define Cs4 14431
#define Db4 14431
#define D4 13621
#define Ds4 12856
#define Eb4 12856
#define E4 12135
#define F4 11454
#define Fs4 10811
#define Gb4 10811
#define G4 10204
#define Gs4 9631
#define Ab4 9631
#define A4 9091
#define As4 8581
#define Bb4 8581
#define B4 8099

#define C5 7645
#define Cs5 7215
#define Db5 7215
#define D5 6810
#define Ds5 6428
#define Eb5 6428
#define E5 6067
#define F5 5727
#define Fs5 5405
#define Gb5 5405
#define G5 5102
#define Gs5 4816
#define Ab5 4816
#define A5 4545
#define As5 4290
#define Bb5 4290
#define B5 4050

#define REST 100

/*
 *	Tempo
 */
#define t05 4000  
#define t1 10000 
#define t2 20000
#define t3 30000


/*
 * Função quer vai modificar a frequência do sinal mensagem.
 */
void play(int nota, int dur);

/*
 * Função que funciona como uma pausa musical.
 */
void rest(int dur);


/*
 * Funções que compoem a música do Super Mario
 */
void song_measure_1();
void song_measure_2();
void song_measure_3();
void song_measure_4();
void song_measure_5();
void song_measure_6();
void song_measure_7();
void song_measure_8();

/*
 * Função que junta as partes da música do Super Mário
 */
void song_mario();

/*
 * Função que executa a música Marcha Imperial.
 */
void song_starwars();

int main(void) {

	/*** Watchdog timer and clock Set-Up ***/
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	DCOCTL = 0;             		// Select lowest DCOx and MODx
	BCSCTL1 = CALBC1_8MHZ;  		// Set range
	DCOCTL = CALDCO_8MHZ;   		// Set DCO step + modulation

	/*** GPIO Set-Up ***/
	P1DIR |= BIT2;					// P1.2 set as output
	P1SEL |= BIT2;					// P1.2 selected Timer0_A Out1
	P2DIR |= BIT1;					// P2.1 set as output
	P2SEL |= BIT1;					// P2.1 selected Timer1_A Out1

	P1DIR |= RED;					// Launchpad LEDs for output
    P1OUT &= ~RED;					// Red LED off at startup

	/*** Timer0_A Set-Up ***/ 
    /* Sinal da portadora: 1MHz */
	
	TA0CCR0 |= 8 - 1;				// PWM Period
	TA0CCTL1 |= OUTMOD_7;			// TA0CCR1 output mode = reset/set
	TA0CCR1 |= 4;					// TA0CCR1 PWM duty cycle
	TA0CTL |= TASSEL_2 + MC_1;		// SMCLK, Up Mode (Counts to TA0CCR0)
	TA0CCTL0 |= CCIE;

	/*** Timer1_A Set-Up ***/  
    /* Sinal mensagem */

	TA1CCR0 |= C4 - 1; 			    // PWM Period
	TA1CCTL1 |= OUTMOD_7;			// TA1CCR1 output mode = reset/set
	TA1CCR1 |= C4/2;				// TA1CCR1 PWM duty cycle
	TA1CTL |= TASSEL_2 + MC_1;		// SMCLK, Up Mode (Counts to TA1CCR0)
	TA1CCTL0 |= CCIE;

    //bpm = t05; // for star wars
    bpm = t3; // for mario

    while (1) {

	    song_mario();
        //song_starwars();
	}
}



void play(int nota, int dur) {
 
 	for (j = 0; j <= dur; j++) {
		for (i = 0; i <= bpm; i++) {
			TA1CCR0 = nota - 1;
			TA1CCR1 = nota/2;
		}
	}
    P1OUT ^= RED;
}

void rest(int dur) {
 
 	for (j = 0; j <= dur; j++) {
		for (i = 0; i <= bpm; i++) {
			TA1CCR0 = REST - 1;
			TA1CCR1 = REST/2;
		}
	}
}



void song_measure_1() {
    play(E4, 1);
    play(E4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C4, 1);
    play(E4, 1);
    rest(1);
    play(G4, 1);
    rest(3);
    play(G3, 1);
    rest(3);
}

void song_measure_2() {
    
    play(C4, 1);
    rest(2);
    play(G3, 1);
    rest(2);
    play(E3, 1);
    rest(2);
    play(A3, 1);
    rest(1);
    play(B3, 1);
    rest(1);
    play(As3, 1);
    play(A3, 1);
    rest(1);
}

void song_measure_3() {
    play(G3, 1);
    play(E4, 1);
    rest(1);
    play(G4, 1);
    play(A4, 1);
    rest(1);
    play(F4, 1);
    play(G4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    play(B3, 1);
    rest(2);
}

void song_measure_4() {
    rest(2);
    play(G4, 1);
    play(Fs4, 1);
    play(F4,1);
    play(Ds4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(Gs3, 1);
    play(A3, 1);
    play(C4, 1);
    rest(1);
    play(A3, 1);
    play(C4, 1);
    play(D4, 1);
}

void song_measure_5() {
    rest(2);
    play(G4, 1);
    play(Fs4, 1);
    play(F4,1);
    play(Ds4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C5, 1);
    rest(1);
    play(C5, 1);
    play(C5, 1);
    rest(3);
}

void song_measure_6() {
    rest(2);
    play(Eb4, 1);
    rest(2);
    play(D4, 1);
    rest(2);
    play(C4, 1);
    rest(7);
}

void song_measure_7() {
    play(C4, 1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    rest(1);
    play(E4, 1);
    play(C4, 1);
    rest(1);
    play(A3, 1);
    play(G3, 1);
    rest(3);
}

void song_measure_8() {
    play(C4, 1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    play(E4,1);
    rest(7);
}

void song_mario() {
    song_measure_1();
    song_measure_2();
    song_measure_3();
    song_measure_2();
    song_measure_3();
    song_measure_4();
    song_measure_5();
    song_measure_4();
    song_measure_6();
    song_measure_4();
    song_measure_5();
    song_measure_4();
    song_measure_6();
    song_measure_7();
    song_measure_8();
    song_measure_7();
}


void song_starwars() {
    play(A3, 50);
    play(A3, 50);
    play(A3, 50);
    play(F3, 35);
    play(C4, 15);
    play(A3, 50);
    play(F3, 35);
    play(C4, 15);
    play(A3, 65);
 
    rest(15);
 
    play(E4, 50);
    play(E4, 50);
    play(E4, 50);
    play(F4, 35);
    play(C4, 15);
    play(Gs3, 50);
    play(F3, 35);
    play(C4, 15);
    play(A3, 65);
 
    rest(15);
 
    play(A4, 50);
    play(A3, 30);
    play(A3, 15);
    play(A4, 40);
    play(Gs4, 20);
    play(G4, 20);
    play(Fs4, 12);
    play(F4, 12);
    play(Fs4, 25);
 
    rest(25);
 
    play(As3, 25);
    play(Ds4, 40);
    play(D4, 20);
    play(Cs4, 20);
    play(C4, 12);
    play(B3, 12);
    play(C4, 25);
 
    rest(25);
 
    play(F3, 12);
    play(Gs3, 50);
    play(F3, 37);
    play(A3, 12);
    play(C4, 50);
    play(A3, 37);
    play(C4, 12);
    play(E4, 65);
 
    play(A4, 50);
    play(A3, 30);
    play(A3, 15);
    play(A4, 40);
    play(Gs4, 20);
    play(G4, 20);
    play(Fs4, 12);
    play(F4, 12);
    play(Fs4, 25);
 
    rest(25);
 
    play(As3, 25);
    play(Ds4, 40);
    play(D4, 20);
    play(Cs4, 20);
    play(C4, 12);
    play(B3, 12);
    play(C4, 25);
 
    rest(25);
 
    play(F3, 25);
    play(Gs3, 50);
    play(F3, 37);
    play(C4, 12);
    play(A3, 50);
    play(F3, 37);
    play(C4, 12);
    play(A3, 65);

}
