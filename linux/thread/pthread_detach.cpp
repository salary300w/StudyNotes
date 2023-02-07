/*

 #include <pthread.h>

       int pthread_detach(pthread_t thread);
       作用：分离一个线程，当某个线程标记分离时，当进程结束时，会自动回收其资源。
       参数：
            thread：线程号
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
        sleep(1);
    }
}
int main()
{
    pthread_t threa;
    pthread_create(&threa, nullptr, deal, nullptr);
    pthread_detach(threa);
    int i = 10;
    while (i)
    {
        std::cout << "父线程：" << i-- << "\n";
        sleep(3);
    }
    return 0;
}