#include "ZHOS.h"

void producer(void *args)
{
	ZHOSCond *cond = (ZHOSCond *)args;
	while (true)
	{
		ZHOS.condSignal(cond);
		ZHOS.log("生产者生产一次。\r\n");
		ZHOS.delay(10000);
	}
}

void consumer(void *args)
{
	int result;
	ZHOSCond *cond = (ZHOSCond *)args;
	while (true)
	{
		ZHOS.log("消费者等待生产。\r\n");
		result = ZHOS.condWait(cond, 50000);
		if(result)
		{
			ZHOS.log("超时。\r\n");
		}
		else
		{
			ZHOS.log("消费者消费一次。\r\n");
		}
	}
}


int main(void)
{
	ZHOSCond *cond;
	ZHOSInit();
	cond = ZHOS.createCond(1);
	ZHOS.createTask(consumer, cond);
	ZHOS.createTask(producer, cond);
	ZHOS.switchTask();
	while(1);
}
