/*
#include <unistd.h>

       int access(const char *pathname, int mode);
        作用：判断某个文件是否有某个权限，或者判断文件是否存在
        参数：
            pathname：文件路径
            mode：
                R_OK：是否有读权限
                W_OK: 是否有写权限
                X_OK: 是否有执行权限
                F_OK：是否存在
            返回值：成功0，失败-1
*/
#include <iostream>
#include <unistd.h>
int main()
{
    int key = access("open.cpp", F_OK);
    if (key == 0)
        std::cout << "文件存在";
    else
        std::cout << "文件不存在";

    return 0;
}   