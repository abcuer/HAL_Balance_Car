#include "headfile.h"

static SoundLight_t sound_light = {
	.flag = 0, // 声光提示激活标志：1 表示正在进行声光报警，如避障蜂鸣器提醒；0 表示无报警
	.time = 0  // 声光提示计时器：记录声光报警的持续时间，到达设定值后自动关闭蜂鸣器等提示
};

/**
 * @brief 系统初始化函数
 * @param 无
 * @retval 无
 */
void System_Init(void)
{
//  DWT_Init();
  MPU_Init();
  motor_init();
  encoder_init();
  OLED_Init();
  bt_init();
  pid_init(&dist, POSITION_PID, -0.6, 0, 0.1);
}

/**
 * @brief 声光提示启动函数（例如避障触发后报警）
 * @param 无
 * @retval 无
 */
void SoundLight(void)
{
	if(sound_light.flag == 0)
	{
		Buzzer_ON();
		Follow_ON();
		sound_light.flag = 1;
	}
}

/**
 * @brief 声光提示状态更新函数，计时并关闭报警
 * @param 无
 * @retval 无
 */
void UpdateSoundLight(void)
{
    if(sound_light.flag)
    {
        sound_light.time++;

		if(sound_light.time >= 20) 
		{
			Buzzer_OFF();
			Follow_OFF();
			sound_light.time = 0;
			sound_light.flag = 0; 
		}
        
    }
}
