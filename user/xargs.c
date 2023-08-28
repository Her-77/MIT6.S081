#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"   // MAXARG

int main(int argc, char *argv[])
{
    char *args[MAXARG];
    char buf[512];
    
    memset(args, 0, MAXARG);
    memset(buf, 0, 512);
    for (int i = 1; i < argc; i++)
        args[i - 1] = argv[i];
    
    while(1)
    {
        char *p = buf;  // buf会被重复利用
        int n;
        while ((n = read(0, p, 1)) && *p != '\n')
            p++;        // read()会逐一读取管道中的信息
        *p = '\0';

        if(p != buf)
        {
            if(fork()==0)
            {
                args[argc - 1] = buf;
                args[argc] = 0;
                exec(argv[1], args);
                printf("Subprocess Error!!!\n");    // 如果上一行的exec()成功执行，则这行printf()不会输出
            }
            else
                wait(0);
        }
        else
            break;
    }
    exit(0);
}