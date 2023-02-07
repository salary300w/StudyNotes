/*
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
fd:返回的文件描述符，open得到的。
buf：需要读取数据存放的地方
count：指定数组的大小

返回值：
    成功：
    >0：返回实际读取到的字节数
    =0：文件无数据可读
    失败：
    返回-1；



#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
fd:返回的文件描述符，open得到的。
buf：往磁盘写入的数据
count：要写的数据的实际大小

返回值：
    成功：实际返回的字节数
    失败：返回-1
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
int main()
{
    auto key = open("文件.txt", O_RDONLY);
    if (key == -1)
        perror("open");
    char num[2];
    auto key1 = open("new.txt", O_RDWR|O_CREAT, 0664);
    if (key1 == -1)
        perror("new");
    int len = 0;
    while ((len = read(key, num, sizeof(num))) > 0)
        write(key1, num, sizeof(num));
    close(key);
    close(key1);
    return 0;
}
