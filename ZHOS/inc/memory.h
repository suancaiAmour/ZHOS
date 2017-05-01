// 作者 正点原子 酸菜Amour

#ifndef __MEMORY_H
#define __MEMORY_H

#include "stm32f10x.h"
#include "ZHOS.h"

#define MEM_BLOCK_SIZE			32 //每个内存块 32 字节
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE

void myfree(void *ptr);
void *mymalloc(u32 size);
void mymemset(void *s,u8 c,u32 count);
void mymemcpy(void *des,void *src,u32 n);
u8 mymemperused(void);
#endif











