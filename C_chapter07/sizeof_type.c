/* 让 MinGW 的 printf 支持 C99 的 %zu 格式符, 必须在包含头文件之前定义 */
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
int main(){

    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(long) = %zu\n", sizeof(long));
    printf("sizeof(long long) = %zu\n", sizeof(long long));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(long double) = %zu\n", sizeof(long double));
    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(short) = %zu\n", sizeof(short));

    return 0;
}