#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list_node {
        void *data;
        struct list_node *next;
};

list_t *list_new(list_ops_t *ops)
{
	list_t *new_list;

	if (!(new_list = malloc(sizeof(list_t))))
		return NULL;
	memset(new_list, 0, sizeof(list_t));
	if (ops)
		new_list->ops = *ops;

	return new_list;
}

int list_add_head(list_t *l, void *data)
{
	list_node_t *new_node;

	if (!(new_node = malloc(sizeof(list_node_t))))
		return -1;
	new_node->data = data;
	new_node->next = l->head;
	l->head = new_node;

	return 0;
}

int list_add_tail(list_t *l, void *data)
{
	list_node_t *new_node, **p;

	if (!(new_node = malloc(sizeof(list_node_t))))
		return -1;
	new_node->data = data;
	new_node->next = NULL;
	for (p = &(l->head); *p; p = &((*p)->next));
	*p = new_node;

	return 0;
}

void list_print(list_t *l)
{
	list_node_t *p;

	for (p = l->head; p; p = p->next) { 
		if (l->ops.print)
			l->ops.print(p->data);
		else
			printf("%d \n", (int)(long)(p->data));
	}
}

void list_exec(list_t *l, void (*cb)(void *d, void *param), void *param)
{
	list_node_t *p;

	for (p = l->head; p; p = p->next) { 
		if (cb)
			cb(p->data, param);
	}
}

void *list_pop(list_t *l, int id)
{
	list_node_t **p;
	void *retval, *del;
	int i;

	if (id == -1) {
		id = 0;
		for (p = &(l->head); *p; p = &((*p)->next))
			id++;
		id--;
	}

	for (p = &(l->head), i = 0; *p && i < id; p = &((*p)->next), i++);
	if (i < id)
		return NULL;

	if (!*p)
		return NULL;
	retval = (*p)->data;
	del = *p;
	*p = (*p)->next;
	free(del);

	return retval;
}

void *list_get(list_t *l, void *d)
{
	list_node_t *p;

	if (!(l->ops.cmp))
		return NULL;

	for (p = l->head; p; p = p->next) {
		if (l->ops.cmp(d, p->data) == 0)
			return p->data;
	}

	return NULL;
}

void list_reset(list_t *l)
{
	list_node_t *p, *del;

	for (p = l->head; p; ) {
		if (l->ops.destroy)
			l->ops.destroy(p->data);
		del = p;
		p = p->next;
		free(del);
	}
	l->head = NULL;
}

void list_destroy(list_t **l)
{
	list_reset(*l);
	free(*l);
	*l = NULL;
}

