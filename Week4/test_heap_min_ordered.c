#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

static void test_ordered_minheaps(void);
static void test_unordered_minheaps(void);

int main (void)
{
	// Stops output being buffered;
	// we get all printf output before crashes/aborts
	setbuf (stdout, NULL);

	test_ordered_minheaps();
	test_unordered_minheaps();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}


static void test_ordered_minheaps (void)
{
	node *tree = NULL;
	puts ("ordered: test 1: empty tree");
	assert (heap_min_ordered_p (tree));

	tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	puts ("ordered: test 2: tree size 1");
	assert (heap_min_ordered_p (tree));

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 15, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("ordered: test 3: tree size 2");
	assert (heap_min_ordered_p (tree));

	node *leaf_1 = malloc (sizeof *leaf);
	(*leaf_1) = (node) { .item = 13, .left = NULL, .right = NULL };
	tree->right = leaf_1;

	puts ("ordered: test 4: tree size 3");
	assert (heap_min_ordered_p (tree));
	
	
	node *leaf_2 = malloc (sizeof *leaf);
	(*leaf_2) = (node) { .item = 27, .left = NULL, .right = NULL };
	tree->left->left = leaf_2;

	puts ("ordered: test 4: tree size 4");
	assert (heap_min_ordered_p (tree));

	node *leaf_3 = malloc (sizeof *leaf);
	(*leaf_3) = (node) { .item = 1000, .left = NULL, .right = NULL };
	tree->left->right = leaf_3;

	puts ("ordered: test 5: tree size 5");
	assert (heap_min_ordered_p (tree));

	node *leaf_4 = malloc (sizeof *leaf);
	(*leaf_4) = (node) { .item = 18, .left = NULL, .right = NULL };
	tree->right->left = leaf_4;

	puts ("ordered: test 6: tree size 6");
	assert (heap_min_ordered_p (tree));


	free (leaf_4);
	free (leaf_3);
	free (leaf_2);
	free (leaf_1);
	free (leaf);
	free (tree);
}

static void test_unordered_minheaps (void)
{
	node *tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 8, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("unordered: test 1: tree size 2");
	assert (! heap_min_ordered_p (tree));

	node *tree1 = malloc (sizeof *tree);
	(*tree1) = (node) { .item = 6, .left = NULL, .right = NULL };

	node *leaf1 = malloc (sizeof *leaf);
	(*leaf1) = (node) { .item = 8, .left = NULL, .right = NULL };
	tree->left = leaf1;

	node *leaf2 = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 4, .left = NULL, .right = NULL };
	tree->right = leaf2;
	puts ("unordered: test 1: tree size 3");
	assert (! heap_min_ordered_p (tree));
	

	free (leaf);
	free (tree);
	free (leaf1);
	free (leaf2);
	free (tree1);
	
}
