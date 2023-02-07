#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>

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
    { //打开管道
        auto open_key = open("fifo1", O_WRONLY);
        if (open_key == -1)
        {
            perror("open:");
            exit(0);
        }

        for (int i = 0; i < 100; i++)
        {
            char buf[1024];
            sprintf(buf, "hello,%d\n", i);
            write(open_key, buf, strlen(buf));
            std::cout << buf << "\n";
            sleep(1);
        }
        close(open_key);
    }
    return 0;
}