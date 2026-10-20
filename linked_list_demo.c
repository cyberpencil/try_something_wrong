/*
 * linked_list_demo.c
 * ---------------------------------------------------------------------------
 * 链表 / 静态链表 / 动态链表 / 单链表 的 增、删、改、查 完整示例
 *
 * 编译 (gcc/msvc 均可):
 *     gcc -std=c11 -Wall -Wextra -O2 -o linked_list_demo linked_list_demo.c
 * 运行:
 *     ./linked_list_demo
 *
 * 全文分三部分:
 *   1) 动态单链表(带头结点/哨兵结点) —— malloc 分配结点, 指针串联
 *   2) 无头结点单链表          —— 演示二级指针的用法
 *   3) 静态链表                —— 用数组下标(游标)代替指针
 * ---------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ===========================================================================
 * 第一部分: 动态单链表(带头结点)
 * ---------------------------------------------------------------------------
 * "动态"的含义: 结点在堆区由 malloc 在运行时申请, 个数可以随意变化,
 *               结点之间的先后关系由真正的指针 next 记录。
 *
 *   head -> [dummy|next] -> [10|next] -> [20|next] -> [30|NULL]
 *            头结点(不存有效数据)       第一个数据结点      尾结点
 *
 * 头结点的作用: 让"空表"和"非空表"的插入/删除逻辑完全统一,
 *               头指针 head 永远不变, 函数不用返回新的头。
 * =========================================================================== */

typedef struct Node {
    int          data;   /* 数据域 */
    struct Node *next;   /* 指针域: 保存下一个结点的地址, NULL 表示表尾 */
} Node;

/* ------------------------------ 建表 / 销毁 ------------------------------ */

Node *list_create(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (head == NULL) {
        fprintf(stderr, "错误: malloc 失败(内存不足)\n");
        exit(EXIT_FAILURE);
    }
    head->data = 0;      /* 头结点的数据域无意义, 占位而已 */
    head->next = NULL;
    return head;
}

/* 释放整表(包括头结点)。传入的 head 用完后必须置 NULL, 否则是野指针 */
void list_destroy(Node *head)
{
    Node *cur = head;
    while (cur != NULL) {
        Node *nxt = cur->next;   /* ①先把下一个记下来 */
        free(cur);               /* ②再释放当前     */
        cur = nxt;               /* ③顺序绝不能反过来 */
    }
}

/* 只清空数据结点, 保留头结点, 之后还能继续用 */
void list_clear(Node *head)
{
    Node *cur = head->next;
    while (cur != NULL) {
        Node *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    head->next = NULL;
}

bool list_empty(const Node *head)
{
    return head->next == NULL;
}

int list_length(const Node *head)
{
    int n = 0;
    for (const Node *p = head->next; p != NULL; p = p->next)
        ++n;
    return n;
}

/* ---------------------------------- 增 ---------------------------------- */

/* 头插: O(1)。注意先接后断, 顺序写错会丢链 */
void list_push_front(Node *head, int v)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = head->next;   /* ① 新结点先指向原来的第一个结点 */
    head->next = p;         /* ② 头结点再指向新结点           */
}

/* 尾插: O(n), 需要走到表尾 */
void list_push_back(Node *head, int v)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = NULL;

    Node *tail = head;
    while (tail->next != NULL)   /* 停在最后一个结点上 */
        tail = tail->next;
    tail->next = p;
}

/* 在下标 pos 处插入(pos 从 0 开始, pos == 表长 表示尾插)。
 * 返回 false 表示 pos 越界。 */
bool list_insert_at(Node *head, int pos, int v)
{
    if (pos < 0) return false;

    if (pos > list_length(head)) return false;   /* 尾插 pos == 长度 是合法的 */

    Node *prev = head;                       /* 找到第 pos-1 个结点 */
    for (int i = 0; i < pos; ++i)
        prev = prev->next;

    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = prev->next;
    prev->next = p;
    return true;
}

