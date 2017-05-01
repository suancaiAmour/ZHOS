#include "ZHOS.h"
#include "log.h"
#include "sys.h"
#include "switch.h"
#include "string.h"

OSClass *pZHOS;

void ZHOSInit(void)
{
	NVIC_Configuration();
	uart_init(LOG_RATE);
	pZHOS = OSClass_new("系统内核");
	SwitchStart();
	pZHOS->log("ZHOS初始化成功\r\n");
}

void SwitchTask(void)
{
	SwitchDelay(0);
}

CTOR(OSClass, rootClass)
FUNCTION_SETTING(log, ZHLog);
FUNCTION_SETTING(createTask, CreateTask);
FUNCTION_SETTING(endTask, TaskEnd);
FUNCTION_SETTING(switchTask, SwitchTask);
FUNCTION_SETTING(delay, SwitchDelay);
END_CTOR
