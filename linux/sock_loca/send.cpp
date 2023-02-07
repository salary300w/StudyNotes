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
    auto conn_fd = socket(AF_UNIX, SOCK_STREAM, 0); //创建监听套接字

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,"app_local");
    auto bind_key=bind(conn_fd, (sockaddr *)&addr, sizeof(addr));
    if(bind_key==-1)
    {
        perror("bind");
        exit(0);
    }
    struct sockaddr_un addr1;
    addr1.sun_family = AF_UNIX;
    strcpy(addr1.sun_path,"socket_local");
    connect(conn_fd, (sockaddr *)&addr1, sizeof(addr1));
    int i=0;
    while (1)
    {
        char wbuf[1024]="hello";
        strcat(wbuf,std::to_string(i++).c_str());
        write(conn_fd, wbuf, strlen(wbuf));
        sleep(1);
    }
    return 0;
}