////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using arrays.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd   Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

#define DEFAULT_SIZE 10

typedef struct queue queue;

struct queue {
	size_t n_items;
	size_t capacity;
	Item *items;
	size_t front;
	size_t back;
};


static void test_with_zero_item (void);
static void test_with_two_items (void);
static void test_with_rotating_items (void);
/** Create a new, empty Stack.  $ O(1) $. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .capacity = DEFAULT_SIZE, .front =0 , .back = 0};

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate queue items");

	return new;
}

/** Destroy a Queue.  $ O(1) $. */
void queue_drop (queue *q)
{
	assert (q != NULL);
	free (q->items);
	free (q);
}


/** Add an item to the end of a Queue.  $ O(1) $.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{
	assert (q != NULL);
	assert (q->n_items < q->capacity);
	q->items[q-> back % q->capacity] = it;
	q->n_items++;
	q->back++;
}

/** Remove an item from the front of a Queue.  $ O(n) $.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	assert (q != NULL);
	if (q->n_items == 0) {
		fprintf (stderr, "queue underflow!\n");
		abort();
	}

	// shift the elements across
	Item it = q->items[q->front % q->capacity];
	q->front++;
	q->n_items--;
	//for (size_t i = 0; i < q->n_items; i++)
	//	q->items[i] = q->items[i + 1];

	return it;
}

/** Get the number of items in a Queue.  $ O(1) $. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

void white_box_tests (void)
{
	puts("Test 0: white_box test");
	test_with_zero_item();
	test_with_two_items();
	test_with_rotating_items();
}	



static void test_with_zero_item (void){
	queue *q = queue_new();
	assert (q->capacity == DEFAULT_SIZE);
	assert (q!=NULL);
	assert (q->items != NULL);		
	assert (q->n_items == 0);
	printf("pass test_zero_item\n");
	queue_drop (q);
}
static void test_with_two_items (void){
	queue *q = queue_new();
	queue_en(q,1);
	assert (q->items[0] == 1);
	assert (q->items[q->front] == 1);
	//assert (q->items[q->back] == 1);
	assert (q->n_items == 1);
	assert (q->capacity == DEFAULT_SIZE);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 1);



	queue_en(q,2);
	assert (q->items[0] == 1);
	assert (q->items[1] == 2);
	assert (q->n_items == 2);
	assert (q->capacity == DEFAULT_SIZE);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 2);
	

	
	Item it = queue_de (q);
	assert (q->items[q->front] == 2);
	assert (q->n_items == 1);
	assert (q->capacity == DEFAULT_SIZE);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 1);
	assert (it == 1);
	printf("pass test_two_items\n");
	/*	int i = 0;
	while (i < 9){
		queue_en(q,i);
		i++;
	}
	i=0;
	while(i<10){
		printf("%d",q->items[i]);
		i++;
	}
	printf("pass test_two_items\n");*/
	queue_drop (q);
}
static void test_with_rotating_items (void){
	queue *q = queue_new();	
	for (int i = 0 ; i< 7;i++){
		queue_en(q,i);	
	}
	assert (q->items[q->front % q->capacity] == 0);
	assert (q->items[(q-> back % q->capacity)-1] == 6);
	assert (q->n_items == 7);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 7);
	for (int i = 0 ; i< 4;i++){
		Item it = queue_de (q);
	}
	assert (q->items[q->front % q->capacity] == 4);
	assert (q->items[(q-> back % q->capacity)-1] == 6);
	assert (q->n_items == 3);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 3);
	for (int i = 0 ; i< 6;i++){
		 queue_en (q,i);
	}
	assert (q->items[q->front % q->capacity] == 4);
	assert (q->items[(q-> back % q->capacity)-1] == 5);
	assert (q->n_items == 9);
	assert (queue_size(q) == q->n_items);
	assert (q->n_items == 9);
	queue_drop (q);
	printf("pass test_with_rotating_items\n");
}



