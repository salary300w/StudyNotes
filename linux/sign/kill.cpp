/*
#include <sys/types.h>
       #include <signal.h>

       int kill(pid_t pid, int sig);
       作用：给某个进程pid，发送某个信号。sig
       参数：
            pid：进程pid
                >0 发送给指定进程
                =0 将信号发送给当前的进程组
                =-1 将信号发送给每一个有权限接收这个信号的进程
                <-1 取绝对值，和>0相同；
            sig：信号编号或者宏值，0表示不发送任何信号


    #include <signal.h>

       int raise(int sig);
       作用： 给当前进程发送信号
       参数：要发送的信号
       返回值：
            成功返回0
            失败非0

    #include <stdlib.h>

       void abort(void);
       作用：发送SIGABRT信号给当前进程，杀死当前进程
*/
