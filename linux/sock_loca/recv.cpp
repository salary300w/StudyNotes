#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <sys/time.h>
#include <sys/un.h>

int main()
{
    auto lis_fd = socket(AF_UNIX, SOCK_STREAM, 0); //创建监听套接字

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;

    strcpy(addr.sun_path,"socket_local");

    auto bind_key=bind(lis_fd, (struct sockaddr *)&addr, sizeof(addr));
    if(bind_key==-1)
    {
        perror("bind");
        exit(0);
    }

    listen(lis_fd, 100);
    
    struct sockaddr_un addr1;
    socklen_t len = sizeof(addr1);
    auto conn_fd = accept(lis_fd, (struct sockaddr *)&addr1, &len);
    char readbuf[1024];
    while (1)
    {
        read(conn_fd, readbuf, sizeof(readbuf));
        std::cout << readbuf << "\n";
        bzero(readbuf, sizeof(readbuf));
    }
    return 0;
}