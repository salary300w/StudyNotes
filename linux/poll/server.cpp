#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <sys/time.h>
#include <poll.h>

int main()
{
    auto listen_fd = socket(AF_INET, SOCK_STREAM, 0); //创建监听socket文件
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.204.134", &addr.sin_addr.s_addr);
    addr.sin_port = htons(9999);
    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)); //链接地址和端口号
    listen(listen_fd, 128);                                  //设置监听是否连接

    struct pollfd reads[1024];
    for (int i = 0; i < 1024; i++)
    {
        reads[i].fd = -1;
        reads[i].events = POLL_IN;
    }
    reads[0].fd = listen_fd;
    int max = 0;
    while (1)
    {
        auto poll_key = poll(reads, max + 1, -1);
        if (poll_key == -1)
        {
            perror("poll:");
            exit(0);
        }
        if (reads[0].revents & POLLIN)
        {
            sockaddr_in add;
            auto add_len = sizeof(add);
            auto connect_fd = accept(listen_fd, (sockaddr *)&add, (socklen_t *)&add_len);
            std::cout << "连接成功...,connect_fd:" << connect_fd << "\n";
            for (int i = 1; i < 1024; i++)
            {
                if (reads[i].fd == -1)
                {
                    reads[i].fd = connect_fd;
                    reads[i].events = POLLIN;
                    break;
                }
            }
            max = connect_fd > max ? connect_fd : max;
        }
        for (int i = 1; i <= max; i++)
        {
            if (reads[i].revents & POLLIN)
            {
                char buf[1024];
                int len = read(reads[i].fd, buf, sizeof(buf));
                if (len == -1)
                {
                    perror("read");
                    exit(0);
                }
                else if (len == 0)
                {
                    std::cout << "连接断开...connect_fd:"<<reads[i].fd<<"\n";
                    close(reads[i].fd);
                    reads[i].fd = -1;
                }
                else if (len > 0)
                {
                    std::cout << buf;
                    bzero(buf, sizeof(buf));
                }
            }
        }
    }
    return 0;
}