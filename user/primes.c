#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int pp[])
{
    close(pp[1]);
    int i;
    if (read(pp[0], &i, sizeof(i)) == 0)
    {
        close(pp[0]);
        exit(0);
    }
    printf("prime %d\n", i);

    int num, cp[2];
    pipe(cp);        //创建当前进程的管道，往里面写数据，它又变成了父进程
    if (fork() == 0) //子进程
    {
        close(pp[0]);
        close(cp[1]);
        child(cp);
    }
    else
    {
        close(cp[0]);
        while (read(pp[0], &num, sizeof(num)) != 0)
        {
            if (num % i != 0)
            {
                write(cp[1], &num, sizeof(num));
            }
        }
        close(pp[0]);
        close(cp[1]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p); //创建一个管道p

    if (fork() == 0) //子进程
    {
        child(p);
    }
    else
    {
        close(p[0]); //父进程，关闭管道读端

        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i, sizeof(i));
        }
        close(p[1]);
        wait(0); //等待子进程退出
    }
    exit(0);
}