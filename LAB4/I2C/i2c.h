/*
 * i2c.h
 *
 * Created: 2/26/2024 13:23:25
 *  Author: Student
 */ 
#ifndef I2C_H_
#define I2C_H_



void i2cInit (void);
void i2cStart (void);
void i2cStop (void);
void i2cWrite(uint8_t u8data);
uint8_t i2cReadNACK(void);
uint8_t i2cGetStatus(void);
float at30_readTemp(void);
uint8_t at30_setPrecision(uint8_t prec);


#endif /* I2C_H_ */