#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
void i2c_init();
void i2c_start();
void i2c_write(char x);
void i2c_stop();


#endif