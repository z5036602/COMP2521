// COMP2521 19T0 ... lab 01: test a linked list implementation
//
// 2018-11-22	Zhengyue LIU <z5036602@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists.h"

void test_zero_node_ll (void);
void test_one_node_ll (void);
void test_two_node_ll (void);
void test_three_node_ll(void);
	
void test_zero_node_cl(void);
void test_one_node_cl(void);
void test_four_node_cl(void);
void test_six_node_cl(void);

void test_zero_node_dl(void);
void test_one_node_dl(void);
void test_three_node_dl(void);



int main (void)
{
	// Creates an empty list, and then prints it.
	link list = NULL;                // this is the zero node testing ?
	list_print (list);
	
		
	// You should write some tests here. (And remove this comment.)
	test_zero_node_ll();
	test_one_node_ll();
	test_two_node_ll();
	test_three_node_ll();

	test_zero_node_cl();
	test_one_node_cl();
	test_four_node_cl();
	test_six_node_cl();
	
	test_zero_node_dl();
	test_one_node_dl();
	test_three_node_dl();

	return EXIT_SUCCESS;
}

void test_zero_node_ll (void){
	printf("Test zero node linkedlist: \n");
	link list = NULL;                // this is the zero node testing ?
	list_print (list);
	int c = list_sum_items(list);
	printf("The sum is %d\n",c);
	list_drop (list);
	
}	
void test_one_node_ll (void) {
	printf("Test single node with value 1,0,-1: \n");
	Item N_1_val = 1;
	Item N_2_val = 0;
	Item N_3_val = -1;
	link node_1 = node_new (N_1_val);
	list_print (node_1);
	int c = list_sum_items(node_1);
	printf("The sum is %d\n",c);
	//list_drop(node_1);
	link node_2 = node_new (N_2_val);
	list_print (node_2);
	c = list_sum_items(node_2);
	printf("The sum is %d\n",c);
	link node_3 = node_new (N_3_val);
	list_print (node_3);
	c = list_sum_items(node_3);
	printf("The sum is %d\n",c);
	list_drop(node_1);
	list_drop(node_2);
	list_drop(node_3);
	
}

void test_two_node_ll (void){
	printf("Test two node with value 1,-1: \n");
	Item N_1_val = 1;
	Item N_2_val = -1;
	link node_1 = node_new (N_1_val);
	link node_2 = node_new (N_2_val);
	list_insert_next (node_1 ,node_2);
	list_print (node_1);
	int c = list_sum_items(node_1);
	printf("The sum is %d\n",c);
	list_drop(node_1);
}


void test_three_node_ll(void){
	printf("Test three node with value 1,0,-1: \n");
	Item N_1_val = 1;
	Item N_2_val = 0;
	Item N_3_val = -1;
	link node_1 = node_new (N_1_val);
	link head = node_1;
	link node_2 = node_new (N_2_val);
	link node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);
	list_print(head);
	int c = list_sum_items(head);
	printf("The sum is %d\n",c);
	list_drop (head);

	printf("Test three node with value 1,2,3: \n");
	N_1_val = 1;
	N_2_val = 2;
	N_3_val = 3;
	node_1 = node_new (N_1_val);
	head = node_1;
	node_2 = node_new (N_2_val);
	node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);
	list_print(head);
	c = list_sum_items(head);
	printf("The sum is %d\n",c);
	list_drop (head);
	printf("Test three node with value -1,-2,-3: \n");
	N_1_val = -1;
	N_2_val = -2;
	N_3_val = -3;
	node_1 = node_new (N_1_val);
	head = node_1;
	node_2 = node_new (N_2_val);
	node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);
	list_print(head);
	c = list_sum_items(head);
	printf("The sum is %d\n",c);
	list_drop (head);
}
void test_zero_node_cl(void){
	printf("Test the 0 node clist: \n");
	link circular_list = clist_new(0);
	clist_print(circular_list);
	list_drop(circular_list);
}

void test_one_node_cl(void){
	printf("Test the 1 node clist: \n");
	link circular_list = clist_new(1);
	clist_print(circular_list);
	list_drop(circular_list);
}

void test_four_node_cl(void){
	printf("Test the 4 nodes clist: \n");
	link circular_list = clist_new(4);
	clist_print(circular_list);
	clist_print(circular_list->next);
	clist_print(circular_list->next->next);
	clist_print(circular_list->next->next->next);
	list_drop(circular_list);
}
	
void test_six_node_cl(void){
	printf("Test the 6 nodes clist: \n");
	link circular_list = clist_new(6);
	clist_print(circular_list);
	clist_print(circular_list->next);
	clist_print(circular_list->next->next);
	clist_print(circular_list->next->next->next);
	clist_print(circular_list->next->next->next->next);
	clist_print(circular_list->next->next->next->next->next);
	list_drop(circular_list);
}

void test_zero_node_dl(void){
	printf("Test the zero node dlist: \n");
	link list = NULL;
	dlink d_list = dlist_new_from_list (list);
	dlist_print(d_list);
	list_drop(list);
	dlist_drop(d_list);
}
void test_one_node_dl(void) {
	printf("Test the one node dlist: \n");
	Item N_1_val = 1;
	link node_1 = node_new (N_1_val);	
	dlink d_list = dlist_new_from_list (node_1);
	dlist_print(d_list);
	list_drop(node_1);
	dlist_drop(d_list);
}

void test_three_node_dl(void){
	printf("Test the three node dlist: \n");
	Item N_1_val = 1;
	Item N_2_val = 2;
	Item N_3_val = 3;
	link node_1 = node_new (N_1_val);
	link head = node_1;
	link node_2 = node_new (N_2_val);
	link node_3 = node_new (N_3_val);
	list_insert_next (head ,node_2);
	list_insert_next (node_2,node_3);	
	dlink d_list = dlist_new_from_list (head);
	dlist_print(d_list);
	list_drop(head);
	dlist_drop(d_list);
}





