#ifndef _motor_h
#define _motor_h

#include "stdint.h"

typedef struct{
	uint8_t dir;
	int16_t encoder;
} Motor_t;

void Motor_Init(void);
void MotorSetDuty(int16_t dutyL, int16_t dutyR);
void MotorStop(void);

extern Motor_t motor_left;
extern Motor_t motor_right;
extern uint8_t stop_flag;
#endif