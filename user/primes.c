#include "kernel/types.h"
#include "user.h"

#define SIZE 34

void recursiveFork(int _buf[])
{
    if(_buf[0] == 0)
        exit(0);
    
    int p[2];
    int buf[SIZE];
    int buf_[SIZE];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        memset(buf, 0, sizeof(buf));
        memset(buf_, 0, sizeof(buf_));
        int Count = 0;
        
        read(p[0], buf, sizeof(buf));
        close(p[0]);
        
        int flag = buf[0];
        printf("prime %d\n", flag);
        for (int i = 1; buf[i] != 0; i++)
        {
            if (buf[i] % flag != 0)
                buf_[Count++] = buf[i];
        }
        recursiveFork(buf_);
    }
    else
    {
        close(p[0]);
        write(p[1], _buf, SIZE * sizeof(int));
        close(p[1]);
        wait((int *)0);
    }

    exit(0);
}

int main()
{
    int digits[SIZE];
    memset(digits, 0, sizeof(digits));
    for (int i = 0; i < SIZE; i++)
        digits[i] = i + 2;

    recursiveFork(digits);

    exit(0);
}