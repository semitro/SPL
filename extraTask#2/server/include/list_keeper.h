#ifndef LIST_KEEPER
#define LIST_KEEPER

#include "list/list.h"
#include "list/list_functions.h"

#include "execution/strange_runner.h"

#include "task_queue.h"

list_node* list;

list_node* get_list();

void init_list(size_t size);
// Применить к каждому элементу списка функцию
void do_this_with_list(list_content(*)(list_content), size_t index_from, size_t index_to);
// Применить к каждому элементу бинарник типа эльф-64, где-то лежащий в памяти
void apply_elf64_on_list(void* elf64hdr,size_t index_from, size_t index_to);
#endif // LIST_KEEPER

