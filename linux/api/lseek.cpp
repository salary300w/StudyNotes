/*
    标准c库
       #include <stdio.h>

       int fseek(FILE *stream, long offset, int whence);


    Linux 系统函数
       #include <sys/types.h>
       #include <unistd.h>

       off_t lseek(int fd, off_t offset, int whence);
       作用：
            1、移动文件指针到头文件
                lseek(fd,0,SEEK_SET);
            2、获取文件指针的位置
            3、获取文件的长度
                lseek(fd,0,SEEK_END);
            4、拓展文件的长度
                lseek(fd,100,SEEk_END);

       参数：
        fd 文件描述符
        offset 偏移量
        whence
            SEEK_SET
                设置文件指针的偏移量 通过offset指定
            SEEK_CUR
                从当前位置+offset设置偏移量
            SEEK_END
                文件大小+offset的值设置偏移量
       返回值：
        文件指针最终所在的位置
*/
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
    auto key=open("文件.txt",O_RDWR);

    if(key==-1)
	    perror("open");

    lseek(key,100,SEEK_END);

    write(key," ",1);
    close(key);

    return 0;
}
