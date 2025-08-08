#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>


 // Initialise TIM3 for PWM output on PA6 (10 kHz, 25 % duty)

void motor_PWM_init(void);

//  Initialise PC0/PC1 as a quadrature‐encoder input (EXTI0/1).

void motor_encoder_init(void);


//  Return the current quadrature count.
// Encoder tick count (signed 32-bit).
int32_t motor_encoder_getValue(void);

#endif 