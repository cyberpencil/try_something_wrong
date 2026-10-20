/* Prints a table of squares using a for statement */
#include <stdio.h>
int main(void)
{
int i, n;
char ch;
printf("This program prints a table of squares.\n");
printf("Enter number of entries in table: ");
scanf("%d", &n);
ch = getchar();
for (i = 1; i <= n; i++)
{   
   
    if(i % 24 == 0){
        printf("\n");
        printf("Press Enter to continue...");
        ch = getchar();
    }
    printf("%10d%10d\n", i, i * i);
}
return 0;
}