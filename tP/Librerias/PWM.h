#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void PWM_init(void);
void PWM_update(int Error,int Kp);

#endif
