#ifndef __PID_h_
#define __PID_h_
#include "stdint.h"

enum
{
  POSITION_PID = 0,  // 位置式
  DELTA_PID,         // 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}PID_t;

void pid_init(PID_t *pid, uint32_t mode, float p, float i, float d);
void pid_cal(PID_t *pid);
void pidout_limit(PID_t *pid);

#endif

