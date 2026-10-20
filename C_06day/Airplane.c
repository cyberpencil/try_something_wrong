/* C语言程序设计：现代方法 第五章第8题 */

#include <stdio.h>

int main(void)
{
    int hour, minute;
    int t;

    printf("Enter a time (24-hour): ");
    scanf("%d:%d", &hour, &minute);

    /* 转换为从午夜开始的分钟数 */
    t = hour * 60 + minute;

    if (t <= 531) {          /* 8:00 与 9:43 的中点 */
        printf("Closest departure time is 8:00 a.m., arriving at 10:16 a.m.\n");
    } else if (t <= 631) {   /* 9:43 与 11:19 的中点 */
        printf("Closest departure time is 9:43 a.m., arriving at 11:52 a.m.\n");
    } else if (t <= 723) {   /* 11:19 与 12:47 的中点 */
        printf("Closest departure time is 11:19 a.m., arriving at 1:31 p.m.\n");
    } else if (t <= 803) {   /* 12:47 与 2:00 的中点 */
        printf("Closest departure time is 12:47 p.m., arriving at 3:00 p.m.\n");
    } else if (t <= 892) {   /* 2:00 与 3:45 的中点 */
        printf("Closest departure time is 2:00 p.m., arriving at 4:08 p.m.\n");
    } else if (t <= 1042) {  /* 3:45 与 7:00 的中点 */
        printf("Closest departure time is 3:45 p.m., arriving at 5:55 p.m.\n");
    } else if (t <= 1222) {  /* 7:00 与 9:45 的中点 */
        printf("Closest departure time is 7:00 p.m., arriving at 9:20 p.m.\n");
    } else {
        printf("Closest departure time is 9:45 p.m., arriving at 11:58 p.m.\n");
    }

    return 0;
}