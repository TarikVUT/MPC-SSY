/*
 * LAB1.c
 *
 * Author : Tarik
 */ 

/************************************************************************/
/* INCLUDE                                                              */
/************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "libs/libprintfuart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/************************************************************************/
/* DEFINES                                                              */
/************************************************************************/

// F_CPU definovano primo v projektu!!! Debug->Properties->Toolchain->Symbols

/************************************************************************/
/* VARIABLES                                                            */
/************************************************************************/

//musime vytvorit soubor pro STDOUT
FILE uart_str = FDEV_SETUP_STREAM(printCHAR, NULL, _FDEV_SETUP_RW);

/************************************************************************/
/* PROTOTYPES                                                           */
/************************************************************************/

void board_init();

/************************************************************************/
/* FUNCTIONS                                                            */
/************************************************************************/
void board_init(){
	UART_init(38400); //nastaveni rychlosti UARTu, 38400b/s
	stdout = &uart_str; //presmerovani STDOUT
}

#define UPPER_CASE 1  
#define NORMAL_CASE 0

#define DIRECTION_UP 1   
#define DIRECTION_DOWN 0

#define FIELD_SIZE 52  


char alphabetField[FIELD_SIZE];

 
void generateField(int caseType) {
	if (caseType != UPPER_CASE && caseType != NORMAL_CASE) {
		printf("PROGRAM ERROR\n");
		return;
	}

	for (int i = 0; i < 26; i++) {
		if (caseType == UPPER_CASE) {
			alphabetField[i] = 'A' + i; 
			alphabetField[i + 26] = 'A' + i + 32;
			} else if (caseType == NORMAL_CASE) {
			alphabetField[i] = 'a' + i; 
			alphabetField[i + 26] = 'a' + i - 32;  
		}
	}
}

 
void capsLetters(int caseType) {
	if (caseType != UPPER_CASE && caseType != NORMAL_CASE) {
		printf("PROGRAM ERROR\n");
		return;
	}

	for (int i = 0; i < FIELD_SIZE; i++) {
		if (caseType == UPPER_CASE) {
			alphabetField[i] = toupper(alphabetField[i]); 
			} else if (caseType == NORMAL_CASE) {
			alphabetField[i] = tolower(alphabetField[i]);  
		}
	}
}

void printField(int direction) {
	if (direction != DIRECTION_UP && direction != DIRECTION_DOWN) {
		printf("PROGRAM ERROR\n");
		return;
	}

	if (direction == DIRECTION_UP) {
		for (int i = 0; i < FIELD_SIZE; i++) {
			printf("%c ", alphabetField[i]);
		}
		} else if (direction == DIRECTION_DOWN) {
		for (int i = FIELD_SIZE - 1; i >= 0; i--) {
			printf("%c ", alphabetField[i]);
		}
	}
	printf("\n");
}

int main(void)
{ 	
	
	int variable = 10;
	#ifdef ODECET
	variable -= CONSTANT;
	// Task 4
	
	#endif
	printf("Value of variable: %d\n", variable);
	
	// Task 5
	unsigned char a = 255; 
	unsigned char b = 255;
	
	unsigned int sum = (unsigned int)a + (unsigned int)b;
	printf("Soucet: %u\n", sum);
	
	// Task 6
	int number = 24;
	number >>= 3;
	number -= 1;
	
	number &= 0x2;

	// Task 7
	int value = 200;
	
	char str[80] = "Hodnota=";
	
	char valueStr[20];  
	sprintf(valueStr, "%d", value);  
	strcat(str, valueStr); 

	//printf("Vysledek pomoci strcat a sprintf: %s\n", str);

	char result[80];
	sprintf(result, "Hodnota=%d", value); 
	//printf("Vysledek pomoci sprintf: %s\n", result);
	
	
	// Task 8
	int caseType = UPPER_CASE; 
	int direction = DIRECTION_UP;  

	
	generateField(caseType);
	capsLetters(NORMAL_CASE); 
	printField(direction);
	
	// Task 9
	int number = 42;         
	int *ptr = &number;     

	printf("Hodnota promenne 'number': %d\n", number);  
	printf("Hodnota, na kterou ukazuje ukazatel 'ptr': %d\n", *ptr);  
	printf("Adresa pameti, kde je ulozena promenna 'number': %p\n", (void*)&number); 
	printf("Adresa pameti, na kterou ukazuje ukazatel 'ptr': %p\n", (void*)ptr); 
	 
	board_init();
	printf("Hello, I am here\n\r");
	
	// Task 4
	printf("Value of variable: %d\n\r", variable);
	
	// Task 5
	printf("Soucet: %u\n\r", sum);
	
	// Task 6
	printf("Vysledek: %d\n\r", number);
	
	// Task 7
	printf("Vysledek pomoci strcat a sprintf: %s\n\r", str);
	
	printf("Vysledek pomoci sprintf: %s\n\r", result);
	
	
	
	
	
	
	
	
	
	int i=0;
    while (1) 
    {
	_delay_ms(10000);
	i++;
	printf("Test x = %d \n\r", i);
    }
}

