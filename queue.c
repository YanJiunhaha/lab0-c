/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q;
    /* What if malloc returned NULL? */
    if (!(q = malloc(sizeof(queue_t))))
        return NULL;

    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    /* How about freeing the list elements and the strings? */
    list_ele_t *front = q->head, *tmp;
    while (front) {
        tmp = front;
        front = front->next;
        free(tmp->value);
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!(newh = malloc(sizeof(list_ele_t))))
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    int str_size = 1;
    char *str_cp = s;
    while (*str_cp != '\0') {
        ++str_cp;
        ++str_size;
    }
    if (!(str_cp = malloc(sizeof(char) * str_size))) {
        free(newh);
        return false;
    }
    int i;
    for (i = 0; i < str_size; ++i)
        *(str_cp + i) = *(s + i);

    newh->value = str_cp;
    q->head = newh;
    if (!q->size)
        q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return false;
    list_ele_t *newt;
    if (!(newt = malloc(sizeof(list_ele_t))))
        return false;
    newt->next = NULL;
    int str_size = 1;
    char *str_cp = s;
    while (*str_cp != '\0') {
        ++str_size;
        ++str_cp;
    }
    if (!(str_cp = malloc(sizeof(char) * str_size))) {
        free(newt);
        return false;
    }
    int i;
    for (i = 0; i < str_size; ++i)
        *(str_cp + i) = *(s + i);

    newt->value = str_cp;
    if (q->size)
        q->tail->next = newt;
    else
        q->head = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->size)
        return false;
    if (sp) {
        int i;
        for (i = 0; i < bufsize - 1; ++i)
            *(sp + i) = *(q->head->value + i);

        *(sp + bufsize - 1) = '\0';
    }
    free(q->head->value);
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    q->size--;
    if (!q->head)
        q->tail = NULL;
    free(tmp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return (q) ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->size)
        return;
    list_ele_t *front, *current, *next;
    current = q->head;
    next = q->head->next;

    front = q->tail;
    q->tail = q->head;
    q->head = front;
    current->next = NULL;

    while (next) {
        front = current;
        current = next;
        next = next->next;
        current->next = front;
    }
}
