/* Checks numbers for repeated digits */
#include <stdbool.h> /* C99 only */
#include <stdio.h>
int main(void) {
  bool digit_seen[10] = {false};     /* digits that have appeared */
  bool digit_repeated[10] = {false}; /* digits that appeared twice or more */
  bool has_repeat = false;
  int digit;
  long n;
  printf("Enter a number: ");
  scanf("%ld", &n);
  while (n > 0) {
    digit = n % 10;
    if (digit_seen[digit]) {         /* seen before: this digit repeats */
      digit_repeated[digit] = true;
      has_repeat = true;
    }
    digit_seen[digit] = true;
    n /= 10;
  }
  if (has_repeat) {
    printf("Repeated digit(s):");
    for (digit = 0; digit < 10; digit++) /* scan 0..9 to print in ascending order */
      if (digit_repeated[digit])
        printf(" %d", digit);
    printf("\n");
  } else
    printf("No repeated digit\n");
  return 0;
}

