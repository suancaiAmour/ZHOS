#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "stdint.h"

void CreateTask(void (*task)(void));
void SwitchDelay(uint16_t Time);
void SwitchStart(void);
void TaskEnd(void);

#endif


