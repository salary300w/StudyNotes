/*
#include <pthread.h>

       void pthread_exit(void *retval);
       作用：终止当前线程
       参数：
            retval：需要传递一个指针，作为一个返回值，可以在pthread_join函数中获取到。
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
    pthread_create(&threa, nullptr, deal, &num);
    int i = 10;
    while (i)
    {
        std::cout << "父线程：" << i-- << "\n";
        sleep(1);
    }
    return 0;
}