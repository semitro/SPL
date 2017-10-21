#ifndef LIST_KEEPER
#define LIST_KEEPER

#include "list/list.h"

list_node* list;

list_node* get_list();

void init_list(size_t size);

void do_this_with_list(void* commands, size_t index_from, size_t index_to);

#endif // LIST_KEEPER

