#include <stdio.h>
#include <stdlib.h>

/* 单链表结点定义（与 LeetCode 保持一致） */
struct ListNode {
    int val;
    struct ListNode *next;
};

/*
 * LeetCode 2. 两数相加
 * 输入：两个非空链表，按【逆序】存储一个非负整数（即头结点是个位）
 * 输出：两数之和的链表，同样逆序存储
 * 例：2->4->3 (342) + 5->6->4 (465) = 7->0->8 (807)
 *
 * 思路：逐位相加 + 进位(carry)，用哑结点尾插构造结果链表。
 * 时间复杂度 O(max(m, n))，空间复杂度 O(max(m, n))。
 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode dummy; /* 哑结点：省去"第一个结点"的特判 */
    struct ListNode *tail = &dummy;
    dummy.next = NULL;
    int carry = 0; /* 进位，只可能是 0 或 1 */

    /* carry != 0 让最高位产生的进位也能再建一个结点 */
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;

        struct ListNode *node =
            (struct ListNode *)malloc(sizeof(struct ListNode));
        if (node == NULL) { /* 内存分配失败的容错 */
            return NULL;
        }
        node->val = sum % 10; /* 当前位的数字 */
        node->next = NULL;

        tail->next = node; /* 尾插：结果顺序与输入一致（低位在前） */
        tail = node;
    }

    return dummy.next; /* dummy 在栈上，但它的 next 指向堆内存，返回安全 */
}

/* *************** 以下为本地测试辅助代码（提交 LeetCode 时不需要） *************** */

/* 用数组（低位在前）构造链表 */
struct ListNode *createList(const int *arr, int n) {
    struct ListNode dummy;
    struct ListNode *tail = &dummy;
    dummy.next = NULL;

    for (int i = 0; i < n; ++i) {
        struct ListNode *node =
            (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = arr[i];
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return dummy.next;
}

void printList(const struct ListNode *head) {
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

void freeList(struct ListNode *head) {
    while (head != NULL) {
        struct ListNode *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    int a[] = {2, 4, 3}; /* 342 */
    int b[] = {5, 6, 4}; /* 465 */

    struct ListNode *l1 = createList(a, sizeof(a) / sizeof(a[0]));
    struct ListNode *l2 = createList(b, sizeof(b) / sizeof(b[0]));

    printf("l1: ");
    printList(l1);
    printf("l2: ");
    printList(l2);

    struct ListNode *sum = addTwoNumbers(l1, l2);
    printf("sum: ");
    printList(sum); /* 期望 7 -> 0 -> 8 */

    freeList(l1);
    freeList(l2);
    freeList(sum);

    /* 额外用例：链表长度不等 + 最高位进位  999 + 1 = 1000 */
    int c[] = {9, 9, 9};
    int d[] = {1};
    struct ListNode *l3 = createList(c, 3);
    struct ListNode *l4 = createList(d, 1);
    struct ListNode *sum2 = addTwoNumbers(l3, l4);
    printf("999 + 1 = ");
    printList(sum2); /* 期望 0 -> 0 -> 0 -> 1 */

    freeList(l3);
    freeList(l4);
    freeList(sum2);

    return 0;
}
