/*
#include <unistd.h>

int pipe(int pipefd[2]);

作用：创建一个匿名管道，用来进行进程间通信
参数：peprfd[2]是一个传出参数
    peprfd[0]:管道读端
    peprfd[1]:管道写端
返回值：成功返回0，失败返回-1

管道默认阻塞，管道无数据，read阻塞。管道满，write阻塞。
*/

#include <unistd.h>
#include <iostream>
//子进程给父进程发送数据。
int main()
{
    int pipefd[2];
    auto pipe_sign = pipe(pipefd);
    if (pipe_sign == -1)
    {
        perror("pipe:");
        return 0;
    }
    auto fork_sign = fork();
    if (fork_sign > 0)
    {
        //关闭读端
        close(pipefd[0]);
        char message[] = "hello,i am father!";
        write(pipefd[1], message, sizeof(message));
    }
    else
    {
        //关闭写端
        close(pipefd[1]);
        char buf[1024];
        read(pipefd[0], buf, sizeof(buf));
        std::cout << "child get message form father:" << buf << "\n";
    }

    return 0;
}