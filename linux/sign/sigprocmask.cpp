/*
#include <signal.h>

    Prototype for the glibc wrapper function 
       int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
       参数：
            how：如何对阻塞信号集处理
                SIG_BLOCK:将用户设置的阻塞信号集添加到内核中，内核中原来数据不变
                SIG_UNBLOCK：根据用户设置的数据，对内核中数据进行解除阻塞
            set：已经初始化的用户自定义信号集
            oldset：保存的之前内核中的阻塞信号集的状态，可以是null
        返回值：成功为0.失败-1
    #include <signal.h>
    int sigpending(sigset_t *set);
    作用：获取内核中的未决信号集
    参数：set，传出参数，保存未决信号集中的信息
*/
#include <signal.h>
#include <iostream>
#include <unistd.h>
int main()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGALRM);
    //sigprocmask(SIG_BLOCK,&set,NULL);
    alarm(1);
    int i = 1;
    while (1)
    {
        std::cout << i << "\n";
        i++;
    }
    return 0;
}