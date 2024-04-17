/*
========================================
<<LIBRERÍA PARA LA LECTURA DEL MCP9803>>
========================================
La autoría de la mayoría de esta libreria es de "mux", fue rescatada de:
https://code.google.com/archive/p/mcp9800/source/default/commits
Sin licencia
Se le hicieron leves modificaciones para mi uso
*/
#include <stdio.h>
#include <stdfix.h>
#include <string.h>
#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h> 
#include <stdio.h>
#include "mcp9800.h"
#include "UART.h"
#define MCP_ADDR        (0x48)
/*MCP registers*/
#define MCP_TEMP        (0x00)
#define MCP_CONFIG      (0x01)
#define MCP_HYSTR       (0x02)
#define MCP_LIMIT       (0x03)
/*CONFIG register bits*/
#define MCP_ONE_SHOT    (7)
#define MCP_ADC_RES     (5)
#define MCP_FAULT_QUEUE (3)
#define MCP_ALERT_POL   (2)
#define MCP_INT_MODE    (1)
#define MCP_SHUTDOWN    (0)
#define R_BIT           (1)
#define W_BIT           (0)

static mcp_alert_callback_t alert_func = NULL;
void i2c_read(uint8_t reg, uint8_t *buf, int len)
{
    //send START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    //wait for packet to be transmitted
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_START) {
        goto error;
    }

    //send SLA+W bit to enter MT mode
    TWDR = ((MCP_ADDR << 1) | W_BIT);
    //wait for packet to be transmitted
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_MT_SLA_ACK) {
        goto error;
    }

    //send register address
    TWDR = reg;
    //wait for packet to be transmitted
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_MT_DATA_ACK) {
        goto error;
    }

    //send repeated START condition 
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    //wait for packet to be transmitted
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_REP_START) {
        goto error;
    }

    //send SLA+R to switch to MR mode
    TWDR = ((MCP_ADDR << 1) | R_BIT);
    //wait for SLA+R
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));      

    if ((TWSR & 0xFB) != TW_MR_SLA_ACK) {
        goto error;
    }

    while (len--) {       
        if (len == 0) {
            TWCR = (1<<TWINT) | (1<<TWEN);
        } else {
            TWCR = (1<<TWINT) | (1<<TWEN) |(1<<TWEA);
        }
        while (!(TWCR & (1<<TWINT)));      
        *buf++ = TWDR;
    }

    //send STOP condition    
    TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
error:
    return;
}

void i2c_wwrite(uint8_t reg, uint8_t *buf, int len)
{
    //send START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    //wait for packet to be transmitted
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_START) {
        goto error;
    }

    //send SLA+W bit to enter MT mode
    TWDR = ((MCP_ADDR << 1) | W_BIT);
    //wait for packet to be transmitted
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_MT_SLA_ACK) {
        goto error;
    }

    //send register address
    TWDR = reg;
    //wait for packet to be transmitted
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xFB) != TW_MT_DATA_ACK) {
        goto error;
    }
   
    //send data packet(s)
    while (len--) {
        TWDR = *buf++;
        //wait for packet to be transmitted
        TWCR = (1<<TWINT) | (1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        if ((TWSR & 0xFB) != TW_MT_DATA_ACK) {
            goto error;
       }
    }
    //send STOP condition    
    TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
error:
    return;
}

void mcp_init()
{

}
#if 0
ISR(INT0_vect,  ISR_BLOCK)
{
    /*must read any register to ack alert*/
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    if (alert_func) {
        alert_func();
    }
}
#endif
void mcp_set_one_shot(uint8_t enable)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(1 << MCP_ONE_SHOT);
    config |= (enable << MCP_ONE_SHOT);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_adc_resolution(mcp_adc_resolution_t resolution)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(3 << MCP_ADC_RES);
    config |= (resolution << MCP_ADC_RES);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_fault_queue(mcp_fault_queue_t fault_queue)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(3 << MCP_FAULT_QUEUE);
    config |= (fault_queue << MCP_FAULT_QUEUE);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_power_mode(mcp_power_mode_t power_mode)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(1 << MCP_SHUTDOWN);
    config |= (power_mode << MCP_SHUTDOWN);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_alert_mode(mcp_alert_mode_t alert_mode)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(1 << MCP_INT_MODE);
    config |= (alert_mode << MCP_INT_MODE);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_alert_polarity(mcp_alert_polarity_t alert_polarity)
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    config &= ~(1 << MCP_ALERT_POL);
    config |= (alert_polarity << MCP_ALERT_POL);
    i2c_wwrite(MCP_CONFIG, &config, 1);
}

