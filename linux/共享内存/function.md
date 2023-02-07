#include <sys/ipc.h>
       #include <sys/shm.h>
       int shmget(key_t key, size_t size, int shmflg); 
       作用：创建共享内存段，新创建的内存段中数据初始化为0，或者获取已有共享内存段的标识
       参数：
            key：key_t类型的整型，通过这个参数找到或者创建一个共享内存段 一般用16进制表示，非0值
            size：共享内存的大小
            shmflg：属性
                访问权限
                附加属性：判断/创建共享内存段是否存在
                    创建：IPC_CREAT
                    判断共享内存是否存在：IPC_EXCL 需要与IPC_CREAT一起使用
        返回值：
            失败返回-1
            成功返回共享内存的引用ID，用来操作共享内存




            #include <sys/types.h>
       #include <sys/shm.h>

       void *shmat(int shmid, const void *shmaddr, int shmflg);
       作用：和当前进程进行关联
       参数：
            shmid：共享内存的标识（ID），由shmgat返回值获取
            shmaddr：申请的共享内存的起始地址，传入null 由内核指定
            shmflg：对共享内存的操作
                    读权限：SHM_RDONLY,必须要有读权限
                    读写：0
        返回值：
            成功返回共享内存的起始地址
            失败返回（void*)-1

       int shmdt(const void *shmaddr);
       作用：解除当前进程和共享内存的关联
       参数：
            shmaddr：共享内存的首地址
        返回值：成功0，失败-1



#include <sys/ipc.h>
       #include <sys/shm.h>

       int shmctl(int shmid, int cmd, struct shmid_ds *buf);
       作用：删除共享内存，共享内存要删除才会消失，
       参数：
            shmid：共享内存的标识（ID）
            cmd：操作
                IPC_STAT:获取当前共享内存的状态
                IPC_SET:设置共享内存的状态
                IPC_RMID：标记共享内存被销毁
            buf：需要设置或获取的共享内存的属性信息
        返回值：



            #include <sys/types.h>
       #include <sys/ipc.h>

       key_t ftok(const char *pathname, int proj_id);
       作用：根据指定的路径名，和int值，生成一个共享内存的key

