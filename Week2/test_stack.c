////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Stack ADT implementation.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

static void test_empty_stack (void);
static void test_one_item_stack (void);
static void bounds_condition_check(void);
static void pop_empty_stack_check(void);


int main (void)
{
	white_box_tests ();

	test_empty_stack ();
	test_one_item_stack ();
	bounds_condition_check ();
	pop_empty_stack_check ();
    // add more tests of your own!

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

static void test_empty_stack (void)
{
	puts ("Test 1: testing an empty stack.");
	Stack s = stack_new ();
	assert (stack_size (s) == 0);
	stack_drop (s);
}

static void test_one_item_stack (void)
{
	puts ("Test 2: testing a stack with one item.");
	Stack s = stack_new ();
	stack_push (s, 1);

	assert (stack_size (s) == 1);

	assert (stack_pop (s) == 1);
	assert (stack_size (s) == 0);

	stack_drop (s);
}
static void bounds_condition_check(void)
{
	puts("Test 3: testing the bounds condition of the stack");
	Stack s = stack_new ();
	for(int i =1;i<=100 ;i++){
		stack_push (s, i);
	}
	assert (stack_size (s) == 100);
	assert (stack_pop (s) == 100);
	assert (stack_size (s) == 99);
	assert (stack_pop (s) == 99);
	assert (stack_size (s) == 98);
	stack_drop (s);

}

static void pop_empty_stack_check(void)
{
	Stack s = stack_new ();
	puts("Test 4: testing the empty stack pop protection");
	printf("Shall we pop an empty stack?: y/n \n");
	int q = getchar();
	if ( q == 'y'){
		stack_pop(s);
	}
	else {
		assert (stack_size (s) == 0);
	}
	stack_drop (s);
}
