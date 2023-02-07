/*
int open(const char *pathname, int flags, mode_t mode);
创建新的文件
pathname：创建文件的路径
flags：文件的操作权限设置或其他设置（O_RDONLY, O_WRONLY,O_RDWR.）
mode:八进制的数，表示用户对新建文件的操作权限,最终权限是mode&~umask（0002）
umask的作用就是抹去某些权限
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "iostream"
int main()
{
    auto key = open("new_file", O_CREAT, 0777);
    if (key == -1)
        perror("open");
    close(key);
    auto key1=open("new_file",O_APPEND);
    

    return 0;
}