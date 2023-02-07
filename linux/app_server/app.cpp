#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    auto connect_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.204.133", &addr.sin_addr.s_addr);
    addr.sin_port = (htons(9999));
    connect(connect_fd, (struct sockaddr *)&addr, sizeof(addr));
    char write_buf[1024];
    char read_buf[1024];
    while (1)
    {
        std::cin >> write_buf;
        if (strlen(write_buf) > 0)
        {
            auto write_key = write(connect_fd, &write_buf, strlen(write_buf));
            bzero(write_buf, sizeof(write_buf));
        }
        auto read_key = read(connect_fd, &read_buf, sizeof(read_buf));
        if (read_key > 0)
        {
            std::cout << "返回的数据为：" << read_buf << "\n";
            bzero(read_buf, sizeof(read_buf));
        }
        else if (read_key == -1)
            break;
    }

    return 0;
}