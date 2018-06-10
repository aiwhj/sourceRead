/**
 * Redis 源码
 * `helpEntry` 结构体
 * 指针与数组
 * 
 * 看到 `helpEntries[i] = tmp;` 产生疑问
 * 不是特别理解 helpEntries[i]，只是连续的内存块，怎么变成了数组？
 * 为什么没有显性声明helpEntries为数组却可以直接使用指针下标？
 * 
 * 1. 类型相同的连续内存块就是数组
 * 2. p[3] 等价于 *(p + 3)
 * */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *str;
} helpEntry;

static helpEntry *helpEntries;

int main ()
{
    int len = 5;
    helpEntry tmp;
    tmp.str = "whj";
    int i;
    // 申请5块连续的用于存放helpEntry结构体的内存
    helpEntries = malloc(sizeof(helpEntry) * len);

    for (i = 0; i < len; i++) {
        // 指针的加减
        *(helpEntries++) = tmp;
    }
    
    // 使指针重新指向内存头
    helpEntries -= 5;

    for (i = 0; i < len; i++)
    {
        // 指向数组的指针
        helpEntries[i] = tmp;
    }

    for (i = 0; i < len; i++)
    {
        printf("full: %s\n", (helpEntries++)->str);
    }
    
    helpEntries -= 5;
    free(helpEntries);
}