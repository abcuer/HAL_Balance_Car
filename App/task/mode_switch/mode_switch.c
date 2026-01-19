#include "mode_switch.h"
#include "mode.h"

void ModeSwitchTask(void const * argument)
{
    for(;;)
    {
        ModeSelect();  // 模式切换、蓝牙解析、超声波避障都在这里面
        
        // 重要：将 ModeSelect 里的延时改为 osDelay
        // 建议 ModeSelect 内部执行频率为 20ms-50ms
        osDelay(20); 
    }
}