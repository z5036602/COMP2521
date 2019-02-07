////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A binary search tree implementation.
//
// 2018-12-08	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <z5036602@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "btree.h"
#include "item.h"
#include "item_int.h"
#include "item_btree_node.h"
#include "testable.h"
#include "queue.h"

typedef struct btree_node btree_node;
struct btree_node {
	Item item;
	btree_node *left, *right;
};

typedef struct traverse_state traverse_state;
struct traverse_state {
	btree_traversal how;
	size_t n_nodes, upto;
	btree_node **nodes;
	btree_visitor_fp visitor;
};

static btree_node *btree_node_new (Item it);

static void btree_traverse_prefix (btree_node *, traverse_state *);
static void btree_traverse_infix (btree_node *, traverse_state *);
static void btree_traverse_postfix (btree_node *, traverse_state *);
static void btree_traverse_level (btree_node *, traverse_state *);
static void btree_traverse_visit (btree_node *, traverse_state *);

// Remove `__unused' tags from your functions before flight.
#ifndef __unused
#define __unused __attribute__((unused))
#endif

////////////////////////////////////////////////////////////////////////

/** Get the value at the current binary-tree node. */
Item btree_node_value (btree_node *tree)
{
	if (tree == NULL)
		return NULL;
	else
		return tree->item;
}

/**
 * Insert a value into a binary tree, maintaining search-tree ordering;
 * duplicates are inserted to the left of the tree.
 *
 * @param tree	the btree to insert into
 * @param value	the value to insert
 * @returns the root of the resulting tree
 */
btree_node *btree_insert (btree_node *tree, Item value)			// write this god damn thing in iterative manner
{
	if (tree == NULL)
		return btree_node_new (value);

	int cmp = item_cmp (tree->item, value);
	if (cmp <  0) {
		tree->right = btree_insert (tree->right, value);
	} else /* (cmp >= 0) */ {
		tree->left  = btree_insert (tree->left, value);
	}

	return tree;
}

/**
 * Search for a value in a binary tree with search-tree ordering.
 *
 * @param tree	the btree to search in
 * @param key	the value to search for
 * @returns the node that matches the key, or `NULL' if not found.
 */
btree_node *btree_search (btree_node *tree, Item item)           // try write it in iterative manner 
{
	if (tree == NULL) return NULL;
	int cmp = item_cmp (tree->item, item);
	if (cmp == 0) return tree;
	if (cmp <  0) return btree_search (tree->right, item);
	if (cmp  > 0) return btree_search (tree->left, item);
	return NULL;
}

/**
 * Search for, and delete, a value in a binary tree, maintaining the
 * search-tree ordering.  Promote the leftmost node of the right subtree
 * on deletion where necessary.                        //whats the reason?
 *
 * @param tree	the btree to search in and delete from
 * @param key	the key to search and delete
 * @returns the root of the resulting tree
 */
btree_node *btree_delete_node (btree_node *tree, Item item)
{
	if (tree == NULL) return NULL;
	int cmp = item_cmp (tree->item, item);
	if (cmp == 0) {
		// tree has no subtrees:
		if (tree->left == NULL && tree->right == NULL)
			free(tree);//do i need to manipulate the pointer if dont 
		else if ((tree->left != NULL && tree->right == NULL) ||
				 (tree->right != NULL && tree->left == NULL)){
			btree_node* tmp = (tree->left!=NULL)? tree->left:tree->right;
			free(tree);
			return tmp;

		}	else {
			btree_node*curr = tree->right;
			while(curr->left!=NULL){
				curr=curr->left;
			}
			Item tmp_it = curr->item;
			free(curr);
			tree->item = tmp_it;
			return tree;
		}
	} else if (cmp > 0) {
		tree->left  = btree_delete_node (tree->left,  item);
	} else if (cmp < 0) {
		tree->right = btree_delete_node (tree->right, item);
	}
	
	return tree;
}

