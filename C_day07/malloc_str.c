/* 让 MinGW 的 printf 支持 C99 的 %zu 格式符, 必须在包含头文件之前定义 */
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>        /* 只为切换控制台代码页, 解决中文乱码 */
#endif

/* 演示 1：malloc 按需分配一块恰好放得下字符串的内存 */
static void demo_malloc(void)
{
    const char *src = "hello, malloc!";
    size_t len = strlen(src) + 1;          /* +1 是给结尾的 '\0' 留位置 */

    char *str = (char *)malloc(len * sizeof(char));
    if (str == NULL) {                     /* malloc 失败一定要检查 */
        fprintf(stderr, "malloc 失败\n");
        exit(EXIT_FAILURE);
    }

    strcpy(str, src);
    printf("[malloc ] 申请 %zu 字节, 内容: %s\n", len, str);

    free(str);                             /* 用完必须释放, 否则内存泄漏 */
    str = NULL;                            /* 置空, 避免野指针 */
}

/* 演示 2：realloc 边读边扩容, 处理长度事先未知的字符串 */
static char *read_line(void)
{
    size_t cap = 8;                        /* 初始容量故意给小一点, 好观察扩容 */
    size_t len = 0;
    char *buf = (char *)malloc(cap);
    if (buf == NULL)
        return NULL;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= cap) {              /* 还要留一个字节给 '\0' */
            cap *= 2;
            char *tmp = (char *)realloc(buf, cap);
            if (tmp == NULL) {
                free(buf);                 /* 扩容失败: 释放旧内存再返回 */
                return NULL;
            }
            buf = tmp;                     /* realloc 可能搬家, 必须用它的返回值 */
            printf("[realloc] 容量不够, 扩容到 %zu 字节\n", cap);
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';
    return buf;
}

int main(void)
{
#ifdef _WIN32
    /* 源文件是 UTF-8 编码, 而 Windows 控制台默认代码页是 GBK(936),
       不切换的话, 程序输出的 UTF-8 汉字会被按 GBK 解码成乱码 */
    SetConsoleOutputCP(CP_UTF8);        /* 输出按 UTF-8 解码 */
    SetConsoleCP(CP_UTF8);              /* 输入也按 UTF-8, 保证中文输入正确 */
#endif

    demo_malloc();

    printf("请输入一行文本: ");
    char *line = read_line();
    if (line == NULL) {
        fprintf(stderr, "动态分配失败\n");
        return EXIT_FAILURE;
    }

    printf("[输入   ] 长度 %zu, 内容: %s\n", strlen(line), line);

    free(line);                            /* 谁申请, 谁释放 */
    line = NULL;

    return 0;
}
