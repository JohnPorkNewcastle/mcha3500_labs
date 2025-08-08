#include <stdint.h>
#include <stdlib.h>
#include <math.h>



#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"
#include "uart.h"
#include "motor.h"

static TIM_HandleTypeDef htim3;
static volatile int32_t enc_count = 0;
 
 
 
 void motor_PWM_init(void)
{
    /* TODO: Enable TIM3 clock */
    /* TODO: Enable GPIOA clock */
__HAL_RCC_TIM3_CLK_ENABLE();
__HAL_RCC_GPIOA_CLK_ENABLE();


    /* TODO: Initialise PA6 with:
     *   - Pin 6
     *   - Alternate function push-pull mode
     *   - No pull
     *   - High frequency
     *   - AF2 (TIM3) */
GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitStruct.Pin = GPIO_PIN_6;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* TODO: Initialise TIM3 (Instance=TIM3):
 *   - Prescaler = 1
 *   - Counter mode = up
 *   - Period = value for 10 kHz output
 *   - Clock division = 0
 */
htim3.Instance = TIM3;
htim3.Init.Prescaler = 1;
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
htim3.Init.Period = 4999;
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
HAL_TIM_PWM_Init(&htim3);

/* TODO: Configure TIM3 Channel 1:
 *   - OC mode = PWM1
 *   - Pulse = 0 (start OFF)
 *   - OC polarity = high
 *   - Fast mode = disabled
 */
TIM_OC_InitTypeDef sConfigOC = {0};
sConfigOC.OCMode = TIM_OCMODE_PWM1;
sConfigOC.Pulse = 0;
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

/* TODO: Set initial compare for 25% duty */
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1250);


/* TODO: Start TIM3 channel 1 */
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);


}



void motor_encoder_init(void)
{
__HAL_RCC_SYSCFG_CLK_ENABLE();

    /* TODO: Enable GPIOC clock */
__HAL_RCC_GPIOC_CLK_ENABLE();
    /* TODO: Initialise PC0|PC1:
     *   - Pins 0 & 1
     *   - Interrupt on rising & falling edge
     *   - No pull
     *   - High frequency
     */
GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING_FALLING;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* TODO: NVIC priority for EXTI0 and EXTI1 = 0x0F */
    /* TODO: Enable EXTI line 0 & 1 interrupts */

HAL_NVIC_SetPriority(EXTI0_IRQn, 0x0F, 0);
HAL_NVIC_EnableIRQ(EXTI0_IRQn); 


HAL_NVIC_SetPriority(EXTI1_IRQn, 0x0F, 0);
HAL_NVIC_EnableIRQ(EXTI1_IRQn);      



}

void EXTI0_IRQHandler(void)
{
    /* TODO: if (PC0 == PC1) enc_count++; else enc_count--; */
    /* TODO: __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); */
    GPIO_PinState A = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
    GPIO_PinState B = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);

if (A == B)    // i.e. PC0 == PC1
        enc_count++;
    else
        enc_count--;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
}


void EXTI1_IRQHandler(void)
{
    /* TODO: if (PC1 == PC0) enc_count--; else enc_count++; */
    /* TODO: __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1); */
GPIO_PinState A = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
GPIO_PinState B = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);

if (B == A)    // i.e. PC1 == PC0
        enc_count--;
    else
        enc_count++;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);



}


int32_t motor_encoder_getValue(void)
{
    return enc_count;
}
