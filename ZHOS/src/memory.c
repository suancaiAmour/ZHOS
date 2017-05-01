#include "memory.h"
#include <string.h>

// 32 字节对齐 保证首字节地址对齐
__attribute__((aligned(32))) static u8 membase[MEM_MAX_SIZE]; //内存池
static u16 memmapbase[MEM_ALLOC_TABLE_SIZE]; // 内存表

struct _m_mallco_dev
{
    u8 	*membase;
    u16 *memmap;
    u8  memrdy;
};

static struct _m_mallco_dev _mallco_dev=
{
	membase,
	memmapbase,
	0,
};

void mymemcpy(void *des,void *src,u32 n)  
{  
    u8 *xdes=des;
	u8 *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  

void mymemset(void *s,u8 c,u32 count)  
{  
    u8 *xs = s;  
    while(count--)*xs++=c;  
}	   

static void _mem_init(void)
{  
    mymemset(_mallco_dev.memmap, 0,MEM_ALLOC_TABLE_SIZE*2);
	mymemset(_mallco_dev.membase, 0,MEM_MAX_SIZE);
	_mallco_dev.memrdy =1;
}  

u8 mymemperused(void)
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<MEM_ALLOC_TABLE_SIZE;i++)
    {  
        if(_mallco_dev.memmap[i])used++;
    } 
    return (used*100)/(MEM_ALLOC_TABLE_SIZE);
}  

static u32 _mem_malloc(u32 size)
{  
    signed long offset=0;  
    u32 nmemb;
	u32 cmemb=0;
    u32 i;  
    if(!_mallco_dev.memrdy) _mem_init();
    if(size==0)return 0XFFFFFFFF;
    nmemb=size/MEM_BLOCK_SIZE;
    if(size%MEM_BLOCK_SIZE)nmemb++;
    for(offset=MEM_ALLOC_TABLE_SIZE-1;offset>=0;offset--)
    {     
		if(!_mallco_dev.memmap[offset])cmemb++;
		else cmemb=0;
		if(cmemb==nmemb)
		{
            for(i=0;i<nmemb;i++)
            {  
                _mallco_dev.memmap[offset+i]=nmemb;
            }  
            return (offset*MEM_BLOCK_SIZE);
		}
    }  
    return 0XFFFFFFFF;
}  

static u8 _mem_free(u32 offset)
{  
    int i;  
    if(!_mallco_dev.memrdy)
	{
		_mem_init();
        return 1;
    }  
    if(offset<MEM_MAX_SIZE)
    {  
        int index=offset/MEM_BLOCK_SIZE;
        int nmemb=_mallco_dev.memmap[index];
        for(i=0;i<nmemb;i++)
        {  
            _mallco_dev.memmap[index+i]=0;
        }  
        return 0;  
    }else return 2;
}  

void myfree(void *ptr)
{  
	u32 offset;   
	if(ptr==NULL)return;
 	offset=(u32)ptr-(u32)_mallco_dev.membase;
    _mem_free(offset);
}  

void *mymalloc(u32 size)
{  
    u32 offset;   
	offset=_mem_malloc(size);
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)_mallco_dev.membase+offset);
}  

