#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>



/* 链表节点 */
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

/* 链表管理结构 */
typedef struct LinkedList {
    ListNode *head;   /* 头指针 */
    size_t size;      /* 节点个数 */
} LinkedList;

/* 遍历回调函数类型 */
typedef void (*VisitFunc)(int value);

/* ==================== 初始化与销毁 ==================== */

/* 初始化空链表 */
void list_init(LinkedList *list);

/* 清空链表，释放所有节点，但保留链表对象 */
void list_clear(LinkedList *list);

/* 销毁链表：清空并重置链表 */
void list_destroy(LinkedList *list);

/* ==================== 状态查询 ==================== */

/* 判断链表是否为空 */
bool list_is_empty(const LinkedList *list);

/* 获取链表节点个数 */
size_t list_size(const LinkedList *list);

/* ==================== 插入操作 ==================== */

/* 头插：在链表头部插入元素 */
bool list_insert_head(LinkedList *list, int value);

/* 尾插：在链表尾部插入元素 */
bool list_insert_tail(LinkedList *list, int value);

/*
 * 按位置插入：在第 index 个位置前插入元素
 * 合法范围：0 <= index <= list_size(list)
 * index == size 时等价于尾插
 */
bool list_insert_at(LinkedList *list, size_t index, int value);

/* ==================== 删除操作 ==================== */

/* 删除头节点 */
bool list_delete_head(LinkedList *list);

/* 删除尾节点 */
bool list_delete_tail(LinkedList *list);

/*
 * 按位置删除：删除第 index 个节点
 * 合法范围：0 <= index < list_size(list)
 */
bool list_delete_at(LinkedList *list, size_t index);

/* 按值删除：删除第一个值为 value 的节点 */
bool list_delete_value(LinkedList *list, int value);

/* ==================== 查找与访问 ==================== */

/* 按值查找节点，返回第一个匹配节点的指针；找不到返回 NULL */
const ListNode *list_find_node(const LinkedList *list, int value);

/* 按值查找位置，返回第一个匹配节点的下标；找不到返回 -1 */
int list_find_index(const LinkedList *list, int value);

/*
 * 获取第 index 个节点的值
 * 合法范围：0 <= index < list_size(list)
 * 成功返回 true，并通过 out_value 输出
 */
bool list_get(const LinkedList *list, size_t index, int *out_value);

/*
 * 修改第 index 个节点的值
 * 合法范围：0 <= index < list_size(list)
 */
bool list_set(LinkedList *list, size_t index, int value);

/* ==================== 遍历操作 ==================== */

/* 遍历链表，对每个节点的值调用 visit 回调 */
void list_traverse(const LinkedList *list, VisitFunc visit);

/* ==================== 进阶操作 ==================== */

/* 原地反转链表 */
void list_reverse(LinkedList *list);

#endif /* LINKED_LIST_H */