/* 有序插入: 要求表已经是升序, 插入后仍然升序 */
void list_insert_sorted(Node *head, int v)
{
    Node *prev = head;
    while (prev->next != NULL && prev->next->data < v)
        prev = prev->next;

    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = prev->next;
    prev->next = p;
}

/* ---------------------------------- 删 ---------------------------------- */

/* 删除第一个值为 v 的结点, 返回是否删掉了 */
bool list_erase_value(Node *head, int v)
{
    Node *prev = head;
    while (prev->next != NULL && prev->next->data != v)
        prev = prev->next;

    if (prev->next == NULL) return false;   /* 没找到 */

    Node *victim = prev->next;              /* 被删结点 */
    prev->next = victim->next;              /* 前驱绕过它 */
    free(victim);                           /* 一定不能忘了 free */
    return true;
}

/* 删除所有值为 v 的结点, 返回删除个数 */
int list_erase_all(Node *head, int v)
{
    int cnt = 0;
    Node *prev = head;
    while (prev->next != NULL) {
        if (prev->next->data == v) {
            Node *victim = prev->next;
            prev->next = victim->next;
            free(victim);
            ++cnt;
            /* prev 不动: 因为新的 prev->next 还没检查过 */
        } else {
            prev = prev->next;
        }
    }
    return cnt;
}

/* 删除下标 pos 处的结点 */
bool list_erase_at(Node *head, int pos)
{
    if (pos < 0) return false;

    Node *prev = head;
    for (int i = 0; i < pos && prev->next != NULL; ++i)
        prev = prev->next;

    if (prev->next == NULL) return false;   /* 越界 */

    Node *victim = prev->next;
    prev->next = victim->next;
    free(victim);
    return true;
}

/* 删除表头第一个数据结点(出栈) */
bool list_pop_front(Node *head, int *out)
{
    if (head->next == NULL) return false;
    Node *victim = head->next;
    head->next = victim->next;
    if (out != NULL) *out = victim->data;
    free(victim);
    return true;
}

/* O(n^2) 去重: 每个结点都跟它后面所有结点比一遍 */
void list_remove_duplicates(Node *head)
{
    for (Node *p = head->next; p != NULL; p = p->next) {
        Node *prev = p;
        while (prev->next != NULL) {
            if (prev->next->data == p->data) {
                Node *victim = prev->next;
                prev->next = victim->next;
                free(victim);
            } else {
                prev = prev->next;
            }
        }
    }
}

/* ---------------------------------- 改 ---------------------------------- */

/* 把所有值为 oldv 的结点改成 newv, 返回改动个数 */
int list_update(Node *head, int oldv, int newv)
{
    int cnt = 0;
    for (Node *p = head->next; p != NULL; p = p->next) {
        if (p->data == oldv) {
            p->data = newv;
            ++cnt;
        }
    }
    return cnt;
}

/* 改下标 pos 处的值 */
bool list_update_at(Node *head, int pos, int v)
{
    Node *p = head->next;
    for (int i = 0; i < pos && p != NULL; ++i)
        p = p->next;
    if (p == NULL) return false;
    p->data = v;
    return true;
}

/* ---------------------------------- 查 ---------------------------------- */

/* 按值查: 返回第一个匹配结点的指针, 找不到返回 NULL。
 * 返回的是"借出去的"指针, 调用者不该 free 它 —— 这是 C 链表常见的约定。 */
Node *list_find(Node *head, int v)
{
    for (Node *p = head->next; p != NULL; p = p->next)
        if (p->data == v)
            return p;
    return NULL;
}

/* 按位置查(O(n))。链表不支持随机访问, 所以按下标取值是线性的 */
Node *list_at(Node *head, int pos)
{
    if (pos < 0) return NULL;
    Node *p = head->next;
    for (int i = 0; i < pos && p != NULL; ++i)
        p = p->next;
    return p;
}

