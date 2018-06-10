/**
 * Redis 源码
 * `SDS` 字符串结构
 * 柔性数组 Flexible Array
 * 
 * 看到内存释放 `free(s - sizeof(struct sdshdr));` 的时候产生疑问，
 * 为什么结构体的内存和内部的字符数组的内存会是连续的？
 * 
 * https://coolshell.cn/articles/11377.html
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * charInit(char *init, int initlen);
void charFree(char *s);

struct sdshdr {
    int len;
    int free;
    // 结构体末尾定义空的字符数组，构建可变的字符串，只能在末尾定义
    char buf[];
};

int main()
{
    char *init = "i am whj";
    int initlen = strlen(init);

    char *buf = charInit(init, initlen);

    printf("the init: %s\n", buf);

    charFree(buf);
}

char * charInit(char *init, int initlen)
{
    struct sdshdr *sh;

    // 一起分配结构体和字符串所需要的的内存
    sh = malloc(sizeof(struct sdshdr) + initlen + 1);

    if (init)
    {
        memcpy(sh->buf, init, initlen);
    }
    sh->buf[initlen] = '\0';
    return (char *)sh->buf;
}

void charFree(char *s)
{
    if (s == NULL)
        return;
    // 使指针指向整块内存头部，然后释放
    free(s - sizeof(struct sdshdr));
}
