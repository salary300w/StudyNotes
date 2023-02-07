#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

int main()
{
    fd_set reads;
    FD_ZERO(&reads);
    std::cout<<reads[1];
}