/* 按值查下标, 找不到返回 -1 */
int list_index_of(Node *head, int v)
{
    int i = 0;
    for (Node *p = head->next; p != NULL; p = p->next, ++i)
        if (p->data == v)
            return i;
    return -1;
}

/* ---------------------------------- 其它 --------------------------------- */

void list_print(const Node *head, const char *tag)
{
    printf("%-22s [", tag);
    for (const Node *p = head->next; p != NULL; p = p->next)
        printf("%d%s", p->data, (p->next != NULL) ? " -> " : "");
    printf("]  (长度 %d)\n", list_length(head));
}

/* 原地逆置(头插法重建): 三个指针轮流倒 */
void list_reverse(Node *head)
{
    Node *cur = head->next;
    head->next = NULL;               /* 新表先清空 */
    while (cur != NULL) {
        Node *nxt = cur->next;       /* ① 记下后继 */
        cur->next = head->next;      /* ② 头插到新表 */
        head->next = cur;
        cur = nxt;                   /* ③ 继续处理下一个 */
    }
}

/* 冒泡排序(交换数据域, 不搬结点)。生产代码一般直接交换整条链 */
void list_sort(Node *head)
{
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (Node *p = head->next; p->next != NULL; p = p->next) {
            if (p->data > p->next->data) {   /* 只交换数据域, 结点位置不动 */
                int t = p->data;
                p->data = p->next->data;
                p->next->data = t;
                swapped = true;
            }
        }
    }
}

/* ===========================================================================
 * 第二部分: 无头结点的单链表 —— 为什么要用二级指针 Node **
 * ---------------------------------------------------------------------------
 * 此时 head 本身就指向第一个数据结点(空表时 head == NULL)。
 * 插入/删除"第一个结点"会改变 head 这个变量本身,
 * 所以函数必须拿到 head 变量的地址, 即 Node **head。
 * =========================================================================== */

typedef struct IntNode {
    int             data;
    struct IntNode *next;
} IntNode;

void nd_push_front(IntNode **phead, int v)
{
    IntNode *p = (IntNode *)malloc(sizeof(IntNode));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = *phead;    /* 新结点接在原来的表头前面 */
    *phead = p;          /* 再让 head 变量改指向新结点 */
}

void nd_push_back(IntNode **phead, int v)
{
    IntNode *p = (IntNode *)malloc(sizeof(IntNode));
    if (p == NULL) { fprintf(stderr, "错误: malloc 失败\n"); exit(EXIT_FAILURE); }
    p->data = v;
    p->next = NULL;

    if (*phead == NULL) {      /* 空表是特例: 直接改 head */
        *phead = p;
        return;
    }
    IntNode *tail = *phead;
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = p;
}

/* 删除第一个值为 v 的结点。
 * pp 是"指向当前结点的那根指针"的地址:
 *   pp == phead         → 当前结点是第一个结点, 改的是 head 本身
 *   pp == &prev->next   → 当前结点挂在别人后面, 改的是别人
 * 两种情况一句 *pp = victim->next 通吃, 不用分类讨论。 */
bool nd_erase(IntNode **phead, int v)
{
    IntNode **pp = phead;
    while (*pp != NULL && (*pp)->data != v)
        pp = &(*pp)->next;

    if (*pp == NULL) return false;

    IntNode *victim = *pp;
    *pp = victim->next;
    free(victim);
    return true;
}

IntNode *nd_find(IntNode *head, int v)
{
    for (IntNode *p = head; p != NULL; p = p->next)
        if (p->data == v)
            return p;
    return NULL;
}

int nd_length(const IntNode *head)
{
    int n = 0;
    for (const IntNode *p = head; p != NULL; p = p->next)
        ++n;
    return n;
}

void nd_print(const IntNode *head, const char *tag)
{
    printf("%-22s [", tag);
    for (const IntNode *p = head; p != NULL; p = p->next)
        printf("%d%s", p->data, (p->next != NULL) ? " -> " : "");
    printf("]  (长度 %d)\n", nd_length(head));
}

