#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f1xx_hal.h"

// 如果有多个蜂鸣器可以增加此值
#define BEEP_NUM 1

typedef enum
{
    BEEP_SYSTEM = 0,
} BEEP_Type_e;

typedef enum
{
    BEEP_OFF = 0,
    BEEP_ON
} BEEP_Mode_e;

typedef enum
{
    BEEP_LOW_LEVEL_ON = 0,
    BEEP_HIGH_LEVEL_ON,
} BEEP_ActiveLevel_e; // 触发电平

typedef struct
{
    GPIO_TypeDef* GPIO_Port;
    uint16_t GPIO_Pin;
    BEEP_ActiveLevel_e ActiveLevel; // 鸣叫时的有效电平
} BeepStaticParam_s;

typedef struct
{
    BEEP_Mode_e CurrentMode;
} BeepRunningParam_s;

typedef struct
{
    BeepStaticParam_s StaticParam;
    BeepRunningParam_s RunningParam;
} BEEPInstance;

/* 外部调用接口 */
void BeepDeviceInit(void);
void SetBeepMode(BEEP_Type_e BeepType, BEEP_Mode_e Mode);

#endif