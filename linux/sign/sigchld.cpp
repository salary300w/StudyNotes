#include <signal.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void wait_child(int num)
{
    wait(nullptr);
}

int main()
{
    auto fork_key = fork();
    if (fork_key > 0)
    {
        struct sigaction set;
        set.sa_flags = 0;
        set.sa_handler = wait_child;
        sigemptyset(&set.sa_mask);
        sigaction(SIGCHLD, &set, nullptr);
        int i=100;
        while(i)
        {
            std::cout<<i<<"\n";
            i--;
            sleep(1);
        }
    }
    else if (fork_key == 0)
    {
        std::cout << "i am child\n";
    }
    return 0;
}