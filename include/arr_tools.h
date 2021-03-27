#ifndef __ARRTOOLS__
#define  __ARRTOOLS__

typedef struct arr_item {
	int n;
	int *data;
} arr_item_t;

arr_item_t **handle_list_of_arrays(char *str);
void cleanup_list_of_arrays(arr_item_t ***lines);

#endif
