/*
========================================
<<LIBRERÍA PARA LA LECTURA DEL MCP9803>>
========================================
La autoría de la mayoría de esta libreria es de "mux", fue rescatada de:
https://code.google.com/archive/p/mcp9800/source/default/commits
Sin licencia
Se le hicieron leves modificaciones para mi uso
*/
#ifndef __MCP9800_H__
#define __MCP9800_H___
#include <stdint.h>
typedef enum {
    MCP_ADC_RES_9,
    MCP_ADC_RES_10,
   MCP_ADC_RES_11,
    MCP_ADC_RES_12
}mcp_adc_resolution_t;

typedef enum {
    MCP_FAULT_QUEUE_1,
    MCP_FAULT_QUEUE_2,
    MCP_FAULT_QUEUE_3,
    MCP_FAULT_QUEUE_4,
}mcp_fault_queue_t;

typedef enum {
    MCP_ALERT_POL_LOW,
    MCP_ALERT_POL_HIGH
}mcp_alert_polarity_t;

typedef enum {
    MCP_COMP_MODE,
    MCP_INT_MODE,
}mcp_alert_mode_t;

typedef enum {
    MCP_POWER_UP,
    MCP_POWER_DOWN
}mcp_power_mode_t;

typedef void (*mcp_alert_callback_t) (void);
void mcp_init();
void mcp_set_one_shot(uint8_t enable);
void mcp_set_adc_resolution(mcp_adc_resolution_t adc_resolution);
void mcp_set_fault_queue(mcp_fault_queue_t fault_queue);
void mcp_set_power_mode(mcp_power_mode_t power_mode);
void mcp_set_alert_mode(mcp_alert_mode_t alert_mode);
void mcp_set_alert_polarity(mcp_alert_polarity_t alert_polarity);
void mcp_set_alert_callback(mcp_alert_callback_t callback);
void mcp_set_temp_limits(int16_t lower, int16_t upper);
void ImprimirTemperatura(void);
int LeerTemperatura(void);
uint8_t mcp_read_config();
uint16_t mcp_read_temp();
float mcp_read_temp_float();
#endif/*__MCP9800_H__*/
