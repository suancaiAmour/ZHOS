#ifndef __LOG_H
#define __LOG_H	
#include "sys.h" 

void uart_init(u32 bound);

// 注意发送的内容不能超过 100 byte
void ZHLog(char *fmt, ...);

#endif


