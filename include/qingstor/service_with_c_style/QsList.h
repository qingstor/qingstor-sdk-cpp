
#ifndef _QS_LIST_H
#define _QS_LIST_H

#include <memory.h>
#include <stddef.h>
#include <stdlib.h>
#include  "../QsSdkOption.h"

typedef struct qs_list_s qs_list_t;

struct qs_list_s
{
    qs_list_t *next, *prev;
};

#define qs_list_head_init(name) \
    {                           \
        &(name), &(name)        \
    }

#define qs_list_init(ptr)    \
    do                       \
    {                        \
        (ptr)->next = (ptr); \
        (ptr)->prev = (ptr); \
    } while (0)

// list head to add it before
static void qs_list_append(qs_list_t * new_node, qs_list_t * listhead)
{
    new_node->prev = listhead->prev;
    listhead->prev->next = new_node;
    listhead->prev = new_node;
    new_node->next = listhead;
}

// deletes entry from list
static void qs_list_del(qs_list_t * entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
    qs_list_init(entry);
}

// tests whether a list is empty
static int qs_is_list_empty(const qs_list_t * list_head)
{
    return (list_head->next == list_head);
}

// get last
#define qs_list_get_last(list, type) qs_is_list_empty(list) ? NULL : qs_list_entry((list)->prev, type)

// get first
#define qs_list_get_first(list, type) qs_is_list_empty(list) ? NULL : qs_list_entry((list)->next, type)

#define qs_list_entry(ptr, type) (type *)((char *)ptr - offsetof(type, node))

// traversing
#define qs_list_for_each_entry(postp, pos, head) for (pos = qs_list_entry((head)->next, postp); &pos->node != (head); pos = qs_list_entry(pos->node.next, postp))

#define qs_list_for_each_entry_safe(postp, pos, n, head) for (pos = qs_list_entry((head)->next, postp), n = qs_list_entry(pos->node.next, postp); &pos->node != (head); pos = n, n = qs_list_entry(n->node.next, postp))

typedef struct
{
    qs_list_t node;
    char *content;
} qs_string_item_t;

typedef struct
{
    qs_list_t node;
    int *content;
} qs_bool_item_t;

typedef struct
{
    qs_list_t node;
    int *content;
} qs_int_item_t;

typedef struct
{
    qs_list_t node;
    char *content;
} qs_time_item_t;

typedef struct
{
    qs_list_t node;
    int64_t *content;
} qs_long_item_t;

typedef struct
{
    int64_t size;
    void *buffer;
} qs_buffer_t;

#endif
