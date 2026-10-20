#include <stdio.h>

int *find_largest(int a[], int n);

int *find_largest(int a[], int n)
{
    int *max = &a[0];

    for (int i = 1; i < n; i++) {       /* a[0] 已作为初值，从 1 开始即可 */
        if (*max < a[i]) {
            max = &a[i];
        }
    }

    return max;                         /* 返回指向最大元素的指针 */
}

/* ---- 测试程序 ---- */
int main(void)
{
    int a[] = {5, 7, 8, 9, 3};
    int n = sizeof a / sizeof a[0];
    int *p = find_largest(a, n);

    printf("largest = %d (index %p)\n", *p, p);

    return 0;
}
