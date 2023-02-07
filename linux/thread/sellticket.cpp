//线程同步，多线程实现买票案例，3个窗口一共100张票，

#include <iostream>
#include <string.h>
#include <pthread.h>
int ticket = 100;
pthread_rwlock_t rwlock;
void *deal(void *arg)
{

    std::string action;
    while (1)
    {
        std::cin >> action;
        if (action == "buy")
        {
            pthread_rwlock_wrlock(&rwlock);
            if (ticket > 0)
            {
                ticket--;
                std::cout << "购买成功，余票：" << ticket << "\n";
            }
            else
            {
                std::cout << "余票不足\n";
            }
            pthread_rwlock_unlock(&rwlock);
        }
        else if (action == "back")
        {
            pthread_rwlock_wrlock(&rwlock);
            ticket++;
            std::cout << "退票成功,余票：" << ticket << "\n";
            pthread_rwlock_unlock(&rwlock);
        }
        else if (action == "exit")
        {
            action.clear();
            std::cout << "线程：" << pthread_self() << "，已经退出！\n";
            break;
        }

        else if (action == "look")
        {
            pthread_rwlock_unlock(&rwlock);
            std::cout << "余票为：" << ticket << "\n";
            pthread_rwlock_destroy(&rwlock);
        }
        else
        {
            std::cout << "请重新输入：\n";
        }
        action.clear();
    }
}
int main()
{
    pthread_rwlock_init(&rwlock, nullptr);
    pthread_t tid1, tid2, tid3;
    pthread_attr_t thread_set;
    pthread_attr_init(&thread_set);
    pthread_attr_setdetachstate(&thread_set, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid1, &thread_set, deal, nullptr);
    pthread_create(&tid2, &thread_set, deal, nullptr);
    pthread_create(&tid3, &thread_set, deal, nullptr);
    pthread_attr_destroy(&thread_set);
    pthread_rwlock_destroy(&rwlock);
    pthread_exit(nullptr);
    return 0;
}