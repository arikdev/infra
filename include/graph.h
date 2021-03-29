#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct graph_node graph_node_t;


graph_node_t *graph_new(char *name);
int graph_add_child(graph_node_t *node, graph_node_t *child);
void graph_print(graph_node_t *node);


#endif
