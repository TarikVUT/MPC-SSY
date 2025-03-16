/*
 * timer.c
 *
 * Created: 2/19/2024 13:40:36
 *  Author: Student
 */ 
#include <stdio.h>
#include "timer.h"
#include "../makra.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


void Timer0_cmp_start(uint8_t porovnani){
	
	cli();
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;
	OCR0A = porovnani;
	
	TCCR0A |= (1 << WGM01);
	TCCR0B |= PRESCALE;
	TIMSK0	 |= (1 << OCIE0A);
	TCCR0A |= (1 << COM0A0);
	sei();
}

void Timer0_ovrf_start(){
	cli();
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;
	
	TCCR0B |= PRESCALE;
	TCCR0A |= (1 << COM0A0);
	TIMSK0 |= (1 << TOIE0);
	sei();
}
void Timer0_fastpwm_start(uint8_t strida){
	
	cli();       
	TCCR0A = 0;    
	TCCR0B = 0;
	TIMSK0 = 0;   

	OCR0A = (255*strida)/100;

	TCCR0A |= (1 << WGM01);
	TCCR0A |= (1 << WGM00);
	TCCR0B |= PRESCALE;

	TIMSK0 |= (1 << TOIE0);

	TCCR0A |= (1 << COM0A1);
	
	sei();         
}
void Timer0_Stop(){
	TCCR0B=0;
}

void Timer1_cmp_A_start(uint16_t porovnani){
	
	cli();         
	TCCR1A = 0;     
	TCCR1B = 0; 
	TIMSK1 = 0;   

	OCR1A = porovnani;

	TCCR1B |=(1<<WGM12);

	TCCR1B |= PRESCALE;

	TIMSK1 |= (1 << OCIE1A);
	TCCR1A |= (1 << COM1A0);
	sei();         
}
void Timer1_cmp_B_start(uint16_t porovnani){
	
	cli();         
	TCCR1A = 0;
	TCCR1B = 0; 
	TIMSK1 = 0;   

	OCR1B = porovnani;

	TCCR1B |= PRESCALE;
	TIMSK1 |= (1 << OCIE1B);

	sei();          
}

void Timer1_ovf_start(uint16_t zbytek){
	cli();          
	TCCR1A = 0;     
	TCCR1B = 0;
	TIMSK1 = 0; 
	TCNT1=65535-zbytek;

	TCCR1B |= PRESCALE;

	TIMSK1 |= (1 << TOIE1);
	sei(); 
}

void Timer1_fastpwm_start(uint8_t strida){
	cli();          
	TCCR1A = 0;    
	TCCR1B = 0;
	TIMSK1 = 0;   

	OCR1A = (1023*strida)/100;

	TCCR1A |= (1 << WGM11);
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	TCCR1B |= PRESCALE;

	TIMSK1 |= (1 << TOIE1);

	TCCR1A |= (1 << COM1A0);
	
	sei();        
}

void Timer1_phasepwm_start(uint8_t strida){
	cli();          
	TCCR1A = 0;    
	TCCR1B = 0;
	TIMSK1 = 0;  

	OCR1A = (1023*strida)/100;

	TCCR1A |= (1 << WGM11);
	TCCR1A |= (1 << WGM10);

	TCCR1B |= (1 << WGM13);

	TCCR1B |= PRESCALE;

	TIMSK1 |= (1 << TOIE1);

	TCCR1A |= (1 << COM1A0);
	
	sei();          
}

void Timer1_Stop(){
	TCCR1B=0;
}
void Timer2_cmp_start(uint8_t porovnani){
	
	cli();         
	TCCR2A = 0;     
	TCCR2B = 0; 
	TIMSK2 = 0;    

	OCR2A = porovnani;

	TCCR2A |= (1 << WGM11);

	TCCR2B |= 5;

	TIMSK2 |= (1 << OCIE2A);

	TCCR2A |= (1 << COM2A0);
	sei();          
}

void Timer2_ovf_start(){
	cli();          
	TCCR2A = 0;     
	TCCR2B = 0;
	TIMSK2 = 0;    

	TCCR2B |= 5;

	TCCR2A |= (1 << COM2A0);

	TIMSK2 |= (1 << TOIE2);
	sei(); 
}

void Timer2_fastpwm_start(uint8_t strida){
	cli();          
	TCCR2A = 0;     
	TCCR2B = 0;
	TIMSK2 = 0;  

	OCR2A = (255*strida)/100;

	TCCR2A |= (1 << WGM21);
	TCCR2A |= (1 << WGM20);

	TCCR2B |= 5;


	TCCR2A |= (1 << COM2A1);
	
	sei();          
}

void Timer2_Stop(){
	TCCR2B=0;
}

void Timer3_cmp_start(uint16_t porovnani){
	
	cli();          
	TCCR3A = 0;     
	TCCR3B = 0; 
	TIMSK3 = 0;    
	
	OCR3A = porovnani;
	
	TCCR3A |= (1 << WGM31);
	
	TCCR3B |= PRESCALE;
	
	TIMSK3 |= (1 << OCIE3A);
	
	sei();          
}
void Timer3_ovf_start(uint16_t zbytek){
	cli();          
	TCCR3A = 0;     
	TCCR3B = 0;
	TIMSK3 = 0;     


	TCNT3=65535-zbytek;

	TCCR3B |= PRESCALE;

	TIMSK3 |= (1 << TOIE3);
	sei(); 
}
void Timer3_Stop(){
	TCCR3B=0;
}