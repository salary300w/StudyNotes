/*
#include <sys/types.h>
#include <sys/wait.h>
       pid_t wait(int *wstatus);

       pid_t waitpid(pid_t pid, int *wstatus, int options);
        作用：回收指定进程，可以设置是否阻塞。
        参数：
            pid:
                <-1：回收组id为传入参数绝对值的进程组的子进程；
                -1：回收所有子进程
                0：回收当前进程组的所有子进程。
                >0：表示回收id为pid的子进程。
            wstatus：传入的整型数据的地址，传出参数。
            options：
                0：表示阻塞
                WNOHANG：立即返回（非阻塞）
        返回值：
            >0：返回子进程的id
            =0：options=WNOHANG，表示还有子进程活着
            =-1：错误，或者没有子进程


*/
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
int main()
{
    int pid;
    for (int i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
    }
    if (pid > 0)
    {
        std::cout << "i am father\n"<< getpid() << "\n";
        sleep(1);
    }
    else
    {
        std::cout << "i am child\n"<< getpid() << "\n";
        while(1)
        {
            std::cout<<getpid()<<"\n";
            sleep(1);
        }
    }
    return 0;
}