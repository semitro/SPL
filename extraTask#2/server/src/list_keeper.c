#include "list_keeper.h"

list_node* get_list(){
	return list;
}

void init_list(size_t size){
	if(!list)
		list = list_create(size--);
	size--;
	for(;size>0;size--)
		list_add_front(21,&list);
	list_add_back(14,&list);
}

void do_this_with_list(void* commands, size_t index_from, size_t index_to){
	void(*f)(list_conent) = commands;
	list_map_mut(get_list(),&f);
}
