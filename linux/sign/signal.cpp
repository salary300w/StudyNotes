/*
#include <signal.h>

       typedef void (*sighandler_t)(int);

       sighandler_t signal(int signum, sighandler_t handler);
       作用：捕捉信号，自行处理
       参数
            signum：需要捕捉的信号
            handler：捕捉到信号的处理方式
                SIG_IGN:忽略信号
                SIG_DFL:使用信号默认的行为
                回调函数：捕捉到信号，系统调用该函数，需要程序员实现。
        返回值：成功返回前一次的回调函数。第一次调用返回null。失败返回SIG_ERR
*/