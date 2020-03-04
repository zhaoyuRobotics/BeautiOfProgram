## 1.CpuLine.cpp 程序说明

**我的电脑主频是1.6Ghz, 1.6*10的９次方个始终周期每秒，现在cpu每个时钟周期可以执行两条以上汇编代码，我们取平均两条，于是有（１６００００００００＊２）／５＝５４０００００００（循环/秒）,除以５是因为for循环执行了五条汇编代码。我们不能简单的循环540000000次，然后sleep１秒，cpu波形很可能就是先达到峰值（>50%）,然后跌到一个很低的占用率（锯齿状）。我们缩小两个数量级（１０ｍｓ左右，正好是时间片段大小），这样我们看到的ｃｐｕ曲线效果大概就是百分之50附近。因为还有其他程序在运行，所以还需要微调。
 查看方式：cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c**
 
## CpuSinLine.cpp　程序说明
 此程序的大概意思是选定300ms为一个周期， busy time 和　idle　time加起来总共是 300 ms ．然后 busy time 和　idle　time 之间的加减数是一个sin值. 此值会赋给while循环（空循环，判断　时间的差值　和 busy time 的值）和　usleep(此线程睡眠）
 
#### 以下程序罗列了linux下时间的程序获取部分
```C
#include <time.h>  
#include <sys/time.h>  

#define UINT64 unsigned long long  

struct timeval tms;  
clock_t startTime = 0;  
timerclear(&tms);  
gettimeofday(&tms,NULL);  　　　//gettimeofday(&tms,NULL)　返回该进程从启动到现在经历的毫秒数 
UINT64 startTime = tms.tv_usec; //获取的是微妙级
if((nowTime - startTime)/1000 > busySpan[j]) //等待忙够设定的时间（因为nowTime，startTime是微妙，所以要除以1000, 至少要循环 busySpan[j]ms 时间）
```
 
 
