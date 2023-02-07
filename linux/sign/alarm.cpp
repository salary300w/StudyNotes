/*
    #include <unistd.h>
       unsigned int alarm(unsigned int seconds);
        作用：设置定时器（闹钟），倒计时结束时，函数给当前进程发送信号：SIGALARM
        参数：seconds，倒计时市场，单位秒，为0时，倒计时无效
        返回值：倒计时剩余的时间
    SIGALARM：默认终止当前进程，每一个进程都有且只有唯一的一个定时器，定义新的alarm函数会覆盖之前的alarm函数
*/
#include <unistd.h>
#include <iostream>
int main()
{
    alarm(1);
    int i = 1;
    while (1)
    {
        std::cout << i << "\n";
        i++;
    }

    return 0;
}