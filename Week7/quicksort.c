//21 Jan 2019 Zhengyue LIU z5036602

#include <err.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <time.h>


typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))


static void quick_sort_naive_pivot(Item item[],int lo,int hi);
static void quick_sort_randomised_pivot(Item item[],int lo,int hi);
static void quick_sort_median3_pivot(Item item[],int lo,int hi);
static inline void median_of_3(int list[], int p, int r);
static int partition(Item item[],int start,int end);
static inline void swap_idx(Item item[],int pos1,int pos2);
static inline void print_array(Item item[],size_t size);
static int random_number_generator (int max);
static int partition_median3(Item item[],int start,int end);
time_t t;
int main (int argc, char**argv)
{
	time_t t1;
	srand((unsigned) time(&t1));
	if (argc > 3 ||  argc < 2) errx (EX_USAGE, "usage: %s <pn,pm,pr> <q>", argv[0]);
	size_t n_items;
	size_t mode;
	printf("Enter the mode mode 1 user defiend input, mode 2 testing input: ");
	scanf ("%zu", &mode);
	Item *items = NULL;
	if (mode == 1){
		printf("Enter data size: ");
		scanf ("%zu", &n_items);
		items = calloc (n_items, sizeof (Item));
		if (items == NULL)
			err (EX_OSERR, "couldn't allocate %zu items", n_items);
		printf("Enter data: \n");
		for (size_t i =0 ; i < n_items; i++){
		scanf ("%d", &items[i]);
		}
		for (size_t i =0 ; i < n_items; i++){
		printf ("%d, ", items[i]);
		}
printf("\n");
	}else {
		char datatype[10] ;
		printf("Enter data size: ");
		scanf ("%zu", &n_items);
		items = calloc (n_items, sizeof (Item));
		if (items == NULL)
			err (EX_OSERR, "couldn't allocate %zu items", n_items);
		printf("Enter data type R|A|D: \n");
		scanf ("%s", datatype);
		int i = 0;

		if (strcmp(datatype,"R")==0){
			for (i = 0;i<n_items;i++){
				items[i]= rand()%n_items;
			}
		}else if (strcmp(datatype,"A")==0){
			for (i = 0;i<n_items;i++){
				items[i]= i;
			}
		}else if (strcmp(datatype,"D")==0){
			int counter = n_items;
			for (i = 0;i<n_items;i++){
				items[i]= counter--;
			}
		}
		
	}
	//puts("fdasf");
	clock_t begin = clock();
	if (strcmp(argv[1], "-pn")==0){
		quick_sort_naive_pivot(items,0,n_items-1);
		printf("Sorted with naive pivot: \n");
	}else if (strcmp(argv[1], "-pm")==0){
		quick_sort_median3_pivot(items,0,n_items-1);
		printf("Sorted with median of three pivot: \n");
		
	}else if (strcmp(argv[1], "-pr")==0){
		quick_sort_randomised_pivot(items,0,n_items-1);
		printf("Sorted with randomised pivot: \n");
	}else{
		puts("invalid method");
		return EXIT_FAILURE;
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time_spent :%f seconds\n",time_spent);


	if (argc == 3 && strcpy(argv[2], "-q")){
		return EXIT_SUCCESS;
	}
		print_array(items,n_items);
	return EXIT_SUCCESS;

}

static void quick_sort_naive_pivot(Item item[],int lo,int hi){
	if(hi<=lo) return;
	int partition_index = partition(item,lo,hi);
	quick_sort_naive_pivot(item,lo,partition_index-1);
	quick_sort_naive_pivot(item,partition_index+1,hi);
}
static void quick_sort_median3_pivot(Item item[],int lo,int hi){
	if(hi<=lo) return;
	median_of_3(item,lo,hi);
	int partition_index = partition_median3(item,lo,hi);

	quick_sort_median3_pivot(item,lo,partition_index-1);
	quick_sort_median3_pivot(item,partition_index+1,hi);
}
static void quick_sort_randomised_pivot(Item item[],int lo,int hi){
	if(hi<=lo) return;
	srand(time(NULL)); 
    int random = lo+ rand() % (hi - lo); 
	swap_idx(item,random,hi);
	int partition_index = partition(item,lo,hi);
	quick_sort_randomised_pivot(item,lo,partition_index-1);
	quick_sort_randomised_pivot(item,partition_index+1,hi);
}
static int partition(Item item[],int start,int end){
	Item pivot = item[end];
	size_t i = start, j = end-1;
	//printf("%d ",pivot);
	while(true){
		while(item[i]<=pivot && i<j){
			i++;
		}
		while(pivot<=item[j] && i<j){
			j--; 
		}
		if(i==j) break;
		swap_idx(item,i,j);
	}
	
	i = (item[j] > pivot)? j:j+1;	
	swap_idx(item,i,end);
	return i;
}
static int partition_median3(Item item[],int start,int end){
	Item pivot = item[end];
	size_t i = start, j = end-1;
	//printf("%d ",pivot);
	while(true){
		while(item[i]<=pivot && i<j){
			i++;
		}
		while(pivot<=item[j] && i<j){
			j--; 
		}
		if(i==j) break;
		swap_idx(item,i,j);
	}
	
	i = (item[j] > pivot)? j:j+1;	
	swap_idx(item,i,end);
	return i;
}
static inline void swap_idx(Item item[],int pos1,int pos2){

	int tmp = item[pos1];
	item[pos1] = item[pos2];
	item[pos2] = tmp;
}
static inline void print_array(Item item[],size_t size){
	int i = 0;
	while(i < size){
		printf("%d ",item[i]);
		i++;
	}
}
static inline void median_of_3(int a[], int lo, int hi)
{
    size_t mid = (lo + hi) / 2;
	if (less (a[mid], a[lo])) swap_idx (a, lo, mid);
	if (less (a[hi], a[mid])) swap_idx (a, mid, hi);
	if (less (a[mid], a[lo])) swap_idx (a, lo, mid);
	// now, we have a[lo] <= a[mid] <= a[hi]
	// swap a[mid] to a[lo+1] to use as pivot
	swap_idx (a, mid, hi);          

}
static int random_number_generator (int max){
	time_t t;
	srand((unsigned) time(&t));
	//printf("aaaaa%d",rand()%max);
	return rand()%max;  
}