void nd_free_all(IntNode *head)
{
    while (head != NULL) {
        IntNode *nxt = head->next;
        free(head);
        head = nxt;
    }
}

/* ===========================================================================
 * 第三部分: 静态链表 —— 用数组下标(游标 cursor)代替指针
 * ---------------------------------------------------------------------------
 * 适用场景: 不能用动态内存(嵌入式/单片机), 或者结点数量固定。
 * 思路和动态链表完全一样, 只是 next 里存的不是地址而是数组下标:
 *
 *   下标:      0        1        2        3        4 ...
 *   pool[]: [data|next] ...                 <-- 一整块静态存储(数组/全局区)
 *   next = -1 等价于动态链表里的 NULL
 *
 * 通常开两条链:
 *   head      → 数据链表(已使用的结点)
 *   free_head → 备用链表(空闲结点, 用 next 串成一条链)
 * 这样 s_malloc / s_free 就是 O(1) 的"摘下/挂回"操作,
 * 本质上是自己实现了一个极简的内存池。
 * =========================================================================== */

#define STATIC_CAP 12   /* 静态链表的最大容量(编译期确定) */

typedef struct {
    int data;           /* 数据域 */
    int next;           /* 游标域: 下一个结点的下标, -1 表示 NULL */
} SNode;

typedef struct {
    SNode pool[STATIC_CAP];
    int   head;         /* 数据链表头游标 */
    int   free_head;    /* 备用链表头游标 */
    int   used;         /* 已用结点个数 */
} StaticList;

void s_init(StaticList *L)
{
    for (int i = 0; i < STATIC_CAP - 1; ++i)
        L->pool[i].next = i + 1;
    L->pool[STATIC_CAP - 1].next = -1;
    L->free_head = 0;      /* 一开始所有结点都在备用链表里 */
    L->head      = -1;     /* 数据链表为空 */
    L->used      = 0;
}

/* 相当于 malloc: 从备用链表头摘一个结点下来, 返回它的下标 */
int s_alloc(StaticList *L)
{
    if (L->free_head == -1) return -1;      /* 相当于 malloc 返回 NULL */
    int idx = L->free_head;
    L->free_head = L->pool[idx].next;
    L->pool[idx].next = -1;
    ++L->used;
    return idx;
}

/* 相当于 free: 把结点挂回备用链表头 */
void s_free(StaticList *L, int idx)
{
    if (idx < 0 || idx >= STATIC_CAP) return;
    L->pool[idx].next = L->free_head;
    L->free_head = idx;
    --L->used;
}

int s_length(const StaticList *L) { return L->used; }

/* 增: 头插 */
bool s_push_front(StaticList *L, int v)
{
    int idx = s_alloc(L);
    if (idx == -1) return false;            /* 表满 */
    L->pool[idx].data = v;
    L->pool[idx].next = L->head;
    L->head = idx;
    return true;
}

/* 增: 尾插 */
bool s_push_back(StaticList *L, int v)
{
    int idx = s_alloc(L);
    if (idx == -1) return false;
    L->pool[idx].data = v;
    L->pool[idx].next = -1;

    if (L->head == -1) {
        L->head = idx;
        return true;
    }
    int tail = L->head;                     /* 游标版"走指针" */
    while (L->pool[tail].next != -1)
        tail = L->pool[tail].next;
    L->pool[tail].next = idx;
    return true;
}

/* 增: 在下标 pos 处插入 */
bool s_insert_at(StaticList *L, int pos, int v)
{
    if (pos < 0 || pos > L->used) return false;

    int idx = s_alloc(L);
    if (idx == -1) return false;
    L->pool[idx].data = v;

    if (pos == 0) {
        L->pool[idx].next = L->head;
        L->head = idx;
        return true;
    }
    int prev = L->head;
    for (int i = 0; i < pos - 1; ++i)
        prev = L->pool[prev].next;
    L->pool[idx].next = L->pool[prev].next;
    L->pool[prev].next = idx;
    return true;
}

