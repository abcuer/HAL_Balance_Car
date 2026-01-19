#ifndef __CTRL_TASK_H
#define __CTRL_TASK_H
#include "cmsis_os.h"

void CtrlTask(void const * argument);

extern osSemaphoreId BinarySem_MPUHandle;

#endif