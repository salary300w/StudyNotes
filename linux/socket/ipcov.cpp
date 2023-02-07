/*
        #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>

        in_addr_t inet_addr(const char *cp);
        作用：将ipv4的字符串地址，转换为网络字节序整数 char cp[]="192.168.0.1";

        int inet_aton(const char *cp, struct in_addr *inp);
        作用：将ipv4的字符串地址，转换为网络字节序整数存储在inp结构体中

        char *inet_ntoa(struct in_addr in);
        作用：将ipv4网络字节序的整数，转换为点分十进制的ipv4地址字符串
                           旧api
        ---------------------------------------------------------------
                           新api

        #include <arpa/inet.h>

       int inet_pton(int af, const char *src, void *dst);
       作用：将ipv4或ipv6的地址字符串地址转换为网络字节序二进制格式
       参数：
            af：
                AF_INET:ipv4
                AF_INET6:ipv6
            src:地址字符串
            dst：网络字节序二进制格式，传出参数；

         const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
         作用：将网络字节序二进制格式转换为文本格式
         参数：
            af：
                AF_INET:ipv4
                AF_INET6:ipv6
            src:网络字节序二进制格式
            dst：地址字符串，传出参数
            size：dst数组的大小
        返回值：转换后字符串的地址，和dst是同一个值。
*/

#include <iostream>
#include <arpa/inet.h>
int main()
{
    char addr[]{"192.168.0.1"};
    int temp;
    inet_pton(AF_INET, addr, &temp);
    auto p=(unsigned char*)&temp;
    std::cout<<(int)*p<<" "<<(int)*(p+1)<<" "<<(int)*(p+2)<<" "<<(int)*(p+3)<<"\n";
    char ip[16];
    auto temp1=inet_ntop(AF_INET,&temp,ip,16);
    std::cout<<ip<<"\n";
    std::cout<<temp1<<"\n";

    return 0;
}