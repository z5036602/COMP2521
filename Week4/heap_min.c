#include <stdbool.h>
#include <stdlib.h>

#include "heap_min.h"

/**
 * Return `true` if the array heap with a sepcified number of items is
 * in heap order.  You must assume that the heap items are in indexes
 * 1..heap_size, and that index 0 is empty and not used to store items.
 */
bool heap_min_p (int heap[], size_t heap_size)
{
	if (heap_size==0 || heap_size == 1){
		return true;
	}
	int k = heap_size;
	while (k  > 1) {
		if (heap[k/2] > heap[k])return false;
		k--;
	}
	return true;
}
