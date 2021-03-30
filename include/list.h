#ifndef __LIST_H__
#define __LIST_H__

typedef struct list_node list_node_t;

typedef struct {
	int (*cmp)(void *d1, void * d2);
	void (*destroy)(void *d);
	void (*print)(void *d);
} list_ops_t;

typedef struct {
	list_node_t *head;
	list_ops_t ops;
} list_t;

list_t *list_new(list_ops_t *ops);
int list_add_head(list_t *l, void *data);
int list_add_tail(list_t *l, void *data);
void list_print(list_t *l);
void list_exec(list_t *l, void (*cb)(void *d, void *param), void *param);
void *list_pop(list_t *l, int id);
void *list_get(list_t *l, void *d);
void list_reset(list_t *l);
void list_destroy(list_t **l);

#endif
