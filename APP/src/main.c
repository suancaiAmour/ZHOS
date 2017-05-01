#include "ZHOS.h"

void Task0(void)
{
   while(1)
   {
	 ZHOS.log("任务0\r\n");
	 ZHOS.delay(2000);
   }
}

void Task3(void)
{
	while(1)
	{
		ZHOS.log("任务3\r\n");
		ZHOS.delay(1000);
	}
}

void Task2(void)
{
	
	ZHOS.createTask(Task3);
	while(1)
	{
		lw_oopc_report();
		ZHOS.delay(10000);
	}
}

void Task4(void)
{
	while(1)
	{
		ZHOS.log("张鸿是帅哥。\r\n");
		ZHOS.delay(500);
	}
}


void Task1(void)
{
   ZHOS.createTask(Task2);
	ZHOS.createTask(Task4);
   while(1)
   {
	   ZHOS.log("任务1\r\n");
	   ZHOS.delay(5000);
   }
}



int main(void)
{
	ZHOSInit();
	ZHOS.createTask(Task0);
	ZHOS.createTask(Task1);
	ZHOS.switchTask();
	while(1);
}
