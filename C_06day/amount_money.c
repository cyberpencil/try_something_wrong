
#include <stdio.h>
void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones){
    int amount;
    
    printf("Enter a dollar amount: ");
    scanf("%d", &amount);

    *twenties = amount / 20;
    amount = amount - *twenties * 20;

    *tens = amount / 10;
    amount = amount - *tens * 10;

    *fives = amount / 5;
    amount = amount - *fives * 5;

    *ones = amount;

}
int main(void)
{
    int twenties, tens, fives, ones;
    pay_amount(77, &twenties, &tens, &fives, &ones);
    printf("$20 bills: %d\n", twenties);
    printf("$10 bills: %d\n", tens);
    printf("$5 bills: %d\n", fives);
    printf("$1 bills: %d\n", ones);
    return 0;
}


