#include <stdint.h>
#include <stdlib.h>
#include <math.h>



#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"
#include "uart.h"
#include "pendulum.h"

/* TODO: Enable ADC1 clock */
/* TODO: Enable GPIOB clock */
/* TODO: Initialise PB0 with:
- Pin 0
- Analog mode
- No pull
- High frequency */
static ADC_HandleTypeDef hadc1;

void pendulum_init(void)
{
__HAL_RCC_ADC1_CLK_ENABLE();
__HAL_RCC_GPIOB_CLK_ENABLE();

 GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = GPIO_PIN_0;
    GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


/* TODO: Initialise ADC1 with:
- Instance ADC 1
- Div 2 prescaler
- 12 bit resolution
- Data align right
- Continuous conversion mode disabled
- Number of conversions = 1
Note: Configuration parameters not mentioned above
are not required for this lab. */

/* === ADC1 init === */
hadc1.Instance = ADC1;
hadc1.Init.ClockPrescaler     = ADC_CLOCK_SYNC_PCLK_DIV2;
hadc1.Init.Resolution         = ADC_RESOLUTION_12B;
hadc1.Init.DataAlign          = ADC_DATAALIGN_RIGHT;
hadc1.Init.ContinuousConvMode = DISABLE;
hadc1.Init.NbrOfConversion    = 1;
HAL_ADC_Init(&hadc1);
/* TODO: Configure ADC channel to:
- Channel 8
- Rank 1
- Sampling time 480 cycles
- Offset 0 */
ADC_ChannelConfTypeDef sConfig = {0};
sConfig.Channel      = ADC_CHANNEL_8;               
sConfig.Rank         = 1;          
sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;    
sConfig.Offset       = 0;
HAL_ADC_ConfigChannel(&hadc1, &sConfig);


}



float pendulum_read_voltage(void)
{

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 0xFF);
    uint32_t raw = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
/* TODO: Start ADC */
    /* TODO: Poll for conversion. Use timeout of 0xFF. */
    /* TODO: Get ADC value */
    /* TODO: Stop ADC */
    /* TODO: Compute voltage from ADC reading. Hint: 2^12-1 = 4095 */
    /* TODO: Return the computed voltage */
return (raw * 3.3f) / 4095.0f;
}