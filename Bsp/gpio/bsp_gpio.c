#include "bsp_gpio.h"

/**
 * @brief  内部私有函数：根据 GPIOx 自动开启对应的 RCC 时钟
 * @note   HAL库中时钟开启通常使用宏定义
 */
void GPIO_SetClock(GPIO_TypeDef* GPIOx, FunctionalState state)
{
    if (state == DISABLE) return; // HAL库通常不通过此统一接口关闭时钟，此处仅实现开启

    if      (GPIOx == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (GPIOx == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (GPIOx == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (GPIOx == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
#ifdef GPIOE
    else if (GPIOx == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
#endif
}

/**
 * @brief  通用的推挽输出初始化
 */
void GPIO_Output(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Speed_e speed)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 1. 开启时钟
    GPIO_SetClock(GPIOx, ENABLE);

    // 2. 配置参数
    GPIO_InitStruct.Pin   = GPIO_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; // 标准推挽输出
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = (uint32_t)speed;
    
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/**
 * @brief  通用的输入初始化
 * @param  mode: GPIO_MODE_INPUT, GPIO_MODE_IT_RISING 等
 */
void GPIO_Input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 1. 开启时钟
    GPIO_SetClock(GPIOx, ENABLE);

    // 2. 配置参数
    GPIO_InitStruct.Pin  = GPIO_Pin;
    GPIO_InitStruct.Mode = mode;
    // 输入模式下的上下拉逻辑
    if (mode == GPIO_MODE_INPUT) {
        GPIO_InitStruct.Pull = GPIO_PULLUP; // 默认为上拉，可根据需要调整
    }

    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}