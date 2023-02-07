/*
        #include <sys/mman.h>
       void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
       功能：将一个文件或一个设备映射到内存中
       参数：
            addr：null，由内核指定
            length：要映射的数据的长度，这个值不能为0，使用文件长度，获取文件长度stat或lseek函数
            prot：对申请的内存映射区的操作权限，要操作映射区需要有读权限
            flags：
                MAP-SHARED:映射区的数据自动和磁盘区同步，进程间通信，需要设置这个权限
                MAP-PRIVATE：不同步
            fd：需要操作的文件描述符
                通过open得到，open的是一个磁盘文件
                文件大小不能为0，open指定的权限不能和prot参数有冲突
            offset：映射的偏移量，一般不用。必须指定为4k的整数倍，0表示不偏移。
        返回值：返回创建的内存首地址
            失败返回：MAP_FAILED ，（void*）-1；
       int munmap(void *addr, size_t length);
            功能：释放内存映射
            参数：
                addr：要释放的内存首地址
                length：要释放的内存大小，要和mmap函数中的length一样。
*/
/*
    使用内存映射进行进程间通讯：
        1、有关系的进程
                还没有子进程时创建内存映射区
                父子进程共享创建的内存映射区
        2、没有关系的进程
                准备大小不为0的磁盘文件
                进程1通过磁盘文件创建内存映射区
                    得到一个操作这块内存的指针
                进程2通过磁盘文件创建内存映射区
                    得到一个操作这块内存的指针
                使用内存映射区通信。
    内存映射区非阻塞
*/
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
    //打开一个文件
    auto open_key = open("text.txt", O_RDWR);
    if (open_key == -1)
    {
        perror("open:");
        exit(0);
    }
    auto size = lseek(open_key, 0, SEEK_END);
    auto mmap_key = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, open_key, 0);
    if (mmap_key == MAP_FAILED)
    {
        perror("mmap:");
        exit(0);
    }
    auto fork_key = fork();
    if (fork_key > 0)
    {
        wait(NULL);
        char buf[64];
        memcpy(buf, mmap_key, sizeof(mmap_key));
        std::cout << buf;
    }
    else if (fork_key == 0)
    {
        memcpy(mmap_key, "hello", 5);
    }
    else
    {
        perror("fork:");
        exit(0);
    }
    return 0;
}