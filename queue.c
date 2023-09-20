#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new_queue = malloc(sizeof(struct list_head));
    INIT_LIST_HEAD(new_queue);
    return new_queue;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    element_t *item = NULL, *tmp = NULL;
    list_for_each_entry_safe (item, tmp, head, list) {
        free(item->value);
        free(item);
    }

    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *node = NULL;

    if (!head || !s)
        return false;

    size_t slen;
    node = malloc(sizeof(element_t));
    if (!node)
        return false;
    INIT_LIST_HEAD(&node->list);
    slen = strlen(s);
    node->value = malloc(slen + 1);
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, slen);
    node->value[slen] = '\0';
    list_add(&node->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *node = NULL;

    if (!head || !s)
        return false;

    size_t slen;
    node = malloc(sizeof(element_t));
    if (!node)
        return false;
    INIT_LIST_HEAD(&node->list);
    slen = strlen(s);
    node->value = malloc(slen + 1);
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, slen);
    node->value[slen] = '\0';
    list_add_tail(&node->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;

    /* Check the sp size is less than bufsize */
    if (sp != NULL) {
        size_t splen = sizeof(sp);
        bufsize = (bufsize < splen) ? bufsize : splen;
    }

    /* Get string from the element */
    element_t *node = list_first_entry(head, element_t, list);
    char *s = node->value;
    if (bufsize && s) {
        size_t slen = strlen(s);
        size_t len = (bufsize <= slen) ? (bufsize - 1) : slen;
        memcpy(sp, s, len);
        sp[len] = '\0';
    }

    list_del_init(&node->list);
    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;

    /* Check the sp size is less than bufsize */
    if (sp != NULL) {
        size_t splen = sizeof(sp);
        bufsize = (bufsize < splen) ? bufsize : splen;
    }

    /* Get string from the element */
    element_t *node = list_last_entry(head, element_t, list);  // callback
    char *s = node->value;
    if (bufsize && s) {
        size_t slen = strlen(s);
        size_t len = (bufsize <= slen) ? bufsize - 1 : slen;
        memcpy(sp, s, len);
        sp[len] = '\0';
    }

    list_del_init(&node->list);
    return node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return -1;

    struct list_head *curr, *next;
    int size = 0;

    list_for_each_safe (curr, next, head)
        size += 1;

    return size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head)
        return false;

    struct list_head *fast = head->next;
    struct list_head *slow = head->next;

    while (fast != head) {
        if (fast->next == head)
            break;

        fast = fast->next->next;
        slow = slow->next;
    }

    /* Queue is empty */
    if (slow == head)
        return false;

    list_del_init(slow);

    element_t *item = NULL;
    item = list_entry(slow, element_t, list);
    free(item->value);
    free(item);

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;


    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head)
        return;
#if 0
    struct list_head *prev, *curr, *next, **new_curr;
    curr = head->next;

    while (curr && curr->next != head) {
        next = curr->next;
        curr->next = next->next;
        next->next = curr;

        if (curr == head->next) {
            new_curr = &curr;
            *new_curr = next;
        } else {
            prev->next = next;
        }

        prev = curr;
        curr = curr->next;
    }
#endif
    return;
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
