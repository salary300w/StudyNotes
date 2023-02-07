//模拟实现linux指令 ls-l程序
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
int main(int arg, char *argv[])
{
    if (arg < 2)
    {
        std::cout << argv[0] << "filename\n";
        return -1;
    }
    struct stat st;
    auto key = stat(argv[1], &st);
    if (key == -1)
    {
        perror("stat");
        return -1;
    }

    //获取文件类型和文件权限
    char perms[11];
    switch (st.st_mode & S_IFMT)
    {
    case S_IFDIR:
        perms[0] = 'd';
        break;
    case S_IFBLK:
        perms[0] = 'b';
        break;
    case S_IFLNK:
        perms[0] = 'l';
        break;
    case S_IFREG:
        perms[0] = '-';
        break;
    case S_IFCHR:
        perms[0] = 'c';
        break;
    case S_IFSOCK:
        perms[0] = 's';
        break;
    case S_IFIFO:
        perms[0] = 'p';
        break;
    default:
        perms[0] = '?';
        break;
    } 
    perms[1]=(st.st_mode&S_IRUSR)?'r':'-';
    perms[2]=(st.st_mode&S_IWUSR)?'w':'-';
    perms[3]=(st.st_mode&S_IXUSR)?'x':'-';
    perms[4]=(st.st_mode&S_IRGRP)?'r':'-';
    perms[5]=(st.st_mode&S_IWGRP)?'w':'-';
    perms[6]=(st.st_mode&S_IXGRP)?'x':'-';
    perms[7]=(st.st_mode&S_IROTH)?'r':'-';
    perms[8]=(st.st_mode&S_IWOTH)?'w':'-';
    perms[9]=(st.st_mode&S_IXOTH)?'x':'-';
    perms[10]=' ';
    //硬连接数
    int linknum=st.st_nlink;
    //文件所有者
    auto user_name=getpwuid(st.st_uid)->pw_name;

    auto group_name=getgrgid(st.st_gid)->gr_name;
    
    //文件大小
    auto file_size=st.st_size;

    //获取修改时间

    auto temp_time=ctime(&st.st_mtim.tv_sec);
    
    char file_time[100];
    
    strncpy(file_time,temp_time,sizeof(temp_time)-1);

    char buf[1024];

    sprintf(buf,"%s %d %s %s %ld %s %s",perms,linknum,user_name,group_name,file_size,file_time,argv[1]);

    std::cout<<buf<<"\n";

    return 0;
}