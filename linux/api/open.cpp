/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int open(const char *pathname, int flags);
打开已经存在的文件
pathname：打开文件的路径
flags：文件的操作权限设置或其他设置（O_RDONLY, O_WRONLY,O_RDWR.）
返回值：文件描述符 打开错误时返回-1
errno：错误号，根据不同的错误返回不同的数值。
       #include <stdio.h>
       void perror(const char *s);
       s参数：用户描述，比如hello，实际输出 hello：（实际错误描述）
       作用：打印错误信息


int open(const char *pathname, int flags, mode_t mode);
创建新的文件
pathname：创建文件的路径
flags：文件的操作权限设置或其他设置（O_RDONLY, O_WRONLY,O_RDWR.）
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "iostream"
int main()
{
    auto key = open("text", O_RDWR);
    std::cout<<key<<"\n";
    if (key == -1)
    {
        perror("open");
    }
    close(key);


    return 0;
}
