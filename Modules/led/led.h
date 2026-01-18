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

typedef enum
{
    LED_LOW_LEVEL_ON = 0,
    LED_HIGH_LEVEL_ON,
} LED_ActiveLevel_e;

typedef struct
{
    GPIO_TypeDef* GPIO_Port;
    uint16_t GPIO_Pin;
    LED_ActiveLevel_e ActiveLevel; // 工作时的电平
} LedStaticParam_s;

typedef struct
{
    LED_Mode_e CurrentMode;
} LedRunningParam_s;

typedef struct
{
    LedStaticParam_s StaticParam;
    LedRunningParam_s RunningParam;
} LEDInstance;

void LedDeviceInit(void);
void SetLedMode(LED_Type_e LEDType, LED_Mode_e Mode);

#endif