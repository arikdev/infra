#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack stack_t;

typedef enum STACK_CODE {
	STACK_OK = 0,
	STACK_EMPTY,
	STACK_ERROR,
} stack_code_e;

int stack_push(stack_t **s, void *data);
int stack_pop(stack_t **s, void **data);
int stack_peek(stack_t **s, void **data);


#endif
