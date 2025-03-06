/*
 * Created: 24/02/2025
 * Author : Tarik
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "makra.h"
#include "uart/uart.h"
#include "Timers/timer.h"



#define F_CPU 8000000
#define FREKVENCE 2
#define BAUD 38400
#define MYUBRR (F_CPU/16/BAUD-1)

volatile char recv;
volatile uint8_t state=0;
volatile uint8_t klik=0;
int generuj2Hz = 1;

FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW);

void board_init();
void menu();

void menu(){
	UART_SendChar(27);
	UART_SendString("[0;33;40m");
	UART_SendString("-------------------------------------\n\r");
	UART_SendString("MENU: \n\r");
	UART_SendString("0 - Konec programu\n\r");
	UART_SendString("1 - Mala abeceda \n\r");
	UART_SendString("2 - Velka abeceda \n\r");
	UART_SendString("3 - Blikni LED \n\r");
	UART_SendString("4 - Potom \n\r");
	UART_SendString("5 - Generovani 2Hz \n\r");
	UART_SendString("-------------------------------------\n\r");
}


void board_init(){
	
	cli(); 
	
	UART_init(38400); 
	
	UCSR1B |= (1 << RXCIE1);

	stdout = &uart_str; 
	
	
	sbi(DDRB,4);
	sbi(PORTB,4); //LED 0 - off

	sbi(DDRB,5); 
	sbi(PORTB,5);
	
	
	cbi(DDRE,4);
	sbi(PORTE,4);
	
	sbi(EIMSK,4);
	sbi(EICRB,ISC41); 
	sbi(EICRB,ISC40);
	
	sei(); 
}
// Blikani
void LEDblik(){
	DDRB = 0x40;
	for (int i = 0; i < 5; i++)
	{
		
		PORTB = 0x40;
		_delay_ms(200);
		PORTB = 0x00;
		_delay_ms(200);
		
	}
	DDRB = 0x00;
}

int main(void)
{

	board_init();
	_delay_ms(100);
	menu();
	_delay_ms(100);
	
	
	
		int i=0;
	while (1)
	{
		if (state==1){
			switch (recv)  			{
				case '0':
				printf("\r\n Konec programu... \r\n");
				menu();
				break;
				
				case '1':
				printf("\n\r");
				// Mala abc
				for (int i=97;i<123;i++)
				{
					UART_SendChar(i);
				}
				
				printf("\n\r");
				break;
				case '2':
				printf("\n\r");
				for (int i=65;i<90;i++)
				{
					UART_SendChar(i);
				}
				printf("\n\r");
				break;
				case '3':
				
				printf("\r\n");
				LEDblik();
				printf("\r\n");
				break;
				case '4':
				printf(" Potom\n\r");
			
				break;
				case '5':
				printf("\n\r");
				if(generuj2Hz){
					printf("Stop generovani \r\n");
					generuj2Hz = 0;
					Timer1_Stop();
				}
				else{
					printf("Start generovani \r\n");
					uint16_t registr_CMP=(F_CPU/FREKVENCE/2/PRESCALE_VALUE)-1;
					Timer1_cmp_A_start(registr_CMP);
					generuj2Hz=1;
					
				}
				break;
				
				default:
				printf("\r\n Spatna volba.. \r\n");
				
			}
			state=0;
		}
		_delay_ms(100);
		i++;
	}
}
//####################################################### PRERUSENI #########################################################//
ISR(INT4_vect){
	cbi(EIMSK,INT4);//zakazane preruseni
	
	_delay_ms(200);
	klik++;
	LED0CHANGE;
	sbi(EIFR,INTF4);
	sbi(EIMSK,INT4); //Povoleni preruseni
}

ISR(USART1_RX_vect)
{
	recv = UART_GetChar();
	UART_SendChar(recv);
	state=1;
}

