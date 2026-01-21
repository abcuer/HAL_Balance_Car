#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f1xx_hal.h" 

typedef enum {
    BSP_GPIO_SPEED_LOW  = GPIO_SPEED_FREQ_LOW,
    BSP_GPIO_SPEED_MID  = GPIO_SPEED_FREQ_MEDIUM,
    BSP_GPIO_SPEED_HIGH = GPIO_SPEED_FREQ_HIGH
} GPIO_Speed_e;

// 函数声明
void GPIO_Output(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Speed_e speed);
void GPIO_Input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mode);
void GPIO_SetClock(GPIO_TypeDef* GPIOx, FunctionalState state);

#endif