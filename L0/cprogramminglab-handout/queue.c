/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    /* Free queue structure */
    if (q == NULL) return;

    while (q->size > 0) q_remove_head(q, NULL);
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    if (q == NULL) return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (newh == NULL) return false;

    newh->value = v;
    newh->next = q->head;
    q->head = newh;
    /* Empty queue */
    if (q->size == 0) q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if (q == NULL) return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) return false;

    newt->value = v;
    newt->next = NULL;
    
    /* Empty queue */
    if (q->size == 0) q->head = newt;
    else q->tail->next = newt;

    q->tail = newt;
    q->size++;
    
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) return false;

    list_ele_t *oldh;
    oldh = q->head;

    if (vp != NULL) *vp = oldh->value;
    
    q->size--;
    q->head = oldh->next;

    free(oldh);

    return true;
}

int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) return 0;
    
    return q->size;
}

/*
  Reverse elements in queue
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) return;

    list_ele_t *curr_ele;
    list_ele_t *next_ele;
    list_ele_t *after_next_ele;

    curr_ele = q->head;
    next_ele = q->head->next;

    q->head->next = NULL;
    q->tail = q->head;

    while (next_ele != NULL)
    {
        after_next_ele = next_ele->next;
        next_ele->next = curr_ele;
        curr_ele = next_ele;
        next_ele = after_next_ele;
    }

    q->head = curr_ele;
}

