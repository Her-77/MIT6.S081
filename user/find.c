#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user.h"

char *fmtname(char *path) // 从路径中提取出文件名，例如从"./user/root/test"中抽取出"test"
{
    static char buf[DIRSIZ + 1];
    char *p;
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), 0, DIRSIZ - strlen(p));
    return buf;
}

void find(char *path, char *name)
{
    // printf("path: %s\nname: %s\n", path, name);
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        // printf("file: %s\n", fmtname(path));
        if (strcmp(fmtname(path), name) == 0)
            printf("%s\n", path);
        break;

    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
        {
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        // 如果成功读取一个完整的目录项，那么返回值将等于目录项的大小 sizeof(de)。因此，循环将一直进行下去，直到不能再读取更多的完整目录项（文件末尾或出错），循环才会终止。
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            //printf("de.name: %s\n", de.name);
            if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            // printf("de.name: %s\n", de.name);
            // printf("DIR path: %s\n", buf);
            find(buf, name);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("'find' Usage: find <path> <file name>\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}