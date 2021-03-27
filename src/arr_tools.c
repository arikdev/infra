#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arr_tools.h"
#include "stack.h"

static void clean_blanks(char *str)
{
	int i, io = 0;

	for (i = 0; str[i]; i++) {
		if (str[i] == ' ')
			continue;
		str[io++] = str[i];
	}	
	str[io] = 0;
}

static arr_item_t *handle_array(char *str)
{
	char *tmp, *p;
	int count = 0, i, len = strlen(str);
	arr_item_t *new_item;

	if (!(new_item = malloc(sizeof(arr_item_t))))
		return NULL;

	clean_blanks(str);
	tmp = strdup(str);

	for (i = 0; i < len; i++) {
		if (str[i] == ',')
			count++;
	}
	if (strlen(str))
		count++;

	new_item->n = count;
	if (count) {
		new_item->data = malloc(sizeof(int) * count);
		i = 0;
		for (p = strtok(tmp, ","); p; p = strtok(NULL, ","))
			new_item->data[i++] = atoi(p);
	} else
		new_item->data = NULL;

	free(tmp);

	return new_item;
}

// Provides a list of arrays of ints
static int parse_list_of_arrays(char *str, arr_item_t **list)
{
	int i, count = 0, len = strlen(str), size, j, n = 0;
	char *p, *tmp, *help;
	arr_item_t *item;
	stack_t *items_s = NULL;
	char work[1024];

	for (i = 0; i < len; i++) {
		if (str[i] == '[') {
			if (stack_push(&items_s, (void *)(str + i  + 1)))
				return -1;
			continue;
		}
		if (str[i] != ']')
			continue;
		if (stack_pop(&items_s, (void *)&help))
			return -1;
		size = str + i - help;
		memcpy(work, help, size);
		work[size] = 0;
		if (strchr(work, '['))
			continue;
		if (!(item = handle_array(work))) {
			printf("ERROR: handle_array failed\n");
			return -1;
		}
		if (list) {
#ifdef DEBUG
			printf("-------------> item#%d  n:%d \n", n, item->n);
			for (j = 0 ; j < item->n; j++)
				printf("%d ", item->data[j]);
			if (item->n)
				printf("\n");
#endif
			list[n] = item;
		} else
			free(item);
		n++;
	}

	return n;
}

arr_item_t **handle_list_of_arrays(char *str)
{
	arr_item_t **lines; 
	int n, i, j;

       	n = parse_list_of_arrays(str, NULL);
	if (!(lines = malloc((n + 1) * sizeof(arr_item_t))))
		return NULL;
	memset(lines, 0, (n + 1) * sizeof(arr_item_t));
       	parse_list_of_arrays(str, lines);


	return lines;
}

void cleanup_list_of_arrays(arr_item_t ***lines)
{
	int i;

	for (i = 0; ; i++) {
		if (!(*lines)[i])
			break;
		free((*lines)[i]);
	}
	free(*lines);
	*lines = NULL;
}

