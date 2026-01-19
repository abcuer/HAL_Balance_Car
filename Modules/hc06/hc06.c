#include "headfile.h"

static RX_DATA_t rx_data;
static BT_Command_t bt_cmd;      // 蓝牙命令结构体

void HC06_Init(void)
{
	HAL_UART_Receive_IT(&huart2, &rx_data.data, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)   // 判断是USART2触发的回调
    {
        switch(rx_data.data)
        {
            case 0x00: bt_cmd.forward=0; bt_cmd.backward=0; bt_cmd.left=0; bt_cmd.right=0; break;
            case 0x01: bt_cmd.forward=1; bt_cmd.backward=0; bt_cmd.left=0; bt_cmd.right=0; break; //前
            case 0x05: bt_cmd.forward=0; bt_cmd.backward=1; bt_cmd.left=0; bt_cmd.right=0; break; //后
            case 0x03: bt_cmd.forward=0; bt_cmd.backward=0; bt_cmd.left=1; bt_cmd.right=0; break; //左
            case 0x07: bt_cmd.forward=0; bt_cmd.backward=0; bt_cmd.left=0; bt_cmd.right=1; break; //右
            case 0x08: bt_cmd.forward=1; bt_cmd.backward=0; bt_cmd.left=1; bt_cmd.right=0; break; //左前
            case 0x02: bt_cmd.forward=1; bt_cmd.backward=0; bt_cmd.left=0; bt_cmd.right=1; break; //右前
            case 0x06: bt_cmd.forward=0; bt_cmd.backward=1; bt_cmd.left=1; bt_cmd.right=0; break; //左后
            case 0x04: bt_cmd.forward=0; bt_cmd.backward=1; bt_cmd.left=0; bt_cmd.right=1; break; //右后
            default:   bt_cmd.forward=0; bt_cmd.backward=0; bt_cmd.left=0; bt_cmd.right=0; break;
        }

        rx_data.flag = 1;  // 标记接收完成

        // 重新打开中断接收，否则只会触发一次
        HAL_UART_Receive_IT(&huart2, &rx_data.data, 1);
    }
}

/**
 * @brief 蓝牙遥控模式控制逻辑
 * @param 无
 * @retval 无
 * @note 根据前后左右命令调整目标速度与转向速度
 */
void BlueTooth(void)
{
    // 1. 优先判断组合指令（只有这样组合键才会生效）
    if(bt_cmd.forward && bt_cmd.left)        { speed_pid.speed = MAX_Speed-10;  turn_pid.speed = MAX_Turn; }
    else if(bt_cmd.forward && bt_cmd.right)  { speed_pid.speed = MAX_Speed+10;  turn_pid.speed = -MAX_Turn;  }
    else if(bt_cmd.backward && bt_cmd.left)  { speed_pid.speed = -MAX_Speed+10; turn_pid.speed = -MAX_Turn; }
    else if(bt_cmd.backward && bt_cmd.right) { speed_pid.speed = -MAX_Speed-10; turn_pid.speed = MAX_Turn;  }
    
    // 2. 再判断单一方向指令
    else if(bt_cmd.forward)  { speed_pid.speed = MAX_Speed+3;  turn_pid.speed = 0; }
    else if(bt_cmd.backward) { speed_pid.speed = -MAX_Speed-3; turn_pid.speed = 0; }
    else if(bt_cmd.left)     { speed_pid.speed = 0;          turn_pid.speed = -25; }
    else if(bt_cmd.right)    { speed_pid.speed = 0;          turn_pid.speed = 25;  }
    else 
    {
        speed_pid.speed = 0;
        turn_pid.speed = 0;
    }
}