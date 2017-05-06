#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "stdint.h"
#include "ZHOS.h"

void CreateTask(void (*task)(void *), void *env);
void CreateTaskWithTackDeep(void (*task)(void *), void *env, uint32_t tackDeep);
void SwitchDelay(uint16_t Time);
void SwitchStart(void);
void TaskEnd(void);
uint64_t getOSTickTime(void);

ZHOSCond *createCond(int condNum);
void releaseCond(ZHOSCond *cond);
void condSignal(ZHOSCond *cond);
int condWait(ZHOSCond *cond, int64_t waitTime);

#endif


