/*
#include <semaphore.h>

       int sem_init(sem_t *sem, int pshared, unsigned int value);
       作用：信号量初始化，
       参数：
            sem：信号量变量的地址
            pshared：0用在线程间，非0用在进程间
            value：信号量的值



*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <semaphore.h>
//创建条件变量
std::vector<int> production;
pthread_mutex_t mutex;
sem_t pro;
sem_t cus;
void *pro_action(void *arg)
{
    while (1)
    {

        sem_wait(&pro);
        pthread_mutex_lock(&mutex);
        production.emplace_back(pthread_self());
        std::cout << "生产了新的产品：" << *production.rbegin() << ",此时的剩余产品：" << production.size() << "\n";
        pthread_mutex_unlock(&mutex);
        sem_post(&cus);
    }
    return nullptr;
}
void *cus_action(void *arg)
{
    while (1)
    {

        sem_wait(&cus);
        pthread_mutex_lock(&mutex);
        auto temp = *production.rbegin();
        production.pop_back();
        std::cout << "消费了新的产品：" << temp << ",此时的剩余产品：" << production.size() << "\n";
        pthread_mutex_unlock(&mutex);
        sem_post(&pro);
    }
    return nullptr;
}
int main()
{
    pthread_mutex_init(&mutex, nullptr);
    sem_init(&pro, 0, 100);
    sem_init(&cus, 0, 0);
    pthread_t pro[5], cus[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], nullptr, pro_action, nullptr);
        pthread_create(&cus[i], nullptr, cus_action, nullptr);
        pthread_detach(pro[i]);
        pthread_detach(cus[i]);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(nullptr);
    return 0;
}