/* 删: 删除第一个值为 v 的结点 */
bool s_erase_value(StaticList *L, int v)
{
    int prev = -1;                 /* -1 表示"前驱是 head 本身" */
    int cur  = L->head;
    while (cur != -1 && L->pool[cur].data != v) {
        prev = cur;
        cur  = L->pool[cur].next;
    }
    if (cur == -1) return false;

    if (prev == -1) L->head = L->pool[cur].next;        /* 删的是首结点 */
    else            L->pool[prev].next = L->pool[cur].next;
    s_free(L, cur);
    return true;
}

/* 改: 把所有 oldv 改成 newv */
int s_update(StaticList *L, int oldv, int newv)
{
    int cnt = 0;
    for (int cur = L->head; cur != -1; cur = L->pool[cur].next) {
        if (L->pool[cur].data == oldv) {
            L->pool[cur].data = newv;
            ++cnt;
        }
    }
    return cnt;
}

/* 查: 按值返回下标, 找不到返回 -1 */
int s_find(const StaticList *L, int v)
{
    for (int cur = L->head; cur != -1; cur = L->pool[cur].next)
        if (L->pool[cur].data == v)
            return cur;
    return -1;
}

void s_print(const StaticList *L, const char *tag)
{
    printf("%-22s [", tag);
    for (int cur = L->head; cur != -1; cur = L->pool[cur].next) {
        printf("%d", L->pool[cur].data);
        printf("%s", (L->pool[cur].next != -1) ? " -> " : "");
    }
    printf("]  (长度 %d, 空闲 %d)\n", s_length(L), STATIC_CAP - L->used);
}

/* ===========================================================================
 * 演示
 * =========================================================================== */

static void demo_dynamic_list(void)
{
    printf("\n===== 1. 动态单链表(带头结点) =====\n");
    Node *L = list_create();
    list_print(L, "初始空表");

    list_push_back(L, 10);
    list_push_back(L, 20);
    list_push_back(L, 30);
    list_print(L, "尾插 10,20,30");

    list_push_front(L, 5);
    list_print(L, "头插 5");

    list_insert_at(L, 2, 15);
    list_print(L, "在下标 2 插入 15");

    list_insert_at(L, 4, 25);
    list_print(L, "在下标 4 插入 25");

    printf("在下标 99 插入: %s\n", list_insert_at(L, 99, -1) ? "成功" : "失败(越界)");

    printf("查 20  -> %s, 下标 %d\n",
           list_find(L, 20) ? "找到" : "没找到", list_index_of(L, 20));
    printf("查 99  -> %s\n", list_find(L, 99) ? "找到" : "没找到");
    printf("下标 3 的值 = %d\n", list_at(L, 3)->data);

    int changed = list_update(L, 15, 150);
    list_print(L, "把 15 改成 150");
    printf("改动个数 = %d\n", changed);

    list_update_at(L, 0, 1);
    list_print(L, "把下标 0 改成 1");

    printf("删除 30     : %s\n", list_erase_value(L, 30) ? "成功" : "失败");
    list_print(L, "删除 30 之后");

    printf("删除 99     : %s\n", list_erase_value(L, 99) ? "成功" : "失败(不存在)");
    list_print(L, "删除不存在的值");

    list_erase_at(L, 0);
    list_print(L, "删除下标 0");

    list_push_back(L, 100);
    list_push_back(L, 100);
    list_push_back(L, 100);
    list_print(L, "尾插 3 个 100");
    printf("删除所有 100, 共 %d 个\n", list_erase_all(L, 100));
    list_print(L, "删除所有 100 之后");

    list_push_back(L, 20);
    list_push_back(L, 20);
    list_print(L, "制造重复元素");
    list_remove_duplicates(L);
    list_print(L, "去重之后");

    list_reverse(L);
    list_print(L, "原地逆置");

    list_sort(L);
    list_print(L, "排序(升序)");

    /* 有序插入演示 */
    list_clear(L);
    int seq[] = { 30, 10, 50, 20, 40, 10 };
    for (int i = 0; i < 6; ++i)
        list_insert_sorted(L, seq[i]);
    list_print(L, "依次有序插入 30,10,50,20,40,10");

    int out = 0;
    list_pop_front(L, &out);
    printf("出栈一个: %d\n", out);
    list_print(L, "出栈之后");

    printf("空表? %s\n", list_empty(L) ? "是" : "否");
    list_clear(L);
    printf("清空后 空表? %s, 长度 %d\n",
           list_empty(L) ? "是" : "否", list_length(L));

    list_destroy(L);
    L = NULL;   /* 防止野指针 */
    printf("已释放整表, 指针置空\n");
}

