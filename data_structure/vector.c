#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     // SIZE_MAX，用于容量溢出检查
#define SUCCESS 1       // 成功
#define ERROR -1        // 失败
#define MALLOC_ERROR -2 // 申请内存失败
#define INDEX_ERROR -3  // 错误的索引号


// 结构体类型必须完整：元素个数由 malloc 在运行时决定，不写在 typedef 里
typedef struct {
    int data;
    int size;
} Vector;

Vector* allocate_initarr(int length) {
    Vector* vector = NULL;

    // 边界处理：非正长度无意义，直接拒绝
    if (length <= 0) {
        return NULL;
    }

    // 防止 sizeof(Vector) * length 溢出（先转换再比较，避免有符号/无符号混算）
    if ((size_t)length > SIZE_MAX / sizeof(Vector)) {
        return NULL;
    }

    vector = malloc(sizeof(Vector) * (size_t)length);
    if (vector == NULL) {
        return NULL; // 申请内存失败，由调用方根据返回值为 NULL 处理
    }
    vector->size = length;
    return vector;
}

int main(void) {
    const int length = 7;

    Vector* vector = allocate_initarr(length);
    if (vector == NULL) {
        printf("allocate memory failed\n");
        return MALLOC_ERROR;
    }

    for (int i = 0; i < length; i++) {
        vector[i].data = i + 1;
        printf("vector[%d] is %d\n", i + 1, vector[i].data);
    }
    printf("vector length is %d \n", vector->size);

    free(vector);  // 释放堆内存，避免内存泄漏
    vector = NULL; // 释放后置空，避免悬空指针

}