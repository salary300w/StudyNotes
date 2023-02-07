#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
int main()
{
    auto open_key = open("test.txt", O_RDWR);
    auto size = lseek(open_key, 0, SEEK_END);
    auto mmap_key = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, open_key, 0);
    memcpy(mmap_key, "hello", 5);
    return 0;
}
