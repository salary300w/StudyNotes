/*
    创建fifo文件
    1、通过命令：mkfifo 名字
    2、通过函数：int mkfifo
    #include <sys/types.h>
    #include <sys/stat.h>

    int mkfifo(const char *pathname, mode_t mode);
    参数：
        pathname：路径
        mode：文件的权限 和open的mode相同
     返回值：成功为0 失败为-1
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
int main()
{
    //判断文件是否存在
    auto access_key = access("fifo1", F_OK);
    if (access_key == -1)
    {
        std::cout << "管道不存在";
        auto pipe_key = mkfifo("fifo1", 0664);
        if (pipe_key == -1)
        {
            perror("pipe:");
            exit(0);
        }
    }
    else
    {
        std::cout << "管道存在";
        exit(0);
    }

    return 0;
}