/*
 * i2c.c
 *
 * Created: 2/26/2024 13:23:11
 *  Author: Student
 */ 
#include "../makra.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "I2C.h"
#include "AT30TSE758.h"
#include "../makra.h"


void i2cInit(void)
{
	//400 kHZ SCL
	TWSR = 0x00;
	TWBR = 0x02;

	TWCR = (1<<TWEN);
}

void i2cStart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void i2cStop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2cWrite(uint8_t u8data)
{
	TWDR = u8data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t i2cReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}
uint8_t i2cReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t i2cGetStatus(void)
{
	uint8_t status;
	status = TWSR & 0xF8;

	return status;
}
uint8_t at30_setPrecision(uint8_t prec) {
	uint16_t config_register = 0;
	config_register |= (uint16_t)(prec << R0);


	i2cStart();
	i2cWrite(TempSensorAddrW);

	if (i2cGetStatus() != 0x18) {
		UART_SendString("Error 18\n\r");
		return 0;
	}

	i2cWrite(Temp_configRegister);

	if (i2cGetStatus() != 0x28) {
		UART_SendString("Error 28\n\r");
		return 0;
	}

	i2cWrite((uint8_t)(config_register >> 8));

	if (i2cGetStatus() != 0x28) {
		UART_SendString("Error 28\n\r");
		return 0;
	}

	i2cWrite((uint8_t)(config_register));

	if (i2cGetStatus() != 0x28) {
		UART_SendString("Error 28\n\r");
		return 0;
	}

	i2cStop();

	return 1;
}

float at30_readTemp(void) {
	volatile uint8_t buffer[2];
	volatile uint16_t teplotaTMP;

	i2cStart();
	i2cWrite(TempSensorAddrW);

	if (i2cGetStatus() != 0x18) {
		UART_SendString("Error 18\n\r");
	}

	i2cWrite(Temp_tempRegister);

	if (i2cGetStatus() != 0x28) {
		UART_SendString("Error 28\n\r");
	}

	i2cStop();

	i2cStart();

	if (i2cGetStatus() != 0x08) {
		UART_SendString("Error 08\n\r");
	}

	i2cWrite(TempSensorAddrR);

	if (i2cGetStatus() != 0x40) {
		UART_SendString("Error 40\n\r");
	}

	buffer[0] = i2cReadACK();

	if (i2cGetStatus() != 0x50) {
		UART_SendString("Error 50\n\r");
	}

	buffer[1] = i2cReadNACK();

	if (i2cGetStatus() != 0x58) {
		UART_SendString("Error 58\n\r");
	}

	i2cStop();

	teplotaTMP = (buffer[0] << 8) | buffer[1];
	
	return (float)teplotaTMP / 256.0;
}
	