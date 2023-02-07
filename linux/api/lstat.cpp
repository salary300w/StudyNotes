/*
#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *pathname, struct stat *statbuf);
            作用：获取文件的相关信息
            参数：
                pathname：操作的文件路径
                statbuf：结构体变量，传出参数
            返回值：成功为0，失败为-1；
       int lstat(const char *pathname, struct stat *statbuf);
            作用：获取软链接的相关信息
            参数：
                pathname：操作的文件路径
                statbuf：结构体变量，传出参数
            返回值：成功为0，失败为-1；

*/