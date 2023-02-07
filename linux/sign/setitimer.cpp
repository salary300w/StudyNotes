/*
#include <sys/time.h>
       int getitimer(int which, struct itimerval *curr_value);

       int setitimer(int which, const struct itimerval *new_value,struct itimerval *old_value);
       作用：设置定时器，替代alarm，单位是微秒，实现周期性定时
       参数：
            which：定时器以什么时间记时
                ITIMER_REAL :真实时间，时间到达，发送SIGALRM信号 常用
                ITIMER_VIRTUAL:用户时间，时间到达，发送SIGVTALRM信号
                ITIMER_PROF:以该进程在用户态和内核态所消耗的时间来计算，时间到达发送SIGPROF信号
            new_value：设置定时器的属性
                struct itimerval { //定时器的结构体
                    struct timeval it_interval;  //每个间隔的时间 Interval for periodic timer
                    struct timeval it_value;     //延时多长时间执行 Time until next expiration
                    };
                struct timeval { //时间的结构体
                    time_t      tv_sec;          seconds
                    suseconds_t tv_usec;        microseconds
                    };
            old_value：记录上一次定时的时间参数，一般不使用，指定NULL
        返回值：
            成功：0
            失败：-1
*/
#include <sys/time.h>
#include <iostream>
int main()
{
    itimerval *timer_set;
    timer_set->it_interval.tv_sec = 2;
    timer_set->it_interval.tv_usec = 0;
    timer_set->it_value.tv_sec = 3;
    timer_set->it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, timer_set, NULL);
    char num;
    std::cin >> num;
    return 0;
}