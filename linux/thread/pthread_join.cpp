/*
#include <pthread.h>

       int pthread_join(pthread_t thread, void **retval);
       作用：和一个已经终止的进程连接，回收子线程的资源
       特点：阻塞函数，调用一次回收一个子线程，一般在主线程中使用
       参数
            thread：需要回收的子线程id
            retval：接收子线程退出时的返回值
        返回值：成功0，失败返回错误号
*/
#include <pthread.h>
#include <iostream>
#include <unistd.h>
void *deal(void *arg)
{
    int i = 10;
    while (i)
    {
        std::cout << "子线程：" << i-- << "\n";
        if (i == 5)
            pthread_exit(nullptr);
        sleep(1);
    }
}
int main()
{
    pthread_t threa;
    int num = 10;
    auto pid = pthread_create(&threa, nullptr, deal, &num);

    auto tid = pthread_join(threa, NULL);

    int i = 10;
    while (i)
    {
        std::cout << "父线程：" << i-- << "\n";
        sleep(1);
    }
    return 0;
}