#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f1xx_hal.h"

#define BEEP_NUM 1  // 蜂鸣器数量

typedef enum {
    BEEP_OFF = 0,  // 蜂鸣器关闭
    BEEP_ON = 1    // 蜂鸣器开启
} BEEP_Mode_e;

typedef struct {
    GPIO_TypeDef* GPIO_Port;  // GPIO端口
    uint16_t GPIO_Pin;        // GPIO引脚
    uint8_t Level;           // 有效电平 (1:高电平有效，0:低电平有效)
} BEEPInstance;

// 蜂鸣器索引定义
typedef enum {
    BEEP_MAIN = 0,  // 主蜂鸣器
} BEEP_Index_e;

// 函数声明
void SetBeep(uint8_t BEEPType, BEEP_Mode_e mode);
void BeepInit(BEEPInstance *instance, uint8_t DevNum);
void BeepDeviceInit(void);

#endif