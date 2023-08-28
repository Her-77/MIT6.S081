#include "kernel/types.h"
#include "user.h"

char buf[10];
int main()
{
    
    int p1[2];
    //int p2[2];
    pipe(p1);
    //pipe(p2);
    /*   
    if (fork() == 0)
    {
        close(p1[1]);
        read(p1[0], buf, sizeof(buf));
        int childPID = getpid();
        printf("%d: received ping\n", childPID);
        close(p1[0]);

        close(p2[0]);
        write(p2[1], "B", 1);
        close(p2[1]);
    }
    else
    {
        close(p1[0]);
        write(p1[1], "A", 1);
        close(p1[0]);

        close(p2[1]);
        read(p2[0], buf, sizeof(buf));
        int fatherPID = getpid();
        printf("%d: received pong\n", fatherPID);
        close(p2[0]);
    }
    */
    if(fork() == 0){
        read(p1[0], buf, sizeof(buf));
        int childPID = getpid();
        printf("%d: received ping\n", childPID);

        write(p1[1], "B", 1);
        exit(0);
    }
    else
    {
        write(p1[1], "A", 1);

        read(p1[0], buf, sizeof(buf));
        int fatherPID = getpid();
        printf("%d: received pong\n", fatherPID);
        wait((int *)0);
    }
    exit(0);
}