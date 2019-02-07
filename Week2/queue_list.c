////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using linked lists.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

typedef struct queue queue;
typedef struct queue_node queue_node;

static void test_with_zero_item (void);
static void test_with_two_items (void);
static void test_with_50_items (void);



struct queue {
    size_t n_items;
	queue_node *head, *tail;
};

struct queue_node {
	Item item;
	queue_node *next;
};

static queue_node *queue_node_new (Item);

/** Create a new, empty Queue. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .head = NULL, .tail = NULL };
	return new;
}

/** Destroy a Queue, releasing all resources associated with it. */
void queue_drop (queue *q)                 // be careful with this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	assert (q != NULL);
	queue_node* curr = q->head;
	queue_node* tmp = q->head;
	//link temp = curr;
	while(curr!= NULL){
		tmp = curr->next;  // store the next node
		free(curr);				// free the current node
		curr=tmp;				//update the current 
	}
	/*queue_node* tmp = q->head;
	for (queue_node *curr = q->head; curr != NULL; curr = curr->next)
	    tmp = curr->next;
		free (curr);
		curr = tmp;*/
    free (q);
}

/** Add an item to the end of a Queue.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{
	queue_node *node = queue_node_new (it);
	if (q->head != NULL) {
		q->tail->next = node;
	} else {
		q->head = node;
	}
	q->tail = node;
	
	q->n_items++;
}

/** Remove an item from the front of a Queue.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	if ( q->n_items ==0){
		puts("queue underflow");
		abort();
	}
	Item it = q->head->item;
	queue_node *del = q->head;
	q->head = q->head->next;
	free (del);
	q->n_items--;
	return it;
}

/** Get the number of items in a Queue. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

static queue_node *queue_node_new (Item it)
{
	queue_node *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue_node");
	(*new) = (queue_node) { .item = it, .next = NULL };
	return new;
}

void white_box_tests (void)
{
	puts("Test 0: white_box test");
	test_with_zero_item();
	test_with_two_items();
	test_with_50_items ();
}

static void test_with_zero_item (void){
	queue *q = queue_new();
	assert(q != NULL);
	assert(q->head ==NULL);
	assert(q->tail ==NULL);
	assert(q->n_items == 0);
	printf("pass test_zero_item\n");
	queue_drop (q);
}

static void test_with_two_items (void){
	queue *q = queue_new();

	queue_en(q,1);
	assert(q->head!=NULL);
	assert(q->tail!=NULL);
	assert(q->head->item == 1);
	assert(q->tail->item == 1);
	assert(q->n_items == 1);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 1);
	
	queue_en(q,2);
	assert(q->head!=NULL);
	assert(q->tail!=NULL);
	assert(q->head->item == 1);
	assert(q->tail->item == 2);
	assert(q->n_items == 2);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 2);

	Item it = queue_de(q);
	assert (q->head->item == 2);
	assert (q->tail->item == 2);
	assert (q->n_items == 1);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 1);
	assert (it == 1);
	queue_drop (q);
	printf("pass test_with_two_items\n");

}


static void test_with_50_items (void){
	queue *q = queue_new();	
	for (int i = 0 ; i< 50;i++){
		queue_en(q,i);	
	}
	assert (q->head->item == 0);
	assert (q->tail->item == 49);
	assert (q->n_items == 50);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 50);
	for (int i = 0 ; i< 23;i++){
		Item item = queue_de(q);	
	}
	assert (q->head->item == 23);
	assert (q->tail->item == 49);
	assert (q->n_items == 27);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 27);
	queue_drop (q);
	printf("pass test_with_50_items\n");
}
