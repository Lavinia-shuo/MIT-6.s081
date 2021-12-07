#include "kernel/types.h"
#include "user/user.h"

int main(void)
{
    int pfd[2], cfd[2];
    char buf, msg = '0';

    pipe(pfd);
    pipe(cfd);
    if (fork() == 0)
    {
        read(pfd[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(cfd[1], &msg, 1);
    }
    else
    {
        write(pfd[1], &msg, 1);
        read(cfd[0], &buf, 1);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}