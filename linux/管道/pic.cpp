/*
实现ps aux|grep xxx 父子进程之前通信
子进程：ps aux，子进程结束后，将数据发送给父进程
父进程：获取数据进行过滤
pipe()
execlp()
*/
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
int main()
{
    int fd[2];
    auto pipe_key = pipe(fd);
    if (pipe_key == -1)
    {
        perror("pipe:");
        exit(0);
    }
    auto fork_key = fork();
    if (fork_key > 0)
    { //父进程
        char buf[1024];
        read(fd[0], buf, sizeof(buf) - 1);
        while(read(fd[0], buf, sizeof(buf) - 1)>0)
        {
            std::cout<<buf<<"\n";
        }
        std::cout << buf << "\n";
    }
    else if (fork_key == 0)
    {
        //子进程
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("execlp:");
        exit(0);
    }
    else
    {
        perror("fork");
        exit(0);
    }

    return 0;
}