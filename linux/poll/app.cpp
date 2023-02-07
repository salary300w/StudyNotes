#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

int main()
{
    auto connect_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.204.134", &addr.sin_addr.s_addr);
    addr.sin_port = htons(9999);
    auto connect_key = connect(connect_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (connect_key == -1)
    {
        std::cout << "连接失败...\n";
        exit(0);
    }
    std::cout << "连接成功...connect_fd:" << connect_fd << "\n";
    char write_buf[1024];
    while (1)
    {
        std::cin>>write_buf;
        strcat(write_buf,"\n");
        auto write_key = write(connect_fd, write_buf, strlen(write_buf));
        if (write_key == -1)
        {
            perror("write:");
            exit(0);
        }
        bzero(write_buf,sizeof(write_buf));
    }
    return 0;
}