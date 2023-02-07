/*
#include <unistd.h>
       #include <fcntl.h>
       int fcntl(int fd, int cmd, ...  arg);
        作用：1、复制文件描述符
              2、设置/获取文件的状态标志
        参数：
            fd：文件描述符
            cmd：
                F_DUPFD:复制文件描述符
                F_GETFL:获取指定文件描述符的文件状态 flag
                F_SETFL:设置指定文件描述符的文件状态 flag 不可更改：O_RDONLY,O_WRONLY,O_RDWR


*/