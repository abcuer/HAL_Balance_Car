#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"

#define KEY_NUM 1  // 按键数量

// 按键索引定义
typedef enum {
    KEY_USER = 0,  // 用户按键
} KEY_Type_e;

// 按键状态枚举
typedef enum {
    KEY_RELEASED = 0,  // 按键释放
    KEY_PRESSED = 1    // 按键按下
} KEY_State_e;

// 按键检测模式
typedef enum {
    KEY_MODE_NORMAL = 0,     // 正常模式（按下触发）
    KEY_MODE_CONTINUOUS = 1  // 连按模式
} KEY_Mode_e;

// 按键实例结构体
typedef struct {
    GPIO_TypeDef* GPIO_Port;  // GPIO端口
    uint16_t GPIO_Pin;        // GPIO引脚
    uint8_t Level;           // 有效电平 (1:高电平按下，0:低电平按下)
    KEY_Mode_e Mode;         // 按键检测模式
    uint32_t LastPressTime;  // 上次按下时间（用于消抖或连按）
    KEY_State_e LastState;   // 上次状态
} KEYInstance;

// 函数声明
void KeyDeviceInit(void);
uint8_t Key_GetNum(uint8_t KeyType);

#endif