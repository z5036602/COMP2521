////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Stack ADT implementation, using arrays.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// 2018-3-12   Zhengyue LIU <z5036602@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

#define DEFAULT_SIZE 10

typedef struct stack stack;

struct stack {
	size_t n_items;
	size_t capacity;
	Item *items;
};
static void test_zero_item(void);
static void test_two_items_push_pop(void);
static void test_expand_shrink(void);
/** Create a new, empty Stack. */
stack *stack_new (void)
{
	stack *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate stack");

	(*new) = (stack) { .n_items = 0, .capacity = DEFAULT_SIZE };

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate stack items");

	return new;
}

/** Destroy a Stack. */
void stack_drop (stack *s)
{
	assert (s != NULL);
	free (s->items);
	free (s);
}

/** Add an item to the top of a Stack. */
void stack_push (stack *s, Item it)
{
	assert (s != NULL);
	if (s->n_items >= s->capacity){
		s->capacity = s->capacity *2;
		s->items = realloc(s->items,s->capacity*sizeof (Item));
	}

	//printf("%d\n",s->n_items);
	//printf("%d\n",s->capacity);
    
	s->items[s->n_items] = it; //did it miss a one ?				 
	s->n_items++;							
	return;
}

/** Remove an item from the top of a Stack. */
Item stack_pop (stack *s)					 
{
	
	assert (s != NULL);
	if(s->n_items == 0){
		printf("stack underflow\n");
		abort();
	}
	
	Item it = s->items[s->n_items - 1];  // isnt the number still there?
	s->n_items--;
	if(s -> n_items < 0.25 * s->capacity && s->capacity > DEFAULT_SIZE){
		s->capacity = s -> capacity /2;   
		s->items = realloc(s->items,s->capacity*sizeof (Item));
	}
	return it;
}

/** Get the number of items in a Stack. */
size_t stack_size (stack *s)
{
	assert (s != NULL);
	return s->n_items;
}

void white_box_tests (void)
{
	puts("Test 0: white_box test");
	test_zero_item();
	test_two_items_push_pop();
    test_expand_shrink();
}
	


static void test_zero_item(void){
	Stack s = stack_new();
	assert (s->capacity == DEFAULT_SIZE);
	assert (s!=NULL);
	assert (s->items != NULL);
	printf("pass test_zero_item\n");
	assert (s->n_items == 0);
	stack_drop(s);
}
static void test_two_items_push_pop(void){
	stack *s = stack_new();
	stack_push(s,1);
	assert (s->items[0] == 1);
	assert (s->n_items == 1);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 1);
//	printf("pass\n");	

	stack_push(s,2);
	assert (s->items[0] == 1);
	assert (s->items[1] == 2);
	assert (s->n_items == 2);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 2);
//	printf("pass 2\n");

	Item it = stack_pop (s);
	assert (s->items[0] == 1);
	assert (s->n_items == 1);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 1);
	assert (it == 2);
	printf("pass test_two_items_push_pop\n");
	stack_drop (s);

}

static void test_expand_shrink(void){
	stack *s = stack_new();

//	printf("pass\n");

	stack_push(s,1);
//	printf("pass\n");	

	stack_push(s,2);
//	printf("pass 2\n");

	Item it = stack_pop (s);

	for (int i = 0 ; i< 10;i++){
		stack_push(s,i);	
	}
	assert (s->items[0] == 1);
	assert (s->items[1] == 0);
	assert (s->n_items == 11);
	assert (s->capacity == 20);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 11);
	
	for (int i = 0 ; i< 30;i++){
		stack_push(s,i);	
	}
	for (int i = 0 ; i< 23;i++){
		stack_pop(s);	
	}
	assert (s->n_items == 18);
	assert (s->capacity == 40);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 18);
	stack_drop (s);
	printf("pass test_expand_shrink\n");
}

	/*stack *s = stack_new();
	assert (s->capacity == DEFAULT_SIZE);
	assert (s!=NULL);
	assert (s->items != NULL);
	assert (s->n_items == 0);
//	printf("pass\n");

	stack_push(s,1);
	assert (s->items[0] == 1);
	assert (s->n_items == 1);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 1);
//	printf("pass\n");	

	stack_push(s,2);
	assert (s->items[0] == 1);
	assert (s->items[1] == 2);
	assert (s->n_items == 2);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 2);
//	printf("pass 2\n");

	Item it = stack_pop (s);
	assert (s->items[0] == 1);
	assert (s->n_items == 1);
	assert (s->capacity == DEFAULT_SIZE);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 1);
	assert (it == 2);

	for (int i = 0 ; i< 10;i++){
		stack_push(s,i);	
	}
	assert (s->items[0] == 1);
	assert (s->items[1] == 0);
	assert (s->n_items == 11);
	assert (s->capacity == 20);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 11);
	
	for (int i = 0 ; i< 30;i++){
		stack_push(s,i);	
	}
	for (int i = 0 ; i< 23;i++){
		stack_pop(s);	
	}
	assert (s->n_items == 18);
	assert (s->capacity == 40);
	assert (stack_size(s) == s->n_items);
	assert (s->n_items == 18);
	stack_drop (s);*/
//printf("pass\n");
	/*size_t i = 0;
	while (i < s->capacity){
		assert(s->items[i] == 0);
		printf("%d\n",s->items[i]);
		i++;
	}*/  // calloc all the value on the index should be zero 
		
	/* i = 0;
	while (i < s->n_items){
		printf("%d" ,s->items[i]);
		i++;
	}
	printf("\n");*/

//	printf("pass\n");
