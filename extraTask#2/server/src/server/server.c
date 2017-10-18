#include "server/server.h"
#include "server/listener.h"
#include "server/client_handler.h"
#include "list/list.h"
#include "list/list_functions.h"
static list_node* list;

list_node* get_list(){
	return list;
}

static void init_list(size_t size){
	if(!list)
		list = list_create(size--);
	size--;
	for(;size>0;size--)
		list_add_front(21,&list);
	list_add_back(14,&list);
}

void start_server(unsigned int port){
	init_list(15);
	print_list(list);
	set_client_handler(handle_client);
	start_listen(port);
}
