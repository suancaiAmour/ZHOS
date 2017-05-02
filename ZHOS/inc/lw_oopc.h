// 作者: 高焕堂 金永华 酸菜Amour

#ifndef LW_OOPC_H_INCLUDED_
#define LW_OOPC_H_INCLUDED_

//#define LW_OOPC_USE_STDDEF_OFFSETOF
#define LW_OOPC_USE_USER_DEFINED_OFFSETOF

#ifdef LW_OOPC_USE_STDDEF_OFFSETOF
#include <stddef.h>
#define LW_OOPC_OFFSETOF offsetof
#endif

#ifdef LW_OOPC_USE_USER_DEFINED_OFFSETOF
#define LW_OOPC_OFFSETOF(s,m) (size_t)&(((s*)0)->m)
#endif

void* lw_oopc_malloc(int size, const char* type, const char* describe);
void lw_oopc_free(void* memblock);
void lw_oopc_report(void);

#define lw_oopc_file_line_params const char* describe

#define ABS_CLASS(type)             \
typedef struct type type;           \
void type##_ctor(type* t);          \
void type##_dtor(type* t);          \
void type##_release(type* t);       \
void type##_retain(type* t);        \
struct type                         \
{   								\

#define END_ABS_CLASS };

#define ABS_CTOR(type)              \
void type##_ctor(type* cthis) {

#define END_ABS_CTOR }

// 根类
ABS_CLASS(rootClass)
void *reserve;
END_ABS_CLASS

#define CLASS(type, Father)                 \
typedef struct type type;           \
type* type##_new(lw_oopc_file_line_params); \
void type##_ctor(type* t);          \
void type##_dtor(type* t);          \
void type##_release(type* t);       \
void type##_retain(type *t);        \
struct type                         \
{                                   \
    void (*dealloc)(type* cthis);   \
    struct Father father;			\
	int referenceCount;            	\

#define END_CLASS  };

#define CTOR(type, Father)                              \
type* type##_new(const char* describe)                  \
{            											\
    struct type *cthis = (struct type*)lw_oopc_malloc(sizeof(struct type), #type, describe);   \
    cthis->referenceCount = 1;                   \
    if(!cthis)                                          \
    {                                                   \
        return 0;                                       \
    }                                                   \
    type##_ctor(cthis);                                 \
    return cthis;                                       \
}                                                       \
void type##_release(type* cthis)                        \
{                                                       \
     if(--cthis->referenceCount == 0)                   \
     {                                                  \
         cthis->dealloc(cthis);                         \
         lw_oopc_free(cthis);                           \
     }                                                  \
}                                                       \
void type##_retain(type* cthis)                         \
{                                                       \
     cthis->referenceCount++;                           \
}                                                       \
void type##dealloc11111(type* cthis){}                  \
void type##_ctor(type* cthis) {                         \
    cthis->dealloc = type##dealloc11111;                \
    Father##_ctor(&(cthis->father));

#define END_CTOR	} \

#define FUNCTION_SETTING(f1, f2)	cthis->f1 = f2

#define SUPER_PTR(cthis, Father) ((Father*)(&(cthis->father)))

#define SUPER_PTR_2(cthis, father, grandfather) \
	SUPER_PTR(SUPER_PTR(cthis, father), grandfather)

#define SUPER_PTR_3(cthis, father, grandfather, greatgrandfather) \
	SUPER_PTR(SUPER_PTR_2(cthis, father, grandfather), greatgrandfather)

#define SUB_PTR(selfptr, self, child) \
	((child*)((char*)selfptr - LW_OOPC_OFFSETOF(child, self)))

#define SUB_PTR_2(selfptr, self, child, grandchild) \
	SUB_PTR(SUB_PTR(selfptr, self, child), child, grandchild)

#define SUB_PTR_3(selfptr, self, child, grandchild, greatgrandchild) \
	SUB_PTR(SUB_PTR_2(selfptr, self, child, grandchild), grandchild, greatgrandchild)

#define INHERIT_FROM(cthis, field)	cthis->father.field

#endif
