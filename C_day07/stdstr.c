#include <stdio.h>
#include <string.h>

int main(){
    char *str = " world ";
    // char *sub = strstr(str, "world");
    int len = strlen(str); 
    printf("%d\n", len);
    // printf("%s\n", sub);

    return 0;
}