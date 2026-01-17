#ifndef __HC_SR04_H
#define __HC_SR04_H
#include "stdint.h"

// 初始化
void HCSR04_Init(void);
void HCSR04_GetValue(void);

extern uint16_t distance;

#endif