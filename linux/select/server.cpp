#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <sys/time.h>

int main()
{
    auto listen_fd = socket(AF_INET, SOCK_STREAM, 0); //创建监听socket文件
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.204.134", &addr.sin_addr.s_addr);
    addr.sin_port = htons(9999);
    auto bind_key = bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)); //链接地址和端口号
    if (bind_key == -1)
    {
        perror("bind");
        exit(0);
    }
    listen(listen_fd, 128); //设置监听是否连接
    fd_set reads, temp;
    FD_ZERO(&reads);
    FD_SET(listen_fd, &reads);
    int max = listen_fd;
    while (1)
    {
        temp = reads;
        auto select_key = select(max + 1, &temp, nullptr, nullptr, nullptr);
        if (select_key == -1)
        {
            perror("selet:");
            exit(0);
        }
        else
        {
            if (FD_ISSET(listen_fd, &temp))
            {
                sockaddr_in add;
                auto add_len = sizeof(add);
                auto connect_fd = accept(listen_fd, (struct sockaddr *)&add, (socklen_t *)&add_len);
                std::cout << "连接成功...\n";
                FD_SET(connect_fd, &reads);
                max = connect_fd;
            }
            for (int i = listen_fd; i <= max; i++)
            {
                if (FD_ISSET(i, &temp))
                {
                    char buf[1024];
                    auto read_key = read(i, buf, sizeof(buf));
                    if (read_key == -1)
                    {
                        perror("read");
                        break;
                    }
                    else if (read_key == 0)
                    {
                        FD_CLR(i, &reads);
                        close(i);
                        std::cout << "连接断开...\n";
                    }
                    else
                    {
                        std::cout << buf;
                        bzero(buf, sizeof(buf));
                    }
                }
            }
        }
    }
    return 0;
}