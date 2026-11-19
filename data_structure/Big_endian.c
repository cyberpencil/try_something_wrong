#include <stdio.h>

int main() {
  int a = 0x12345678;
  char *p = (char *)&a;
  if (*p == 0x12) 
    printf("big endian\n");
  else{
    printf("*p: %x\n", *p);
    printf("little endian\n");
}
  return 0;
}