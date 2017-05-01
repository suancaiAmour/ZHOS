// 作者: 高焕堂 金永华 酸菜Amour

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lw_oopc.h"
#include "memory.h"

#include "log.h"

#define lw_oopc_dbginfo ZHLog

typedef struct LW_OOPC_MemAllocUnit
{
    char *describe;
    void *addr;                   
    int size;
    struct LW_OOPC_MemAllocUnit* next;     
} LW_OOPC_MemAllocUnit;

static LW_OOPC_MemAllocUnit* lw_oopc_memAllocList = 0;

void* lw_oopc_malloc(int size, const char* type, const char* describe)
{
    void* addr = mymalloc(size);
    if (addr != 0)
    {
        LW_OOPC_MemAllocUnit* pMemAllocUnit = mymalloc(sizeof(LW_OOPC_MemAllocUnit));
        if (!pMemAllocUnit)
        {
            lw_oopc_dbginfo("lw_oopc: error! malloc alloc unit failed.\r\n");
        }
		
		pMemAllocUnit->describe = mymalloc(strlen(describe));
        strcpy(pMemAllocUnit->describe, describe);
        pMemAllocUnit->addr = addr;
        pMemAllocUnit->size = size;
        pMemAllocUnit->next = lw_oopc_memAllocList;
        lw_oopc_memAllocList = pMemAllocUnit;

        lw_oopc_dbginfo("lw_oopc: alloc memory in %p, size: %d, object type: %s, describe: %s\r\n", addr, size, type, describe);
    }

    return addr;
}

void lw_oopc_free(void* memblock)
{
    LW_OOPC_MemAllocUnit* prevUnit = 0;
    LW_OOPC_MemAllocUnit* currUnit = lw_oopc_memAllocList;

    while(currUnit != 0)
    {
        if (currUnit->addr == memblock)
        {
            lw_oopc_dbginfo("lw_oopc: free memory in %p, size: %d\r\n", currUnit->addr, currUnit->size);
            if (prevUnit == 0)
            {
                lw_oopc_memAllocList = currUnit->next;
            }
			else
			{
				prevUnit->next = currUnit->next;
			}
            
			goto over; // 统一资源释放出口
        }
        else
        {
            prevUnit = currUnit;
            currUnit = currUnit->next;
        }
    }

    if (currUnit == 0)
    {
        lw_oopc_dbginfo("lw_oopc: error! you attemp to free invalid memory.\r\n");
		return;
    }
	
over:
	myfree(currUnit->describe);
	myfree(currUnit->addr);
	myfree(currUnit);
	currUnit = NULL;
	return;
	
}

void lw_oopc_report(void)
{
    
    LW_OOPC_MemAllocUnit* currUnit = lw_oopc_memAllocList;

    if (currUnit != 0)
    {
        while(currUnit != 0)
        {
            lw_oopc_dbginfo("memory leak in: %p, size: %d, describe: %s\r\n", currUnit->addr, currUnit->size, currUnit->describe);
            currUnit = currUnit->next;
        }
    }
    else
    {
        lw_oopc_dbginfo("lw_oopc: no memory leak.\r\n");
    }
	
	lw_oopc_dbginfo("used memory: %d%%, all memory: %dKb\r\n", mymemperused(), MEM_MAX_SIZE / 1024);
}


// 根类
ABS_CTOR(rootClass)
END_ABS_CTOR
