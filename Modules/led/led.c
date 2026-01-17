#include "led.h"
#include "gpio.h"
LEDInstance led[LED_NUM];
/**
 * @brief 设置LED状态
 * @param LEDType LED类型索引
 * @param mode LED目标状态 (LED_ON 或 LED_OFF)
 */
void SetLed(uint8_t LEDType, LED_Mode_e mode)
{
    if (LEDType >= LED_NUM) return;  // 添加边界检查
    
    GPIO_PinState pinState;
    if (led[LEDType].Level) 
    {
        // 高电平点亮：LED_ON对应高电平，LED_OFF对应低电平
        pinState = (mode == LED_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    }
    else
    {
        // 低电平点亮：LED_ON对应低电平，LED_OFF对应高电平
        pinState = (mode == LED_ON) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    }
    HAL_GPIO_WritePin(led[LEDType].GPIO_Port, led[LEDType].GPIO_Pin, pinState);
}

static void Led_Init(LEDInstance *instance, uint8_t DevNum)
{
    if (DevNum >= LED_NUM) return; 
    
    // 复制配置
    led[DevNum].GPIO_Port = instance->GPIO_Port;
    led[DevNum].GPIO_Pin = instance->GPIO_Pin;
    led[DevNum].Level = instance->Level;
    
    // 初始化时关闭LED
    SetLed(DevNum, LED_OFF);
}


void LedDeviceInit(void)
{
	LEDInstance BalanceLed =
	{
		.GPIO_Port = Balance_GPIO_Port, 
		.GPIO_Pin = Balance_Pin, 
		.Level = 1
	};  
	LEDInstance BTLed =
	{
		.GPIO_Port = BlueTooth_GPIO_Port, 
		.GPIO_Pin = BlueTooth_Pin, 
		.Level = 1
	};  
	LEDInstance FollowLed =
	{
		.GPIO_Port = Follow_GPIO_Port, 
		.GPIO_Pin = Follow_Pin, 
		.Level = 1
	};  
	Led_Init(&FollowLed, LED_FOLLOW);
	Led_Init(&BTLed, LED_BLUETOOTH);
	Led_Init(&BalanceLed, LED_BALANCE);
}