void mcp_set_alert_callback(mcp_alert_callback_t callback)
{
    alert_func = callback;
}

void mcp_set_temp_limits(int16_t lower, int16_t upper)
{
    i2c_wwrite(MCP_HYSTR, (uint8_t*) &lower, 2);
    i2c_wwrite(MCP_LIMIT, (uint8_t*) &upper, 2);
}

uint8_t mcp_read_config()
{
    uint8_t config;
    i2c_read(MCP_CONFIG, &config, 1);
    return config;
}

uint16_t mcp_read_temp()
{    
    uint16_t temp;
    i2c_read(MCP_TEMP, (uint8_t*) &temp, 2);
    return temp;
}

float mcp_read_temp_float()
{    
    uint16_t temp;
    i2c_read(MCP_TEMP, (uint8_t*) &temp, 2);
    float t = temp & 0x00ff;
    int frac = (temp>>8);
    if (frac & 0x80) {
        t+=0.5f;
    }
    if (frac& 0x40) {
        t+=0.25f;
    }
    if (frac&0x20) {
        t+=0.125f;
    }
    if (frac&0x10) {
        t+=0.0625f;
    }
    return t;
}
void ImprimirTemperatura(void){
	char buf[32];
	uart_init();
	//init MCP9800 sensor
	mcp_init();
	mcp_set_adc_resolution(MCP_ADC_RES_12);
	mcp_set_power_mode(MCP_POWER_UP);
	int i;
	for (i=1; i<=250; i++)
	{
		float temp = mcp_read_temp_float();
		int temp_whole = (int)temp; // Extract whole number part
		int temp_frac = (int)((temp - temp_whole) * 10000); // Extract fractional part with desired precision
		if(temp_frac < 0) temp_frac = -temp_frac; // Ensure the fractional part is positive
		// Now print both parts separately
		sprintf(buf, "%d.%04d", temp_whole, temp_frac);
		// Send the temperature string over UART
		uart_send_string("-");
	}
    uart_send_newline();
	uart_send_string("Temperatura: ");
	uart_send_string(buf);
	uart_send_newline();
	// Convert the formatted string to an integer
	int MedicionTemperatura = atoi(buf);
	char buffer[10]; // Espacio para la cadena de caracteres
	sprintf(buffer, "%d", MedicionTemperatura); // Convierte el entero a una cadena
	uart_send_string(buffer);
	;
};
int LeerTemperatura(void){
	int i=1;
char buf[32];
uart_init();
//init MCP9800 sensor
mcp_init();
mcp_set_adc_resolution(MCP_ADC_RES_12);
mcp_set_power_mode(MCP_POWER_UP);
for (i=1; i<=250; i++)
{
	float temp = mcp_read_temp_float();
	int temp_whole = (int)temp; // Extract whole number part
	int temp_frac = (int)((temp - temp_whole) * 10000); // Extract fractional part with desired precision
	if(temp_frac < 0) temp_frac = -temp_frac; // Ensure the fractional part is positive
	// Now print both parts separately
	sprintf(buf, "%d.%04d", temp_whole, temp_frac);
	// Send the temperature string over UART
	uart_send_string(" ");
}
uart_send_newline();
//uart_send_string("Temperatura: ");
//uart_send_string(buf);
//uart_send_newline();
// Convert the formatted string to an integer
int MedicionTemperatura = atoi(buf);
char buffer[10]; // Espacio para la cadena de caracteres
sprintf(buffer, "%d", MedicionTemperatura); // Convierte el entero a una cadena
uart_send_string(buffer);
    return MedicionTemperatura;}
	