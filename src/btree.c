#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h" 

int __btree_insert(btree_t **bt, int value, btree_t *parent)
{
	if (!*bt) {
		if (!(*bt = malloc(sizeof(btree_t))))
		       return -1;
		(*bt)->parent = parent;
		(*bt)->value = value;
		(*bt)->left = (*bt)->right = NULL;	
		return 0;
	}
	if (value >= (*bt)->value)
		return __btree_insert(&((*bt)->right), value, *bt);
	return __btree_insert(&((*bt)->left), value, *bt);
}

int btree_insert(btree_t **bt, int value)
{
	return __btree_insert(bt, value, NULL);
}

bool btree_contains(btree_t *bt, int value)
{
	if (!bt)
		return false;
	if (bt->value == value)
		return true;
	if (value > bt->value)
		return btree_contains(bt->right, value);
	return btree_contains(bt->left, value);
}

/*
void __btree_print(btree_t *bt, int level)
{
	int i;

	if (!bt)
		return;
	__btree_print(bt->right, level + 1);
	for (i = 0; i < level; i++)
		printf(" ");
	printf("%d:%d\n", bt->parent ? bt->parent->value : -1, bt->value);
	__btree_print(bt->left, level + 1);
}
*/

void __btree_print(btree_t *bt, int level)
{
	int i;

	if (!bt)
		return;
	printf("%d:%d\n", bt->parent ? bt->parent->value : -1, bt->value);
	__btree_print(bt->right, level + 1);
	__btree_print(bt->left, level + 1);
}

btree_t *btree_get_node(btree_t *bt, int value)
{
	if (!bt)
		return NULL;
	if (value == bt->value)
		return bt;
	if (value > bt->value)
		return btree_get_node(bt->right, value);
	return btree_get_node(bt->left, value);
	
}

btree_ret_code_e btree_get_biggest(btree_t *bt)
{
	btree_t *node;
	int retVal = bt->value;

	for (node = bt->right; node; node = node->right) 
		retVal = node->value;
	
	return retVal;
}

btree_ret_code_e btree_get_smallest(btree_t *bt)
{
	btree_t *node;
	int retVal = bt->value;

	for (node = bt->left; node; node = node->left) 
		retVal = node->value;
	
	return retVal;
}

int btree_remove(btree_t **bt, int value)
{
	if (!(*bt))
		return BTREE_NOT_FOUND;
	if (value > (*bt)->value)
		return btree_remove(&((*bt)->right), value);
	if (value < (*bt)->value)
		return btree_remove(&((*bt)->left), value);

	if (!(*bt)->left && !(*bt)->right) {
		if (!(*bt)->parent) {
			free(*bt);
			*bt = NULL;
			return BTREE_OK;
		}
		if ((*bt)->parent->left == *bt)
			(*bt)->parent->left = NULL;
		else
			(*bt)->parent->right = NULL;
		free(*bt);
		return BTREE_OK;
	}
	if ((*bt)->left) {
		int biggest = btree_get_biggest((*bt)->left);
		btree_remove(&((*bt)->left), biggest);
		(*bt)->value = biggest;
	} else {
		int smallest = btree_get_smallest((*bt)->right);
		btree_remove(&((*bt)->right), smallest);
		(*bt)->value = smallest;
	}
	return BTREE_OK;
}

void btree_print(btree_t *bt)
{
	return __btree_print(bt, 0);
}

void btree_inorder_print(btree_t *bt) {
	if (!bt)
		return;
	btree_inorder_print(bt->left);
	printf("%d\n", bt->value);
	btree_inorder_print(bt->right);
}


btree_t *get_node(btree_t *bt, int value)
{
	if (!bt)
		return NULL;
	if (bt->value == value)
		return bt;
	if (value > bt->value)
		return get_node(bt->right, value); 
	return get_node(bt->left, value); 
}

btree_t *get_successor(btree_t *bt)
{
	btree_t *p;

	if (!bt)
		return NULL;
	if (bt->right) { 
		btree_t *suc = bt->right, *l;
		for (l = suc->left; l; l = l->left)
			suc = l;
		return suc;
	}
	for (p = bt->parent; p && p->left != bt; p = p->parent)
		bt = p;
	return p;
}

