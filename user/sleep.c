#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    /*
    int size = 0;
    while(argv[size] != 0){
        size++;
    }
    printf("argc: %d\nsize of argv: %d\n", argc, size);
    */
    if (argc < 2)
    {
        printf("Sleep need one argument!\n");
        exit(-1);
    }

    int ticks = atoi(argv[1]);
    sleep(ticks);
    printf("nothing happens for a little while.\n");
    exit(0);
}