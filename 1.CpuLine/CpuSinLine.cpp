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
const int INTERVAL = 300;  

int main(int argc, char* argv[] )  
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
}  
clock_t startTime = 0;  
int j = 0;  
while(1)  
{  
   j = j % COUNT;  
   timerclear(&tms);  
   gettimeofday(&tms,NULL);  
   UINT64 startTime = tms.tv_usec;  
   while(1)//clock返回该进程从启动到现在经历的毫秒数（千分之一秒）  
   {  
       timerclear(&tms);  
       gettimeofday(&tms,NULL);  
       UINT64 nowTime = tms.tv_usec;  
       if((nowTime - startTime)/1000 > busySpan[j])  
           break;  
       printf("nowTime=%d  startTime=%d  busySpan=%d\n",nowTime,startTime,busySpan[j]);
   }  
       if(usleep(idleSpan[j]*1000))  //精确到微秒（百万分之一秒）的函数  
           exit(-1);  
   j++;  
}  
return 0;  
}
