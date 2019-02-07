////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Queue ADT implementation.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

static void test_empty_queue (void);
static void test_one_item_stack (void);
static void test_three_items_stack (void);
static void test_bounds_condition_queue(void);
static void deque_empty_queue(void);

int main (void)
{
	white_box_tests ();
	test_empty_queue();
	test_one_item_stack();
	test_three_items_stack();
	//test_bounds_condition_queue();
	deque_empty_queue();
	test_bounds_condition_queue();
	// add more tests of your own!

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}
static void test_empty_queue (void){
	puts ("Test 1: testing an empty queue.");
	Queue q = queue_new();
	assert (queue_size(q) == 0);
	queue_drop(q);
}
static void test_one_item_stack (void){
	puts ("Test 2: testing a queue with one item.");
	Queue q = queue_new ();
	queue_en (q, 1);

	assert (queue_size (q) == 1);

	assert (queue_de (q) == 1);
	assert (queue_size (q) == 0);

	queue_drop (q);
}
static void test_three_items_stack (void){
	puts ("Test 3: testing a queue with three items.");
	Queue q = queue_new ();
	queue_en (q, 1);
	queue_en (q, 2);
	queue_en (q, 3);
	assert (queue_size (q) == 3);
	assert (queue_de (q) == 1);
	assert (queue_size (q) == 2);
	assert (queue_de (q) == 2);
	assert (queue_size (q) == 1);
	assert (queue_de (q) == 3);
	assert (queue_size (q) == 0);
	queue_drop (q);
}
static void test_bounds_condition_queue(void){
	puts("Test 5: testing the bounds condition of the queue");
	Queue q = queue_new ();
	for(int i =1;i<=15 ;i++){
		queue_en (q, i);
	}
	assert (queue_size (q) == 15);
	assert (queue_de (q) == 1);
	assert (queue_size (q) == 14);
	assert (queue_de (q) == 2);
	assert (queue_size (q) == 13);
	queue_drop (q);
}

static void deque_empty_queue(void){
	Queue q = queue_new ();
	assert (queue_size (q) == 0);
	puts ("Test 4: trying to deque a empty queue.");
	printf("Shall we deque an empty queue?: y/n \n");
	int o = getchar();
	if ( o == 'y'){
		queue_de(q);
	}
	else {
		assert (queue_size (q) == 0);
	}
	queue_drop (q);
}


//static void deque_empty_queue(void){
//	puts(

//}
