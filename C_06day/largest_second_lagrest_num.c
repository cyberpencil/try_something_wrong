/* Searches an array for its largest and second-largest elements,
   storing them in the variables pointed to by largest / second_largest. */
#include <stdio.h>

#define N 5

void find_two_largest(int [], int, int *, int *);

int main(void)
{
    int a[N] = {5, 7, 8, 9, 3};
    int num1, num2;                 /* 必须是真实的 int 变量 */

    find_two_largest(a, N, &num1, &num2);
    printf("largest: %d, second largest: %d\n", num1, num2);

    return 0;
}

void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    int i;

    *largest = *second_largest = a[0];      /* 用首元素做初值，避免读到未初始化的值 */

    for (i = 1; i < n; i++) {
        if (a[i] > *largest) {
            *second_largest = *largest;     /* 旧的最大值降级为第二大 */
            *largest = a[i];
        } else if (a[i] > *second_largest && a[i] != *largest) {
            *second_largest = a[i];         /* 只刷新第二大，且排除等于最大值的情况 */
        }
    }

    printf("the largest num is %d\n", *largest);
    printf("the second largest num is %d\n", *second_largest);
}
