#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "lw_oopc.h"

CLASS(ZHQueue, rootClass)
void **cache;
int front;
int count;
int maxCount;
void (*init)(ZHQueue *cthis, int maxCount);
void (*enQueue)(ZHQueue *cthis, void *con);
void *(*deQueue)(ZHQueue *cthis);
void *(*getConWithIndex)(ZHQueue *cthis, unsigned int index);
END_CLASS

#endif
