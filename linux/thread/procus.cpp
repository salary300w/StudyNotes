//生产者消费者模型

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
//创建条件变量
std::vector<int> production;
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_cond_t cond1;
void *pro_action(void *arg)
{
    while (1)
    {

        pthread_mutex_lock(&mutex);
        if (production.size() == 100)
        {
            pthread_cond_wait(&cond1,&mutex);
        }
        else if (production.size() == 0)
        {

            production.emplace_back(pthread_self());
            std::cout << "生产了新的产品：" << *production.rbegin() << ",此时的剩余产品：" << production.size() << "\n";
            pthread_cond_signal(&cond);
        }
        else
        {
            production.emplace_back(pthread_self());
            std::cout << "生产了新的产品：" << *production.rbegin() << ",此时的剩余产品：" << production.size() << "\n";
        }
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}
void *cus_action(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (production.size() != 0)
        {
            auto temp = *production.rbegin();
            production.pop_back();
            std::cout << "消费了新的产品：" << temp << ",此时的剩余产品：" << production.size() << "\n";
            pthread_cond_signal(&cond1);
        }
        else
        {
            pthread_cond_signal(&cond1);
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}
int main()
{
    pthread_mutex_init(&mutex, nullptr);

    pthread_cond_init(&cond, nullptr);
    pthread_cond_init(&cond1, nullptr);

    pthread_t pro[5], cus[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], nullptr, pro_action, nullptr);
        pthread_create(&cus[i], nullptr, cus_action, nullptr);
        pthread_detach(pro[i]);
        pthread_detach(cus[i]);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&cond1);

    pthread_exit(nullptr);
    return 0;
}