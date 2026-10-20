#include "stdio.h"

void swap(int *, int *);
int main(){
    int i = 1, j = 2;
    printf("before change two int num:%d %d \n",i, j);
    swap(&i, &j);
    return 0;
}

void swap(int *p, int *q){
    int tmep;
    tmep = *p;
    *p = *q;
    *q = tmep;
    printf("after change two int num:%d %d \n",*p,*q);
}