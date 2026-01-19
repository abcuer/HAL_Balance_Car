#ifndef _mode_h
#define _mode_h
#include "stdint.h"
#include "motor.h"
#include "control.h"
#include "mpu6050.h"

#define LIFT_ANGLE_THRESHOLD  40.0f    // Pitch 大于这个角度判断为拿起
#define LIFT_GYRO_THRESHOLD   150       // 陀螺仪 y 轴角速度
#define PUTDOWN_ANGLE_THRESHOLD 20.0f  // Pitch 小于这个角度认为可能已放下
#define PUTDOWN_WAIT_COUNT    30       // 放下后静止时间（例如 50 * 5ms = 250ms）

void Balance(void);
void ModeSelect(void);
void CheckLiftState(void);
void DetectPutDown(void);
void CheckFallDown(void);
void ObstacleAvoid(void);
typedef struct{
	uint8_t flag;
	uint16_t time;
} SoundLight_t;

typedef struct {
    uint8_t mode;              // 当前工作模式: 0 平衡模式，1 蓝牙遥控，2 超声波跟随
    uint8_t balance_enable;    // 平衡控制使能：1 开启，0 暂停
    uint8_t lifted_flag;       // 提起标志位：1 表示小车被提起，0 表示正常运行
    uint16_t putdown_counter;  // 放下计数器
    uint16_t lifted_counter;   // 提起计数器
} BalanceState_t;

extern BalanceState_t balance_state;
extern uint8_t obstacle_blocked;

#endif
