/*
 #include <signal.h>

       int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
       参数：
            signum：需要捕捉的信号编号或宏值
            act：捕捉到信号后的相应处理动作
            oldact：上一次对信号捕捉相关的设置，一般不使用设置null
        返回值：
            成功0
            失败-1


        结构体：
            struct sigaction {
               void     (*sa_handler)(int);
               //函数指针，指向的函数就是信号捕捉之后的处理函数

               void     (*sa_sigaction)(int, siginfo_t *, void *);
               //不常用，

               sigset_t   sa_mask;
               //临时阻塞信号集，信号捕捉函数执行过程中，临时阻塞某些信号。

               int        sa_flags;
               //使用哪一个信号处理对捕捉到的信号进行处理
               //0表示使用sa_handler处理，SA_SIGINFO表示使用sa_sigaction处理

               void     (*sa_restorer)(void);
               //被废弃，指定null
           };

*/