/**
 * Perform a traversal of the tree.
 *
 * @param tree	the btree to traverse
 * @param how	the ordering to use when traversing
 * @param visit	the function pointer to use when traversing,
 *              or NULL to produce an array of nodes.
 * @returns NULL if traversing with a function pointer,
 *          or a dynamically allocated array of nodes.
 */
btree_node **btree_traverse (
	btree_node *tree,
	btree_traversal how,
	btree_visitor_fp visit)
{
	traverse_state state;

	if (visit == NULL) {
		state.n_nodes = btree_size (tree);
		state.nodes = calloc (state.n_nodes, sizeof *state.nodes);
		if (state.nodes == NULL)
			err (EX_OSERR, "couldn't allocate nodes[]");
		state.upto = 0;
	}

	state.visitor = visit;
	state.how = how;

	switch (how) {
	case BTREE_TRAVERSE_PREFIX:
		btree_traverse_prefix (tree, &state);  break;
	case BTREE_TRAVERSE_INFIX:
		btree_traverse_infix (tree, &state);   break;
	case BTREE_TRAVERSE_POSTFIX:
		btree_traverse_postfix (tree, &state); break;
	case BTREE_TRAVERSE_LEVEL:
		btree_traverse_level (tree, &state);   break;
	}

	return state.nodes;
}

/** Returns the number of nodes in the tree. */
size_t btree_size (btree_node *tree)
{
	if (tree == NULL) return 0;
	return 1
		+  btree_size (tree->left)
		+  btree_size (tree->right);
}

/** Returns the number of leaf nodes in the tree. */
size_t btree_size_leaf (BTreeNode tree )
{
	if (tree == NULL) return 0;
	
	if(tree->left==NULL&&tree->right==NULL){
		return 1
			+  btree_size_leaf (tree->left)
			+  btree_size_leaf (tree->right);		
    }
	else{
		return 0
			+  btree_size_leaf (tree->left)
			+  btree_size_leaf (tree->right);
	}
}

/** Returns the height of a tree. */
size_t btree_height (btree_node *tree)
{
	if (tree == NULL) return 0;
	size_t lheight = btree_height (tree->left);
	size_t rheight = btree_height (tree->right);
	return 1
		+  ((lheight > rheight) ? lheight : rheight);   // how does it deal with equal?
}

/** Destroy a tree, releasing all resources it requires. */
void btree_drop (btree_node *tree)      //post-fix traverse
{
	if (tree==NULL) return;
	btree_drop(tree->left);
	btree_drop(tree->right);
	_int_item_drop (tree -> item);
	free(tree);
	
}

/**
 * Return the number of nodes which match the predicate.
 *
 * @param tree	the btree to traverse
 * @param pred	a function pointer to the predicate to match
 */
size_t btree_count_if (btree_node *tree, btree_pred_fp pred)
{	
	if(tree==NULL){
		return 0; 
	}	
	if(pred(tree->item)==true){
		return 1 +  btree_count_if (tree->left,pred) +  btree_count_if (tree->right,pred);		
    }
	else{
		return 0 +  btree_count_if (tree->left,pred) +  btree_count_if (tree->right,pred);
	}
	

}

////////////////////////////////////////////////////////////////////////

static btree_node *btree_node_new (Item it)
{
	btree_node *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate btree_node");
	*new = (btree_node){ .item = it, .left = NULL, .right = NULL };
	return new;
}

/**
 * Perform a prefix-order (node, left, right) traversal.
 *
 * @param tree	the btree we're traversing in
 * @param state	the current state of the traversal
 */
static void btree_traverse_prefix (
	btree_node *tree,
	traverse_state *state)
{
	if (tree == NULL) return;
	btree_traverse_visit (tree, state);
	btree_traverse_prefix (tree->left, state);
	btree_traverse_prefix (tree->right, state);
}

/**
 * Perform an infix-order (left, node, right) traversal.
 *
 * @param tree	the btree we're traversing in
 * @param state	the current state of the traversal
 */
static void btree_traverse_infix (
	btree_node *tree,
	traverse_state *state)
{
	if (tree == NULL) return;
	btree_traverse_infix (tree->left, state);
	btree_traverse_visit (tree, state);
	btree_traverse_infix (tree->right, state);
}

