#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <sys/time.h>
#include <sys/epoll.h>

int main()
{
    auto listen_fd = socket(AF_INET, SOCK_STREAM, 0); //创建监听socket文件
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.204.134", &addr.sin_addr.s_addr);
    addr.sin_port = htons(9999);
    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)); //链接地址和端口号
     if(bind_key==-1)
    {
        perror("bind");
        exit(0);
    }
    listen(listen_fd, 128);                                  //设置监听是否连接

    auto epoll_fd = epoll_create(1);
    struct epoll_event ep;
    ep.data.fd = listen_fd;
    ep.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ep);
    while (1)
    {
        struct epoll_event ep_change[1024];
        auto epoll_key = epoll_wait(epoll_fd, ep_change, 1024, -1);
        if (epoll_key == -1)
        {
            perror("epoll:");
            exit(0);
        }
        else
        {
            for (int i = 0; i < epoll_key; i++)
            {
                if (ep_change[i].data.fd == listen_fd)
                {
                    sockaddr_in add;
                    auto add_len = sizeof(add);
                    auto connect_fd = accept(listen_fd, (sockaddr *)&add, (socklen_t *)&add_len);
                    std::cout << "连接成功...\n";
                    struct epoll_event ep;
                    ep.data.fd = connect_fd;
                    ep.events = EPOLLIN;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &ep);
                }
                else
                {
                    char buf[1024];
                    read(ep_change[i].data.fd, buf, sizeof(buf));
                    std::cout << buf;
                    bzero(buf, sizeof(buf));
                }
            }
        }
    }
    return 0;
}