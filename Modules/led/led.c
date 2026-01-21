#include "led.h"
#include "bsp_gpio.h"
#include "gpio.h"

static LEDInstance led[LED_NUM];

/**
 * @brief 获取任意一个LED的数据
 */
static const LEDInstance *GetLedInstance(LED_Type_e LedType)
{
	return &led[LedType];
}

/**
 * @brief 根据当前状态更新GPIO电平
 */
static void UpdatePinLevel(LED_Type_e LedType)
{
    LEDInstance *instance = &led[LedType];
    // 逻辑：状态与有效电平相同则置位，不同则复位
    GPIO_PinState pinState = (instance->RunningParam.CurrentMode == instance->StaticParam.ActiveLevel) ? 
                              GPIO_PIN_SET : GPIO_PIN_RESET;
    
    HAL_GPIO_WritePin(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin, pinState);
}

/**
 * @brief 设置LED状态
 */
void SetLedMode(LED_Type_e LedType, LED_Mode_e Mode)
{
	if (LedType >= LED_NUM) return;

    led[LedType].RunningParam.CurrentMode = Mode;
    // 更新GPIO电平
    UpdatePinLevel(LedType);
}

static void Led_Init(LedStaticParam_s *config, LED_Type_e LedType)
{
    if (LedType >= LED_NUM) return; 
    // 复制配置
    led[LedType].StaticParam = *config;
	GPIO_Output(config->GPIO_Port, config->GPIO_Pin, BSP_GPIO_SPEED_LOW);
    // 初始化时关闭LED
    SetLedMode(LedType, LED_OFF);
}

void LedDeviceInit(void)
{ 
	LedStaticParam_s config;

	config.GPIO_Port = Balance_GPIO_Port;
	config.GPIO_Pin = Balance_Pin;
	config.ActiveLevel = LED_HIGH_LEVEL_ON;
	Led_Init(&config, LED_BALANCE);

	config.GPIO_Port = BlueTooth_GPIO_Port;
	config.GPIO_Pin = BlueTooth_Pin;
	config.ActiveLevel = LED_HIGH_LEVEL_ON;
	Led_Init(&config, LED_BLUETOOTH);

	config.GPIO_Port = Follow_GPIO_Port;
	config.GPIO_Pin = Follow_Pin;
	config.ActiveLevel = LED_HIGH_LEVEL_ON;
	Led_Init(&config, LED_FOLLOW);
}
