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
    auto access1_key = access("pipe_user1_write", F_OK);
    auto access2_key = access("pipe_user2_write", F_OK);
    if (access1_key == -1)
    {
        std::cout << "管道不存在，创建管道！\n";
        int pipefd[2];
        auto pipe_key = mkfifo("pipe_user1_write", 0664);
        if (pipe_key == -1)
        {
            perror("pipe:");
            exit(0);
        }
    }
    if (access2_key == -1)
    {
        std::cout << "管道不存在，创建管道！\n";
        int pipefd[2];
        auto pipe_key = mkfifo("pipe_user2_write", 0664);
        if (pipe_key == -1)
        {
            perror("pipe:");
            exit(0);
        }
    }

    auto fork_key = fork();
    if (fork_key > 0)
    {
        auto open_key_write = open("pipe_user2_write", O_WRONLY);
        if (open_key_write == -1)
        {
            perror("open:");
            exit(0);
        }
        char buf_write[1024];
        while (1)
        {
            std::cin >> buf_write;
            write(open_key_write, buf_write, strlen(buf_write));
            memset(buf_write, '\0', sizeof(buf_write));
        }
        close(open_key_write);
    }
    else if (fork_key == 0)
    {
        auto open_key_read = open("pipe_user1_write", O_RDONLY);
        if (open_key_read == -1)
        {
            perror("open:");
            exit(0);
        }
        char buf_read[1024];
        while (1)
        {
            auto read_key = read(open_key_read, buf_read, sizeof(buf_read));
            if (read_key != 0)
            {
                std::cout << buf_read << "\n";
                memset(buf_read, '\0', sizeof(buf_read));
            }
        }
    }
    else
    {
        perror("fork:");
        exit(0);
    }
    return 0;
}