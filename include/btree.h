#ifndef __BTREE_H__
#define  __BTREE_H__

#include <stdbool.h>

typedef enum BTREE_RET_CODE {
	BTREE_ERROR = -1,
	BTREE_NOT_FOUND = -1,
	BTREE_OK = 0,
} btree_ret_code_e;

struct btree {
        int value;
        struct btree *parent;
        struct btree *left;
        struct btree *right;
};

typedef struct btree btree_t;
int btree_insert(btree_t **bt, int value);
bool btree_contains(btree_t *bt, int value);
btree_t *btree_get_node(btree_t *bt, int value);
void btree_print(btree_t *bt);
btree_ret_code_e btree_remove(btree_t **bt, int value);
btree_t *get_node(btree_t *bt, int value);
btree_t *get_successor(btree_t *bt);
void btree_inorder_print(btree_t *bt);

#endif
