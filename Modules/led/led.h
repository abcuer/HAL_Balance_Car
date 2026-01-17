#ifndef _LED_H
#define _LED_H

#include "stm32f1xx_hal.h"

#define LED_NUM 3

typedef enum
{
    LED_FOLLOW = 0,
    LED_BLUETOOTH,
    LED_BALANCE
} LED_Type_e;

typedef enum
{
    LED_OFF = 0,
    LED_ON
} LED_Mode_e;

typedef struct
{
    GPIO_TypeDef* GPIO_Port;
    uint16_t GPIO_Pin;
    uint8_t Level; // 1表示高电平点亮，0表示低电平点亮
} LEDInstance;

extern LEDInstance led[LED_NUM];

void LedDeviceInit(void);
void SetLed(uint8_t LEDType, LED_Mode_e mode);

#endif