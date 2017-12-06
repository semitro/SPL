#include "mallo_cat.h"

struct mem *first;

size_t get_real_size_aligned_by_page(size_t size){
	size_t allocated = size + sizeof(struct mem);
	allocated += (sysconf(_SC_PAGESIZE) - allocated % sysconf(_SC_PAGESIZE)) % sysconf(_SC_PAGESIZE);
	return allocated;
}

void heap_init(size_t initial_size){

	// it's better to allocate page-aligned memory because in this case
	// mew_lloc can add some space right after the last
	// it's better to allocate page-aligned memory because in this case
	// mew_lloc can add some space right after the last
	size_t allocated = get_real_size_aligned_by_page(initial_size);

	first = mmap(NULL, allocated,
				 PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
#ifdef DEBUG
	printf("heap init addr: %p\n", first);
	printf("heap init size: %lu\n", allocated);
#endif
	first->capacity = allocated - sizeof(struct mem);
	first->is_free = true;
	first->next = NULL;

}

void* meow_lloc(size_t size){
	struct mem* i = first;
	struct mem* reminder = NULL;
	size_t real_size = size + sizeof(struct mem);
	while(true){
		if(i->is_free && i->capacity >= real_size){
			// split it
			reminder = (void*)i + real_size;
			reminder->capacity = i->capacity - real_size;

			i->capacity = size;

			reminder->is_free = true;
			i->is_free = false;

			reminder->next = i->next;
			i->next = reminder;

			return i + sizeof(struct mem);
		}

		if(i->next)
			i = i->next;
		else
			break;
	}

	// if all the chains are busy,
	// we need to try to mmap a new region
	// first, right after the last element
	#ifdef DEBUG
	puts("There's no free chunks, trying to make MAP_FIXED mmap");
	#endif
	size_t allocated_mem = get_real_size_aligned_by_page(size);
	printf("%d alloc: ", allocated_mem);
	struct mem* new_chunk = mmap(i + i->capacity + sizeof(struct mem), allocated_mem,
								 PROT_EXEC | PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);

	if(-1 != new_chunk){
		#ifdef DEBUG
		puts("MAP_FIXED allocate succeed");
		printf("It's addr: %p\n", new_chunk);
		#endif
		i->next = new_chunk;
		new_chunk->next     = NULL;
		new_chunk->is_free  = true;
		new_chunk->capacity = allocated_mem;
		return new_chunk;
	}
	// if it is impossible, mmap anywhere
	return NULL;
}
