#include <stdio.h>


int main() {
//  struct { int x, y; } x;
//  struct { int x, y; } y;
 
//  x.x = 1;
//  x.y = 2;
//  y.x = 3;
//  y.y = 4;
//  printf("%d %d %d %d\n", x.x, x.y, y.x, y.y);
//  return 0;
    struct Complex {
        double real, image;
    };
    struct Complex c1, c2, c3;
    c1 = (struct Complex){.real = 1.0, .image = 0.0}, c2 =(struct Complex) {1.0, 0.0}, c3;
    c1 = c2;
    printf("%f %f\n", c1.real, c1.image);
    c3.image = c1.image + c2.image;
    c3.real = c1.real + c2.real;
    printf("%f %f\n", c3.real, c3.image);
    return 0;
}