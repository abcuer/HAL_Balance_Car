#include "beep.h"
#include "gpio.h" 

static BEEPInstance beep[BEEP_NUM];

/**
 * @brief 根据当前状态更新GPIO电平
 */
static void UpdateBeepPinLevel(BEEP_Type_e BeepType)
{
    BEEPInstance *instance = &beep[BeepType];
    
    // 逻辑：如果当前模式为 ON，则输出有效电平；否则输出相反电平
    GPIO_PinState pinState;
    if (instance->RunningParam.CurrentMode == BEEP_ON) {
        pinState = (instance->StaticParam.ActiveLevel == BEEP_HIGH_LEVEL_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    } else {
        pinState = (instance->StaticParam.ActiveLevel == BEEP_HIGH_LEVEL_ON) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    }
    
    HAL_GPIO_WritePin(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin, pinState);
}

/**
 * @brief 设置蜂鸣器开关状态
 */
void SetBeepMode(BEEP_Type_e BeepType, BEEP_Mode_e Mode)
{
    if (BeepType >= BEEP_NUM) return;
    
    beep[BeepType].RunningParam.CurrentMode = Mode;
    UpdateBeepPinLevel(BeepType);
}

/**
 * @brief 翻转蜂鸣器状态（常用于报警鸣叫）
 */
static void BeepToggle(BEEP_Type_e BeepType)
{
    if (BeepType >= BEEP_NUM) return;
    
    BEEP_Mode_e nextMode = (beep[BeepType].RunningParam.CurrentMode == BEEP_ON) ? BEEP_OFF : BEEP_ON;
    SetBeepMode(BeepType, nextMode);
}

/**
 * @brief 单个蜂鸣器内部初始化
 */
static void Beep_Init(BeepStaticParam_s *config, BEEP_Type_e BeepType)
{
    if (BeepType >= BEEP_NUM) return; 
    
    // 复制硬件配置
    beep[BeepType].StaticParam = *config;
    // 初始化时保持关闭
    SetBeepMode(BeepType, BEEP_OFF);
}

/**
 * @brief 蜂鸣器设备总初始化
 */
void BeepDeviceInit(void)
{ 
    BeepStaticParam_s config;

    config.GPIO_Port = BEEP_GPIO_Port;
    config.GPIO_Pin = BEEP_Pin;
    config.ActiveLevel = BEEP_LOW_LEVEL_ON; 
    
    Beep_Init(&config, BEEP_SYSTEM);
}