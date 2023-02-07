/*
#include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
       作用：创建子线程
       参数：
            thread：传出参数，线程创建成功后，子线程id写入此变量中
            attr：设置线程的属性，一般是使用默认值，传递null
            start_routine：函数指针，子线程需要处理的逻辑代码
            arg：给第三个参数使用，传参
        返回值：成功返回0，失败返回错误号 获取错误好的信息char* strerror（int errornum）;
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
        std::cout<<*(int*)arg;
        sleep(1);
    }
}
int main()
{
    pthread_t threa;
    int num=10;
    pthread_create(&threa, nullptr, deal, &num);
    int i = 10;
    while (i)
    {
        std::cout << "父线程：" << i-- << "\n";
        sleep(1);
    }
    return 0;
}