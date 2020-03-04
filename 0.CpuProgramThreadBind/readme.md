**编译方法：　g++ test.cpp -lpthread

<br>

### 进程绑定cpu逻辑核 程序 
```c
sched_setaffinity(0, sizeof(mask), &mask)
```
此函数的第一个参数如果是０，代表将此进程绑定到指定cpu(mask),mask可以看到是程序中创建线程时候传过来的参数

<br>

### 线程绑定cpu逻辑核　程序
```c
pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
```
此函数的第一个参数表示要绑定的线程的线程号，cpuset代表逻辑cpu
