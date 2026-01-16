#ifndef _encoder_h
#define _encoder_h
#include "tim.h"
#include "motor.h"

void encoder_init(void);
int16_t Encoder_left_Get(void);
int16_t Encoder_right_Get(void);
void UpdateEncoderCounts(void);

extern Motor_t motor_left;
extern Motor_t motor_right;

#endif