#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define HRAP_BLOCK_SIZE 1024

struct heap {
	int allocated;
	int size;
	int *heap;
};

static void __sift_down(int curInd, int endInd, int heap[])
{
	int i, tmp, leftSon, small;

	for (leftSon = curInd * 2 + 1; leftSon <= endInd; leftSon = curInd * 2 + 1) {
		small = leftSon == endInd || heap[leftSon] <= heap[leftSon + 1] ? leftSon : leftSon + 1;
		if (heap[curInd] < heap[small])
			break;
		tmp = heap[curInd];
		heap[curInd] = heap[small];
		heap[small] = tmp;
		curInd = small;
	}
}

static void __sift_up(int curInd, int heap[])
{
	int father, tmp;

	for (father = (int)((curInd - 1) / 2); father >= 0; father = (int)((curInd - 1) / 2)) {
		if (heap[father] <= heap[curInd])
			break;
		tmp = heap[father];
		heap[father] = heap[curInd];
		heap[curInd] = tmp;
		curInd = father;
	}
}

heap_t *heap_new(int data[], int n)
{
	heap_t *new_heap;
	int i;

	if (!(new_heap = malloc(sizeof(heap_t))))
		return NULL;
	new_heap->allocated = MAX(HRAP_BLOCK_SIZE, n);
	if (!(new_heap->heap = malloc(sizeof(int) * new_heap->allocated))) {
		free(new_heap);
		return NULL;
	}
	new_heap->size = n;
	memcpy(new_heap->heap, data, n * sizeof(int));

	for (i = (int)((n - 2)  / 2); i >= 0; i--)
		__sift_down(i, new_heap->size - 1, new_heap->heap);

	return new_heap;
}

int heap_insert(heap_t *heap, int i)
{
	if (heap->size == heap->allocated) { 
		heap->allocated += HRAP_BLOCK_SIZE;
		if (!(heap->heap = realloc(heap->heap, heap->allocated)))
			return -1;
	}
	heap->heap[heap->size] = i;
	heap->size++;
	__sift_up(heap->size - 1, heap->heap);
}

int heap_remove(heap_t *heap, int *val)
{
	if (!heap->size)
		return -1;

	*val = heap->heap[0];
	heap->heap[0] = heap->heap[heap->size - 1];
	heap->size--;
	__sift_down(0, heap->size - 1, heap->heap);

	return 0;
}

int heap_peek(heap_t *heap, int *val)
{
	if (!heap->size)
		return -1;

	*val = heap->heap[0];

	return 0;
}

void heap_print(heap_t *heap)
{
	int i, next_level = 1;

	for (i = 0; i < heap->size; i++) {
		printf("%d ", heap->heap[i]);
		if (i + 1 == next_level) {
			printf("\n");
			next_level = next_level * 2 + 1;
		}
	}
	printf("\n");
}

bool heap_is_valid(heap_t *heap)
{
	int i, leftSonInd;

	for (i = 0; i < heap->size; i++) { 
		leftSonInd = i * 2 + 1;
		if (leftSonInd >= heap->size)
			return true;
		if (heap->heap[i] > heap->heap[leftSonInd]) {
			printf("FFF i:%d leftson:%d \n", heap->heap[i], heap->heap[leftSonInd]);
			return false;
		}
		if (leftSonInd == heap->size - 1)
			return true;
		if (heap->heap[i] > heap->heap[leftSonInd + 1]) {
			printf("FFF i:%d leftson + 1:%d \n", heap->heap[i], heap->heap[leftSonInd + 1]);
			return false;
		}
	}

	return true;
}
