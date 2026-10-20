#include <stdio.h>
#include <stdlib.h>

void *my_malloc(size_t size)
{
    void *p = malloc(size);          /* 只分配一次, 把结果存下来 */

    if (p == NULL) {                 /* 检查的就是要返回的那块内存 */
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

int main(void)
{
    int *p = (int *)my_malloc(sizeof(int));
    *p = 10;
    printf("%d\n", *p);
    free(p);
    return 0;
    
}