#include <stdio.h>

int main(){
    int arr[7] = {1,2,3,4,5,6,7};
    int *p = arr;
    printf("%p\n", p);
    printf("%d\n", *p);
    printf("%p\n", (p+1));
    printf("%d\n", *(p+2));
    printf("%d\n", *(p+3));
    printf("%d\n", *(p+4));
    printf("%d\n", *(p+5));
    printf("%d\n", *(p+6));
    return 0;
}