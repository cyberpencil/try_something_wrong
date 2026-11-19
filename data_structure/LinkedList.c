#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


/* ==================== 状态查询 ==================== */

/* 判断链表是否为空 */
bool list_is_empty(const LinkedList *list) 
{
  return list->head == NULL;
 }

/* 获取链表节点个数 */
size_t list_size(const LinkedList *list){
  return (size_t) list->size;
}

/* ==================== 插入操作 ==================== */

bool list_insert_head(LinkedList *list, int data) {
  ListNode* new_node = malloc(sizeof(ListNode));
  if(new_node == NULL) return false;
  new_node->data = data;
  new_node->next = NULL;

  if(list->head == NULL){
    list->head = new_node;
  } else {
    new_node->next = list->head;
    list->head = new_node;
  }
  
}

bool list_insert_tail(LinkedList *list, int data) {
  ListNode *new_node = malloc(sizeof(ListNode));
  if (new_node == NULL) {
    return false;
  }

  new_node->data = data;
  new_node->next = NULL;
  if (list->head == NULL) {
    list->head = new_node;
  } else {
    ListNode *cur = list->head;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = new_node;
  }
  list->size += 1;
  return true;
}
/*
 * 按位置插入：在第 index 个位置前插入元素
 * 合法范围：0 <= index <= list_size(list)
 * index == size 时等价于尾插
 */

bool list_insert_at(LinkedList *list, size_t index, int value) {
  if (index > list->size){
    return false;
  }

  ListNode *insert_node = malloc(sizeof(ListNode));
  if (insert_node == NULL){
    return false;
  }
  insert_node->data = value;
  insert_node->next = NULL;

    if (index == 0) {
      insert_node->next = list->head;
      list->head = insert_node;

    } else {
    ListNode *cur = list->head;
    for (int i = 0; i < index - 1; i++) {
      cur = cur->next;
    }
    insert_node->next = cur->next;
    cur->next = insert_node;
    }
  list->size++;
  return true;
}

/*链表打印*/
void list_print(LinkedList *list) {
  for (const ListNode *cur = list->head; cur != NULL; cur = cur->next) {
    printf("%d -> ", cur->data);
  }
  printf("NULL\n");
}

/* ==================== 初始化与销毁 ==================== */

/* 初始化空链表 */
void list_init(LinkedList *list){
  list->size = 0;
  list->head = NULL;
}

void list_clear(LinkedList *list) {
  ListNode *cur;
  cur = list->head;
  while (cur != NULL) {
    ListNode *node = cur->next;
    free(cur);
    cur = node;
  }
}
/* 销毁链表：清空并重置链表 */
void list_destroy(LinkedList *list) {
  list_clear(list);
  list_init(list);
}

/* ==================== 删除操作 ==================== */

/* 删除头节点 */
bool list_delete_head(LinkedList *list){
  if (list->head == NULL || list == NULL) {
      return false;
  } else {
    ListNode* old = list->head;
    list->head = list->head->next;
    list->size--;
    free(old);
    return true;
  }
}

/* 删除尾节点 */
bool list_delete_tail(LinkedList *list){
  if (list == NULL || list->head == NULL ) {
    return false;
  } else if (list->size == 1) {
    free(list->head);
    list->head = NULL;
    list->size--;
    return true;
  } else {

    ListNode* prev = list->head;
    while (prev->next->next != NULL) {
        prev = prev->next;
    } 
    free(prev->next);
    prev->next = NULL;
    list->size--;
    return true;
  }
}

/*
 * 按位置删除：删除第 index 个节点
 * 合法范围：0 <= index < list_size(list)
 */
bool list_delete_at(LinkedList *list, size_t index){
  if (list == NULL || list->head == NULL) {
    return false;
  } 
  ListNode* cur = list->head;
  if (index == 0){
    return list_delete_head(list);
  } else {
    
    for(int i = 0; i < index -1; i++){
      cur = cur->next;
    }
    ListNode* del = cur->next;
    cur->next = del->next;
    free(del);
    list->size--;
    return true;
  }

}

/* 按值删除：删除第一个值为 value 的节点 */
bool list_delete_value(LinkedList *list, int value);




int main() {
  ListNode *node0 = malloc(sizeof(ListNode));
  ListNode *node1 = malloc(sizeof(ListNode));
  ListNode *node2 = malloc(sizeof(ListNode));
  node0->data = 0;
  node0->next = node1;
  node1->data = 1;
  node1->next = node2;
  node2->data = 2;
  node2->next = NULL;

  LinkedList list;
  list.size = 0;
  list.head = node0;
  list.size = 3;
  printf("list address: 0x%p\n", list.head);
  // for (int i = 0; i < 7; i++) {
  //   list_insert_tail(&list, i + 1);
  // }
  // }
  // list_insert_tail(&list, 3);
  // list_insert_tail(&list, 4);
  // list_insert_tail(&list, 5);
  printf("new list length: %d\n", list.size);
  list_print(&list);
  list_insert_at(&list,  3, 3);
  printf("programming is good : \n");
  // list_delete_head(&list);
  printf("head poniter address: 0x%p\n", list.head);
  printf("new list length: %d\n", list.size);
  list_print(&list);
  printf("list is empty: %d\n",list_is_empty(&list));
  printf("===================\n");
  list_delete_at(&list, 0);
  list_print(&list);
  list_clear(&list);
  
}


