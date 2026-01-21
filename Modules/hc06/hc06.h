#ifndef _hc06_h
#define _hc06_h
#include "stdint.h"

#define MAX_Speed 18
#define MAX_Turn 30

typedef struct
{
	uint8_t forward;
    uint8_t backward;
    uint8_t left;
    uint8_t right;
} BT_Command_t;

typedef struct
{
    uint8_t data;
    uint8_t flag;
} RX_DATA_t;

void HC06_Init(void);
void BlueTooth(void);

#endif