#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "graph.h"

#define NAME_SIZE 16

struct graph_node {
	char name[NAME_SIZE];
	list_t *children;
};

static void graph_node_print(void *d)
{
	graph_node_t *graph_node = (graph_node_t *)d;
	printf("%s ", graph_node->name);
}

static list_ops_t ops;

graph_node_t *graph_new(char *name)
{
	graph_node_t *new_node;

	if (!(new_node = malloc(sizeof(graph_node_t))))
		return NULL;
	strncpy(new_node->name, name, NAME_SIZE - 1);
	ops.print = graph_node_print;
	new_node->children = list_new(&ops);

	return new_node;
}

int graph_add_child(graph_node_t *node, graph_node_t *child)
{
	list_add_tail(node->children, child);
}

void graph_print(graph_node_t *node)
{
	printf("Graph :%s \nchildren:", node->name);
	list_print(node->children);
	printf("\n");
}

