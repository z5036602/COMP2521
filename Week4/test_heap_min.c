#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap_min.h"

static void test_valid_minheaps (void);
static void test_invalid_minheaps (void);

int main (void)
{
	// Stops output being buffered;
	// we get all printf output before crashes/aborts
	setbuf (stdout, NULL);

	test_valid_minheaps ();
	test_invalid_minheaps ();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}


static void test_valid_minheaps (void)
{
	int heap1[] = { 0, 2, 10 };

	puts ("valid minheaps: test 1: 2,10");
	assert (heap_min_p (heap1, 2));

	int heap2[] = {0};

	puts ("valid minheaps: test 2: empty heap");
	assert (heap_min_p (heap2, 0));

	int heap3[] = {0,0};

	puts ("valid minheaps: test 3: 0");
	assert (heap_min_p (heap3, 1));

	int heap4[] = {0,6};
	puts ("valid minheaps: test 3: 6");
	assert (heap_min_p (heap4, 1));

	int heap5[] = {0,1,2,3,17,19,36,7,25,100};
	puts ("valid minheaps: test 3: 1,2,3,17,19,36,7,25,100");
	assert (heap_min_p (heap5, 9));

	int heap6[] = {0,-23,-11,3,17,-3,36,7,25};
	puts ("valid minheaps: test 3: -23,-11,3,17,-3,36,7,25");
	assert (heap_min_p (heap6, 8));
}

static void test_invalid_minheaps (void)
{
	int heap1[] = { 0, 10, 7, 6 };

	puts ("invalid minheaps: test 1: 10,7,6");
	assert (! heap_min_p (heap1, 3));

	int heap2[] = {0,2,1,3,17,19,36,7,25,100};
	puts ("invalid minheaps: test 3: 1,2,3,17,19,36,7,25,100");
	assert (!heap_min_p (heap2, 9));

	int heap3[] = {0,-23,-11,3,17,-36,36,7,25};
	puts ("invalid minheaps: test 3: -23,-11,3,17,-3,36,7,25");
	assert(!heap_min_p (heap3, 8));
}
