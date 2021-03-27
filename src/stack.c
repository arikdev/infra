#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack {
	void *data;
	struct stack *next;
};

int stack_push(stack_t **s, void *data)
{
	stack_t *new_node;

	if (!(new_node = malloc(sizeof(stack_t))))
		return STACK_ERROR;
	new_node->data = data;
	new_node->next = *s;
	*s = new_node;

	return STACK_OK;
}

int stack_pop(stack_t **s, void **data)
{
	stack_t *del;

	if (!*s)
		return STACK_EMPTY;
	*data = (*s)->data;
	del = *s;
	*s = (*s)->next;
	free(del);

	return STACK_OK;
}

int stack_peek(stack_t **s, void **data)
{
	if (!*s)
		return STACK_EMPTY;
	*data = (*s)->data;

	return STACK_OK;
}
