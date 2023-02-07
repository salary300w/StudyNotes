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
    auto open_key = open("fifo1", O_RDONLY);
    if (open_key == -1)
    {
        perror("open:");
        exit(0);
    }
    char buf[1024];
    while (1)
    {
        auto read_key=read(open_key, buf, sizeof(buf));
        if(read_key==0)
        {
            std::cout<<"写端断开了";
            exit(0);
        }
        std::cout << buf;
        sleep(1);
    }
    close(open_key);
    return 0;
}
