#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>

typedef struct heap heap_t;

heap_t *heap_new(int data[], int n);
void heap_print(heap_t *heap);
bool heap_is_valid(heap_t *heap);
int heap_insert(heap_t *heap, int i);
int heap_remove(heap_t *heap, int *val);
int heap_peek(heap_t *heap, int *val);

#endif 
