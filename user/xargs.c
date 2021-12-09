#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char buf[512];
    char *args[MAXARG];
    char c;
    char *p;
    int n;

    memset(buf, 0, sizeof(buf));
    memset(args, 0, sizeof(args));

    for (int i = 1; i < argc; ++i)
    {
        args[i - 1] = argv[i];
    }
    while (1)
    {
        p = buf;

        while ((n = read(0, &c, 1)) && c != '\n')
        {
            *p = c;
            p++;
        }
        *p = '\0';
        if (p != buf)
        {
            args[argc - 1] = buf;
            if (fork() == 0)
            {
                exec(argv[1], args);
                exit(1);
            }
            wait(0);
        }
        if (n == 0)
            break;
    }
    exit(0);
}