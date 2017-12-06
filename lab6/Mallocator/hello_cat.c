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
			printf("\t\t\t%p\n", i);

			printf("\t\t\t%d\n", i->capacity);

			reminder->capacity = i->capacity - real_size;


			printf("\t\t\t%d\n", reminder->capacity);
			i->capacity = size;


			reminder->is_free = true;
			i->is_free = false;

			reminder->next = i->next;
			i->next = reminder;

			return (void*)i + sizeof(struct mem);
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
	puts("................................................................");
	puts(".\tThere's no free chunks, trying to make MAP_FIXED mmap");
	#endif
	size_t allocated_mem = get_real_size_aligned_by_page(size);
	printf(".\t alloc: %lu\n", allocated_mem);
	struct mem* new_chunk =
			mmap((void*)i + i->capacity + sizeof(struct mem), allocated_mem,
				 PROT_EXEC | PROT_READ | PROT_WRITE,
				 MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS , -1, 0);

	if(-1 != (long int)new_chunk){

		i->next = new_chunk;
		new_chunk->next     = NULL;
		new_chunk->is_free  = true;
		new_chunk->capacity = allocated_mem - sizeof(struct mem);
		printf(".new chunk \t%d\n", new_chunk->capacity);

		printf(".new chunk \t%d\n", new_chunk->capacity);
		printf(".new chunk \t%d\n", new_chunk->capacity);
		new_chunk ->capacity = new_chunk->capacity;
		printf(".new chunk \t%d\n", new_chunk->capacity);
		printf(".new chunk \t%d\n", new_chunk->capacity);


		#ifdef DEBUG
		puts(".\tMAP_FIXED allocate succeed");
		printf(".\tIt's addr: %p\n", new_chunk);
		printf(".\tIt's capacity: %d\n", new_chunk->capacity);

		puts("................................................................");
		#endif
		printf("new chunk \t%d\n", new_chunk->capacity);

		return (void*)new_chunk +sizeof(struct mem);
	}
	// if it is impossible, mmap anywhere
	return NULL;
}
