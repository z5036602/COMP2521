// COMP2521 19T0 ... lab 01: a linked list implementation
//
// 2018-11-24	Jashank Jeremy <jashank.jeremy@unsw.edu.au>
// 2018-11-28	Zhengyue LIU LIU <z5036602@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

// Remove `__unused' tags from your functions before flight.

#define __unused __attribute__((unused))

#include "lists.h"

/** Traverses and prints the list. */
void list_print (link list)
{
	link curr = list;
	while (curr != NULL) {
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	puts ("|");
}

/** Create a new node, initialised with the item provided.
 * Return a pointer to node (link) */
link node_new (Item item)
{
	link n= malloc(sizeof (*n));
	if (n==NULL)
		err(1,"not enough space");
	n->item = item;
	n->next = NULL;
	return n;
}

/** Insert a new node into a given non-empty list.
 * The node is inserted directly after the head of the list. */
void list_insert_next (link list, link node)
{
	assert(list!= NULL);
	assert(node!= NULL);
	node->next = list->next;
	list -> next = node;
}

/** Return the sum of all items in list */
int list_sum_items (link list)
{
	int sum = 0;
	link curr = list;
	while(curr!=NULL){
		sum+=curr->item;
		curr = curr->next;
	}
	return sum;
}

/** Frees all memory used in the list */
void list_drop (link list)
{	
	assert (list!=NULL);
	link curr = list;
	//link temp = curr;
	while(curr!=NULL && curr->next !=list){
		link temp = curr->next;  // store the next node
		free(curr);				// free the current node
		curr=temp;				//update the current 
	}
	//if(temp->next == list){
		//free(temp);
	//}
}


/** Create a circular list with the specified number of nodes,
 * with each link storing data from 1 to the number of nodes. */
link clist_new (int n_nodes)
{	
	int item;
	if (n_nodes == 0) return NULL;
	link curr = node_new(0);
	link head = curr;
	for(int i = 1;i < n_nodes;i++){
		item = i;
		curr->next = node_new (item);
		
		//link new_node = node_new (item);
		curr = curr->next;

	}
	curr->next = head;
	return head;
}

/** print the data in a circular fashion starting from any node */
void clist_print (link starting_node)
{
	link curr = starting_node;
	printf ("[%d]->", curr->item);
	curr = curr->next;
	while (curr!=starting_node){
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	puts ("|");
}


/** Create a double-linked list which contains the same values,
 * in the same order as 'list' */
dlink dlist_new_from_list (link list)
{
	dlink node = malloc(sizeof(*node));
//	dlink node = malloc(sizeof(*node))
	if (node==NULL){
			err(1,"not enough space");
	}
	node->item = list->item;
	node->next = NULL;
	node->prev = NULL;
	dlink temp_head = node;
	dlink temp = node;
	link curr = list->next;
	while ( curr != NULL){
		temp = node;
		node = malloc(sizeof(*node));
		if (node==NULL){
			err(1,"not enough space");
		}
		temp ->next = node;
		node ->prev = temp;
		node ->next = NULL;
		node ->item = curr->item;
	
		curr = curr->next;
		
	}
	

	
	return temp_head;
}

/** Print a doubly-linked list. */
void dlist_print (dlink list)
{
	dlink curr = list;
	dlink temp = curr;
	while (curr != NULL) {
		temp = curr;
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	puts ("|");
	curr = temp;
	while (curr != NULL) {
		printf ("[%d]->", curr->item);
		curr = curr->prev;
	}
	puts("|");
}

/** Frees all the memory used in the double-linked list */
void dlist_drop (dlink list __unused)
{


	
	return;
}