static void demo_no_dummy_head(void)
{
    printf("\n===== 2. 无头结点单链表(用 Node **) =====\n");
    IntNode *head = NULL;               /* 空表就是一个 NULL */

    nd_push_back(&head, 2);
    nd_push_front(&head, 1);
    nd_push_back(&head, 3);
    nd_push_back(&head, 4);
    nd_print(head, "1,2,3,4");

    printf("查 3  -> %s\n", nd_find(head, 3) ? "找到" : "没找到");

    /* 关键点: 删除"第一个结点"时 head 变量本身会变, 所以传 &head */
    printf("删除表头元素 1: %s\n", nd_erase(&head, 1) ? "成功" : "失败");
    nd_print(head, "删除 1 之后");

    printf("删除表尾元素 4: %s\n", nd_erase(&head, 4) ? "成功" : "失败");
    nd_print(head, "删除 4 之后");

    nd_free_all(head);
    head = NULL;
    printf("已释放\n");
}

static void demo_static_list(void)
{
    printf("\n===== 3. 静态链表(数组 + 游标, 容量 %d) =====\n", STATIC_CAP);
    StaticList L;
    s_init(&L);
    s_print(&L, "初始空表");

    s_push_back(&L, 10);
    s_push_back(&L, 20);
    s_push_back(&L, 30);
    s_push_front(&L, 5);
    s_print(&L, "尾插 10,20,30 + 头插 5");

    s_insert_at(&L, 2, 15);
    s_print(&L, "在下标 2 插入 15");

    int idx = s_find(&L, 20);
    printf("查 20 -> %s, 下标 %d\n", (idx != -1) ? "找到" : "没找到", idx);
    printf("查 99 -> %s\n", (s_find(&L, 99) != -1) ? "找到" : "没找到");

    printf("把 15 改成 150, 共 %d 个\n", s_update(&L, 15, 150));
    s_print(&L, "改完之后");

    printf("删除 30: %s\n", s_erase_value(&L, 30) ? "成功" : "失败");
    s_print(&L, "删除 30 之后");

    /* 反复插入删除, 验证空闲结点会被复用(不会有内存泄漏) */
    for (int i = 0; i < 5; ++i)
        s_push_back(&L, 100 + i);
    s_print(&L, "再尾插 5 个");
    for (int i = 0; i < 5; ++i)
        s_erase_value(&L, 100 + i);
    s_print(&L, "再删掉这 5 个");

    /* 一直插到满, 看是否优雅地失败 */
    printf("一直插入直到表满...\n");
    int v = 0;
    while (s_push_back(&L, 1000 + v))
        ++v;
    s_print(&L, "表满");
    printf("还能继续插入? %s\n", s_push_back(&L, 9999) ? "能" : "不能(已满, s_alloc 返回 -1)");
}

int main(void)
{
    printf("########################################################\n");
    printf("#  链表 / 静态链表 / 动态链表 / 单链表 增删改查 演示    #\n");
    printf("########################################################\n");

    demo_dynamic_list();
    demo_no_dummy_head();
    demo_static_list();

    printf("\n全部演示结束。\n");
    return 0;
}
