#include <stdbool.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

/**
 * Returns 1 if the tree-based heap is in min-heap order.
 * You may assume an empty tree is in min-heap order.
 * You may assume a single node is in min-heap order.
 */
bool heap_min_ordered_p (node *tree)
{
	if (tree==NULL) {return true;}
	//if(tree->left==NULL &&tree->right==NULL) return true;
	if(tree->left  !=NULL &&tree->left->item < tree->item) {return false;}
	if(tree->right !=NULL &&tree->right->item <tree->item){return false;}
	return heap_min_ordered_p (tree->left) && heap_min_ordered_p (tree->right);
}
