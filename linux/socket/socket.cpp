#include <stdio.h>
#include <iostream>
#include <arpa/inet.h>
int main()

{
    char a[4]={'1','2','3','4'};
    std::cout<<a<<"\n";

    int b=*(int*)a;

    int c=htonl(b);

    char* d=(char*)&c;

    std::cout<<*d<<*(d+1)<<*(d+2)<<*(d+3)<<"\n";
    }
