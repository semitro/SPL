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

// Не заботится о concurrency. Это дело task_queue
pthread_mutex_t mutx;
void do_this_with_list(list_content(*f)(list_content), size_t index_from, size_t index_to){
	printf("Исполняю %p на границе [%d,%d]\n",f,index_from,index_to);
	list_map_mut_indexes(get_list(), f, index_from, index_to);
}

// Нужно реализовать поток-демон, выполняющий задания
bool apply_elf64_on_list(void* elf64hdr,size_t index_from, size_t index_to){
	list_content(*f)(list_content) = get_function(elf64hdr);
	if(!f){
		if(get_error() == _NOT_ELF_FILE_ERR)
			perror("The file is not an elf object!");
		else
			if(get_error() == _NO_SYMBOL_SECTION)
				perror("There's no symtab in the elf64-data!");
			else
				perror("Something wrong with function loading.");
		return false;
	}
	add_task(f,index_from,index_to);
	return true;
}
