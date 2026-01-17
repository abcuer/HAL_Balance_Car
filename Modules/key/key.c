#include "key.h"
#include "gpio.h"

KEYInstance key[KEY_NUM];

/**
 * @brief 按键初始化
 * @param instance 按键实例指针
 * @param DevNum 设备编号
 */
static void Key_Init(KEYInstance *instance, uint8_t DevNum)
{
    if (DevNum >= KEY_NUM) return;
    
    // 复制配置
    key[DevNum].GPIO_Port = instance->GPIO_Port;
    key[DevNum].GPIO_Pin = instance->GPIO_Pin;
    key[DevNum].Level = instance->Level;
    key[DevNum].Mode = instance->Mode;
    key[DevNum].LastPressTime = 0;
    key[DevNum].LastState = KEY_RELEASED;
}

/**
 * @brief 按键设备初始化
 */
void KeyDeviceInit(void)
{
    KEYInstance userKey =
    {
        .GPIO_Port = KEY_GPIO_Port, 
        .GPIO_Pin = KEY_Pin, 
        .Level = 0,         
        .Mode = KEY_MODE_NORMAL
    };  
    
    Key_Init(&userKey, KEY_USER);
}

/**
 * @brief 获取按键当前状态（带消抖）
 * @param KeyType 按键类型索引
 * @return 按键当前状态（KEY_PRESSED 或 KEY_RELEASED）
 */
static KEY_State_e Key_GetState(uint8_t KeyType)
{
    if (KeyType >= KEY_NUM) return KEY_RELEASED;
    
    GPIO_PinState pinState = HAL_GPIO_ReadPin(key[KeyType].GPIO_Port, key[KeyType].GPIO_Pin);
    KEY_State_e currentState;
    
    if (key[KeyType].Level) 
    {
        // 高电平按下有效
        currentState = (pinState == GPIO_PIN_SET) ? KEY_PRESSED : KEY_RELEASED;
    }
    else
    {
        // 低电平按下有效
        currentState = (pinState == GPIO_PIN_RESET) ? KEY_PRESSED : KEY_RELEASED;
    }
    
    return currentState;
}

/**
 * @brief 获取按键按下事件（检测上升沿/下降沿）
 * @param KeyType 按键类型索引
 * @return 1:检测到按键按下事件，0:无按键事件
 */
uint8_t Key_GetNum(uint8_t KeyType)
{
    if (KeyType >= KEY_NUM) return 0;
    
    static KEY_State_e key_pre[KEY_NUM];  // 上一次按键状态
    uint8_t key_pressed = 0;
    
    KEY_State_e LastState = Key_GetState(KeyType);
    
    if (key_pre[KeyType] == KEY_RELEASED && LastState == KEY_PRESSED)
    {
        // 检测到由松开变按下（下降沿）
        key_pressed = 1;
    }
    
    key_pre[KeyType] = LastState; // 更新上一次状态
    return key_pressed;
}

/**
 * @brief 判断按键是否处于按下状态
 * @param KeyType 按键类型索引
 * @return 1:按下状态，0:释放状态
 */
static uint8_t Key_IsPressed(uint8_t KeyType)
{
    if (KeyType >= KEY_NUM) return 0;
    
    return (Key_GetState(KeyType) == KEY_PRESSED);
}

/**
 * @brief 判断按键是否长按
 * @param KeyType 按键类型索引
 * @param holdTime_ms 长按判定时间（毫秒）
 * @return 1:长按事件，0:非长按
 */
static uint8_t Key_IsLongPressed(uint8_t KeyType, uint32_t holdTime_ms)
{
    if (KeyType >= KEY_NUM) return 0;
    
    static uint32_t pressStartTime[KEY_NUM] = {0};
    static uint8_t isCounting[KEY_NUM] = {0};
    
    KEY_State_e currentState = Key_GetState(KeyType);
    
    if (currentState == KEY_PRESSED)
    {
        if (!isCounting[KeyType])
        {
            // 开始计时
            pressStartTime[KeyType] = HAL_GetTick();
            isCounting[KeyType] = 1;
        }
        else
        {
            // 检查是否达到长按时间
            if (HAL_GetTick() - pressStartTime[KeyType] >= holdTime_ms)
            {
                isCounting[KeyType] = 0;
                return 1;
            }
        }
    }
    else
    {
        // 按键释放，重置计时
        isCounting[KeyType] = 0;
    }
    
    return 0;
}

/**
 * @brief 按键扫描函数（需要在主循环中周期性调用）
 * @param KeyType 按键类型索引
 * @return 按键事件标志
 *         0x00: 无事件
 *         0x01: 短按事件
 *         0x02: 长按事件
 *         0x04: 连按事件
 */
static uint8_t Key_Scan(uint8_t KeyType)
{
    if (KeyType >= KEY_NUM) return 0;
    
    static uint8_t keyFlags[KEY_NUM] = {0};
    uint8_t event = 0;
    
    // 检测短按（快速按下并释放）
    if (Key_GetNum(KeyType))
    {
        event |= 0x01;  // 短按标志
    }
    
    // 检测长按（持续按下500ms）
    if (Key_IsLongPressed(KeyType, 500))
    {
        event |= 0x02;  // 长按标志
    }
    
    // 检测连按（连按模式下）
    if (key[KeyType].Mode == KEY_MODE_CONTINUOUS && Key_IsPressed(KeyType))
    {
        static uint32_t lastRepeatTime[KEY_NUM] = {0};
        uint32_t currentTime = HAL_GetTick();
        
        // 首次按下或连续按下间隔时间到
        if (lastRepeatTime[KeyType] == 0 || 
            (currentTime - lastRepeatTime[KeyType]) > 200)  // 200ms连按间隔
        {
            lastRepeatTime[KeyType] = currentTime;
            event |= 0x04;  // 连按标志
        }
    }
    else
    {
        // 按键释放，重置连按计时
        static uint32_t lastRepeatTime[KEY_NUM] = {0};
        lastRepeatTime[KeyType] = 0;
    }
    
    keyFlags[KeyType] = event;
    return event;
}