/**
 * Perform a postfix-order (left, right, node) traversal.
 *
 * @param tree	the btree we're traversing in
 * @param state	the current state of the traversal
 */
static void btree_traverse_postfix (
	btree_node *tree,
	traverse_state *state)
{
	if (tree == NULL) return;
	btree_traverse_postfix (tree->left, state);
	btree_traverse_postfix (tree->right, state);
	btree_traverse_visit (tree, state);
}

/**
 * Perform a level-order traversal of the tree.
 * Call `btree_traverse_visit' to visit a node.
 *
 * @param tree	the btree we're traversing in
 * @param state	the current state of the traversal
 */
static void btree_traverse_level (
	btree_node *tree,
	traverse_state *state)
{
	if (tree == NULL) return;
	Queue q = queue_new();
	queue_en (q, BTreeNode_item_new(tree));
	while(queue_size(q)>0){
		Item a = queue_de(q);
		BTreeNode tree_node = BTreeNode_item(a);
		btree_traverse_visit (tree_node, state);
		//a_btree_node_item_drop (Item it);
		if (tree_node->left!=NULL){
			queue_en (q, BTreeNode_item_new(tree_node->left));
		}
		if (tree_node->right!=NULL){
			queue_en (q, BTreeNode_item_new(tree_node->right));		
		}
		_btree_node_item_drop (a);              // how this is not affecting tree_node
	}
	queue_drop(q);
}

/**
 * Actually do the business of visiting one node.  If we are applying a
 * visitor function, apply it; if we are making an array, add this node.
 *
 * @param tree	the btree we're traversing in
 * @param state	the current state of the traversal
 */
static void btree_traverse_visit (
	btree_node *tree,
	traverse_state *state)
{
	assert (tree != NULL);

	if (state->visitor != NULL) {
		state->visitor (tree);
	} else {
		assert (state->upto <  state->n_nodes);
		state->nodes[state->upto++] = tree;
		assert (state->upto <= state->n_nodes);
	}
}

bool even_p (Item it){        //added
	int value = int_item(it);
	return (value%2 ==0)? 1:0;
}

bool odd_p(Item it){
	int value = int_item(it);
	return (value%2 ==0)? 0:1;
}

bool negative_p(Item it){
	int value = int_item(it);
	return (value<0)? 1:0;
}
////////////////////////////////////////////////////////////////////////

void white_box_tests (void)
{
	puts("white box tests");
	BTreeNode root = NULL;
	size_t size_leaf = btree_size_leaf (root);
	size_t number_of_even_1 = btree_count_if (root, even_p);
	size_t number_of_odd_1  = btree_count_if (root, odd_p);
	size_t number_of_negative_1  = btree_count_if (root, negative_p);
	assert(root == NULL);
	
	root = btree_insert (root, _int_item_new(6));
	assert(int_item(root->item) == 6);
	assert(root->left ==NULL);
	assert(root->right ==NULL);
	size_leaf = btree_size_leaf (root);
	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	BTreeNode *nodes = btree_traverse (root, BTREE_TRAVERSE_LEVEL, NULL);
	assert(int_item(root->item) == 6);
	assert(root->left ==NULL);
	assert(root->right ==NULL);
	free(nodes);
	
	root = btree_insert (root, _int_item_new(3));
	assert(int_item(root->item) == 6);
	assert(int_item(root->left->item) ==3);
	assert(root->right ==NULL);
	size_leaf = btree_size_leaf (root);
	number_of_even_1 = btree_count_if (root, even_p);
	number_of_odd_1  = btree_count_if (root, odd_p);
	number_of_negative_1  = btree_count_if (root, negative_p);
	nodes = btree_traverse (root, BTREE_TRAVERSE_LEVEL, NULL);
	assert(int_item(root->item) == 6);
	assert(int_item(root->left->item) ==3);
	assert(root->left->left ==NULL);
	assert(root->left->right ==NULL);
	assert(root->right ==NULL);
	free(nodes);
	btree_drop(root);

	puts("all passed");
}
