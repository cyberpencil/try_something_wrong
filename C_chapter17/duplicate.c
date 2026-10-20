#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *duplicate(char *str)
{
    char *p = (char *)malloc(strlen(str) + 1);
    if (p == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(p, str);
    return p;
}


int main(void)
{
    char *str = "hello, world!";
    char *p = duplicate(str);
    printf("%s\n", p);
    free(p);
    return 0;
}