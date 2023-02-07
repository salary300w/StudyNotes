//写一个守护进程，每隔两秒获取一下系统时间，将时间写入至磁盘中

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <string.h>
void mydeal(int num)
{
    auto open_key = open("data.txt", O_CREAT | O_APPEND | O_RDWR, 0777);
    char buf[1024] = {"12345"};
    write(open_key, buf, strlen(buf));
    close(open_key);
}
int main()
{
    auto fork_key = fork();
    if (fork_key > 0)
    {
        std::cout << "父进程退出\n";
        exit(0);
    }
    //创建会话
    auto set_key = setsid();
    if (set_key == -1)
    {
        perror("setsid:");
        exit(0);
    }
    //设置umask
    umask(0000);

    //重定向标准输入输出流
    auto fd=open("/dev/null",O_RDWR);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDERR_FILENO);
    
    //信号捕捉
    struct sigaction sig_set;
    sig_set.sa_handler = mydeal;
    sig_set.sa_flags = 0;
    sigemptyset(&sig_set.sa_mask);
    sigaction(SIGALRM, &sig_set, NULL);

    //定时器设置
    struct itimerval timer_Set;
    timer_Set.it_interval.tv_sec = 2;
    timer_Set.it_interval.tv_usec = 0;
    timer_Set.it_value.tv_sec = 2;
    timer_Set.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer_Set, NULL);
    while(1)
    {
        sleep(100);
    }
    return 0;
}
