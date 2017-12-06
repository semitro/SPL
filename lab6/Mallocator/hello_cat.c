#include "mallo_cat.h"

struct mem *first;

void heap_init(size_t initial_size){
	first = mmap(NULL, initial_size + sizeof(struct mem),
				 PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
	printf("heap init: %p\n", first);
	first->capacity = initial_size;
	first->is_free = true;
	first->next = NULL;
}

void* meow_lloc(size_t size){
	struct mem* i = first;
	struct mem* reminder = NULL;
	size_t real_size = size + sizeof(struct mem);
	while(i){
		if(i->is_free && i->capacity >= real_size){
			reminder = i + real_size;
			reminder->capacity = i->capacity - real_size;

			reminder->is_free = true;
			i->is_free = false;

			reminder->next = i->next;
			i->next = reminder;

			return i;
		}

		i = i->next;
	}

	return NULL;
}
