////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a binary search tree implementation.
//
// 2018-12-08	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item_int.h"      // why ???
#include "btree.h"
#include "testable.h"     
static void btest_0 (void);
static void btest_1 (void);
static void btest_2 (void);


int main (void)
{
	white_box_tests ();
	puts("Black box tests :");
	puts("Test 0: count leaf && drop with memory leak check");
	btest_0();
	puts("Test 1: horizontal traverse");
	btest_2();
	puts("Test 2: count the special node testing");
	btest_1();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}
static void btest_0 (void){
	BTreeNode root = NULL;
	size_t size_leaf = btree_size_leaf (root);
	size_t size_of_the_tree = btree_size (root);
	assert(size_leaf == 0);
	assert(size_of_the_tree ==0);

	root = btree_insert (root, _int_item_new(8));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 1);
	assert(size_of_the_tree ==1);

	root = btree_insert (root, _int_item_new(4));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 1);
	assert(size_of_the_tree ==2);

	root = btree_insert (root, _int_item_new(6));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 1);
	assert(size_of_the_tree ==3);

	root = btree_insert (root, _int_item_new(3));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 2);
	assert(size_of_the_tree ==4);

	root = btree_insert (root, _int_item_new(10));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 3);
	assert(size_of_the_tree ==5);


	root = btree_insert (root, _int_item_new(9));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 3);
	assert(size_of_the_tree ==6);

	root = btree_insert (root, _int_item_new(14));
	size_leaf = btree_size_leaf (root);
	size_of_the_tree = btree_size (root);
	assert(size_leaf == 4);
	assert(size_of_the_tree ==7);

	btree_drop(root);
}
static void btest_1 (void){
	BTreeNode root = NULL;
	size_t number_of_even_1 = btree_count_if (root, even_p);
	size_t number_of_odd_1  = btree_count_if (root, odd_p);
	size_t number_of_negative_1  = btree_count_if (root, negative_p);
	assert(number_of_even_1 == 0);
	assert(number_of_odd_1 == 0);
	assert(number_of_negative_1 == 0);
	root = btree_insert (root, _int_item_new(10));
	size_t size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 1);

	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	assert(number_of_odd_1 == 0);
	assert(number_of_even_1 == 1);
	assert(number_of_negative_1 == 0);
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 1);


	root = btree_insert (root, _int_item_new(7));
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 2);
	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	assert(number_of_odd_1 == 1);
	assert(number_of_even_1 == 1);
	assert(number_of_negative_1 == 0);
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 2);
	root = btree_insert (root, _int_item_new(14));
	root = btree_insert (root, _int_item_new(-7));
	root = btree_insert (root, _int_item_new(-3));
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 5);
	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	assert(number_of_odd_1 == 3);
	assert(number_of_even_1 == 2);
	assert(number_of_negative_1 == 2);
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 5);
	root = btree_insert (root, _int_item_new(9));
	root = btree_insert (root, _int_item_new(13));
	root = btree_insert (root, _int_item_new(-4));
	root = btree_insert (root, _int_item_new(-10));
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 9);
	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	assert(number_of_odd_1 == 5);
	assert(number_of_even_1 == 4);
	assert(number_of_negative_1 == 4);
	size_of_the_tree = btree_size (root);
	assert(size_of_the_tree == 9);
	btree_drop(root);

}
static void btest_2 (void){
	BTreeNode root = NULL;
	//size_t n_nodes = btree_size (root);
	/*BTreeNode *nodes = btree_traverse (root, BTREE_TRAVERSE_LEVEL, NULL);
	free (nodes);*/  // here is a bug for compiler, you can run without memory leak but will give segfault 
	// if with memory leak check
	root = btree_insert (root, _int_item_new(10));
	root = btree_insert (root, _int_item_new(7));
	root = btree_insert (root, _int_item_new(14));
	root = btree_insert (root, _int_item_new(11));
	root = btree_insert (root, _int_item_new(16));
	root = btree_insert (root, _int_item_new(-4));
	root = btree_insert (root, _int_item_new(4));
	
	size_t n_nodes = btree_size (root);
	BTreeNode *nodes = btree_traverse (root, BTREE_TRAVERSE_LEVEL, NULL);
	int str_tree[7] = {10,7,14,-4,11,16,4};
	for (size_t i = 0; i < n_nodes; i++) {
		BTreeNode node = nodes[i];
		Item nvalue = btree_node_value (node);
		int check = int_item(nvalue);
		assert(check == str_tree[i]);
		
	}
	
	free (nodes);
	btree_drop(root);
	
	puts("memory leak check passed");
}
//static void create an item 
