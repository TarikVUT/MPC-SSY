/*
 * LAB2.c
 *
 * Created: 2/12/2024 13:44:34
 * Author : Student
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "makra.h"
#include "uart/uart.h"
#include "Timers/timer.h"
#include "I2C/i2c.h"


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
	UART_SendString("[0;32;40m"); //BARVA
	
	
	UART_SendString("-------------------------------------\n\r");
	UART_SendString("MENU: \n\r");
	UART_SendString("0 - Konec programu\n\r");
	UART_SendString("1 - Velka abeceda \n\r");
	UART_SendString("2 - Mala abeceda \n\r");
	UART_SendString("3 - Blikne LED \n\r");
	UART_SendString("4 - Generovani 2Hz \n\r");
	UART_SendString("5 - Cteni teploty \n\r");
	UART_SendString("-------------------------------------\n\r");
}


void board_init(){
	
	cli(); 
	
	UART_init(38400); 
	
	UCSR1B |= (1 << RXCIE1);

	stdout = &uart_str; 
	
	
	sbi(DDRB,4);
	sbi(PORTB,4); //LED 0 - off

	sbi(DDRB,5); // LED 1
	sbi(PORTB,5);
	
	
	cbi(DDRE,4);
	sbi(PORTE,4);
	
	sbi(EIMSK,4); //Tlacitko 5 preruseni
	sbi(EICRB,ISC41); //Nastupna hrana
	sbi(EICRB,ISC40); //Sestupna hrana
	
	sei(); // enable interrupts
	Timer2_fastpwm_start(0);
	
}
void LEDblik(){
	DDRB = 0x40;
	for (int i = 0; i < 10; i++)
	{
		PORTB = 0x40;
		_delay_ms(100);
		PORTB = 0x00;
		_delay_ms(100);
	}
	DDRB = 0x00;
}

int main(void)
{
	// USART //

	/*USART_Init(MYUBRR);
	USART_Transmit('H');
	USART_Transmit('E');
	USART_Transmit('L');
	USART_Transmit('L');
	USART_Transmit('O');
	
	
	while(1){
		uint8_t recv;
		recv=USART_Receive();
		USART_Transmit(recv);
	}*/
	
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
				for (int i=65;i<90;i++)
				{
					UART_SendChar(i);
				}
				printf("\n\r");
				break;
				case '2':
				printf("\n\r");
				for (int i=97;i<123;i++)
				{
					UART_SendChar(i);
				}
				break;
				case '3':
				printf("\r\n");
				LEDblik();
				break;
				case '4':
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
				case '5':
				printf("\n\r");
				UART_SendString("Mereni teploty: ");
				//volatile float temp = 1.13 * at30_readTemp() -272.8;
				printf("%f Celsia \n\r", at30_readTemp());
				break;
				
				default:
				printf("\r\nSpatna volba.. \r\n");
				
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

