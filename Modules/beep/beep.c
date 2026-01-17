#include "beep.h"
#include "gpio.h"

BEEPInstance beep[BEEP_NUM];

/**
 * @brief 设置蜂鸣器状态
 * @param BEEPType 蜂鸣器类型索引
 * @param mode 蜂鸣器目标状态 (BEEP_ON 或 BEEP_OFF)
 */
void SetBeep(uint8_t BEEPType, BEEP_Mode_e mode)
{
    if (BEEPType >= BEEP_NUM) return;  // 添加边界检查
    GPIO_PinState pinState;
    if (beep[BEEPType].Level) 
    {
        pinState = (mode == BEEP_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    }
    else
    {
        pinState = (mode == BEEP_ON) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    }
    HAL_GPIO_WritePin(beep[BEEPType].GPIO_Port, beep[BEEPType].GPIO_Pin, pinState);
}

/**
 * @brief 初始化蜂鸣器实例
 * @param instance 蜂鸣器实例指针
 * @param DevNum 设备编号
 */
void BeepInit(BEEPInstance *instance, uint8_t DevNum)
{
    if (DevNum >= BEEP_NUM) return; 
    
    // 复制配置
    beep[DevNum].GPIO_Port = instance->GPIO_Port;
    beep[DevNum].GPIO_Pin = instance->GPIO_Pin;
    beep[DevNum].Level = instance->Level;
    
    // 初始化时关闭蜂鸣器
    SetBeep(DevNum, BEEP_OFF);
}

/**
 * @brief 蜂鸣器设备初始化
 */
void BeepDeviceInit(void)
{
    BEEPInstance mainBeep =
    {
        .GPIO_Port = BEEP_GPIO_Port, 
        .GPIO_Pin = BEEP_Pin, 
        .Level = 1  // 假设高电平有效
    };  
    
    BeepInit(&mainBeep, BEEP_MAIN);
}
