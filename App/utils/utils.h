#ifndef __UTILS_H__
#define __UTILS_H__
#include "pid.h"

void System_Init(void);
void SoundLight(void);
void UpdateSoundLight(void);

extern PID_t dist;

#endif
