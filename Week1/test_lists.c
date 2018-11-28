// COMP2521 19T0 ... lab 01: test a linked list implementation
//
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists.h"

//void (

int main (void)
{
	// Creates an empty list, and then prints it.
	link list = NULL;
	list_print (list);
	
		
	// You should write some tests here. (And remove this comment.)
	Item N_1_val = 1;
	Item N_2_val = 3;
	Item N_3_val = 3;
	link node_1 = node_new (N_1_val);
	link head = node_1;
	link node_2 = node_new (N_2_val);
	link node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);
	list_print(head);
	int c = list_sum_items(head);
	printf("%d\n",c);
	//list_drop (head);

	link circular_list = clist_new(7);
	clist_print(circular_list->next->next);

	dlink d_list = dlist_new_from_list (head);
	printf("dfdf\n");
	dlist_print(d_list); 
	//list_drop(circular_list);
	//c = list_sum_items(circular_list);                 // segmentation fault??
	//printf("%d\n",c);
	/*Item N_1_val = 1;
	Item N_2_val = 0;
	Item N_3_val = 3;
	link node_1 = node_new (N_1_val);
	link head = node_1;
	link node_2 = node_new (N_2_val);
	link node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);
	list_print(head);*/

	return EXIT_SUCCESS;
}
