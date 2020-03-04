#include <time.h>  
#include <sys/time.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <math.h> 
#include <stdio.h>
      
#define DWORD unsigned long  
#define UINT64 unsigned long long  
const double SPLIT = 0.01;  
const int COUNT = 200;  
const double PI = 3.14159265;  
const int INTERVAL = 300;  　　　　　　//看后面程序你就知道，busy+idle＝300ms

int main(int argc, char* argv[])  
{  
	struct timeval tms;  
	DWORD busySpan[COUNT];  
	DWORD idleSpan[COUNT];  
	int half = INTERVAL/2, i;  
	double radian = 0.0;  


	for(i = 0; i < COUNT; ++i)  
	{  
	   busySpan[i] = (DWORD)(half + (sin(PI * radian) * half));  
	   idleSpan[i] = INTERVAL - busySpan[i];  
	   radian += SPLIT;  
	   //printf("looptime=%d, busySpan=%d ,sin():%f ,idleSpan=%d ,radian=%f   \n",i,busySpan[i],sin(PI * radian) * half,idleSpan[i],radian);
	}  

	clock_t startTime = 0;  
	int j = 0;  
	while(1)  
	{  
	   j = j % COUNT;  
	   timerclear(&tms);  
	   gettimeofday(&tms,NULL);  //gettimeofday(&tms,NULL)　返回该进程从启动到现在经历的毫秒数 
	   UINT64 startTime = tms.tv_usec; //获取的是微妙级
	   
	   while(1)
	   {  
	       timerclear(&tms);  
	       gettimeofday(&tms,NULL);  
	       UINT64 nowTime = tms.tv_usec;  
	       if((nowTime - startTime)/1000 > busySpan[j]) //等待忙够设定的时间（因为nowTime，startTime是微妙，所以要除以1000, 至少要循环 busySpan[j]ms 时间）
	       {
			//printf("-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n-----------------------------------busy finish\n"); 
 			break; 
	       }
		   
	       //printf("nowTime=%d  startTime=%d Time-DValue:%d busySpan=%d\n",nowTime,startTime,(nowTime - startTime)/1000,busySpan[j]);
	   }  
	       if(usleep(idleSpan[j]*1000))  //空闲时间
		   exit(-1);  
	   j++;  
	}  
	return 0;  
}
