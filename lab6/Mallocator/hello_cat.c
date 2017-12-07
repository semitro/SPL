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
	printf("heap init addr: %p\n", (void*)first);
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
			reminder = (uint8_t*)i + real_size;
//			printf("\t\t\t%p\n", (void*)i);

//			printf("\t\t\t%lu\n", i->capacity);

			reminder->capacity = i->capacity - real_size;

//			printf("\t\t\t%lu\n", reminder->capacity);
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
	puts(".\tThere's no free chunks, trying to make mmap");
	#endif
	size_t allocated_mem = get_real_size_aligned_by_page(size);
	struct mem* new_chunk =
			(struct mem*)mmap((void*)i + i->capacity + sizeof(struct mem), allocated_mem,
				 PROT_EXEC | PROT_READ | PROT_WRITE,
				  MAP_PRIVATE | MAP_ANONYMOUS , -1, 0);

	if(MAP_FAILED != (void*)new_chunk){
		i->next = new_chunk;
		new_chunk->next     = NULL;
		new_chunk->is_free  = false;

		new_chunk->capacity = allocated_mem - sizeof(struct mem);

		#ifdef DEBUG
		puts(".\tmmap allocate succeed");
		printf(".\tIt's addr: %p\n", new_chunk);
		printf(".\tIt's capacity: %d\n", new_chunk->capacity);

		puts("................................................................");
		#endif

		return (void*)new_chunk +sizeof(struct mem);
	}
	// if it is impossible, mmap anywhere
	return NULL;
}

void merge_with_next_if_free(struct mem* m){
	if(!m || !m->is_free || !m->next || !m->next->is_free
			|| (uint8_t*)m + m->capacity + sizeof(struct mem) != m->next) // следует ли одик блок за другим в памяти
		return;
#ifdef DEBUG
	printf("****\nСливаю блоки с адресами %p и %p\n****\n", (void*)m, (void*)m->next);
#endif
	m->capacity += m->next->capacity + sizeof(struct mem);
	m->next = m->next->next;
}

void frrre(void *mem){
	struct mem* i = first;
	while(i){
		// Если память есть в нашем индексе
		if((uint8_t*)i + sizeof(struct mem) == mem){
			i->is_free = true;
			if(i->next != NULL)
				merge_with_next_if_free(i);
			return;
		}
		   i = i->next;
	}
}





void memalloc_debug_struct_info(struct mem const* const address ) {

	size_t i;
	printf(	"start: %p\nsize: %lu\nis_free: %d\n",
			(void*)address,
			address-> capacity,
			address-> is_free );
	for ( i = 0;
			i <  DEBUG_FIRST_BYTES  &&  i <  address-> capacity;
			++i )
		printf( "%hhX\n",
				((char*)address)[ sizeof( struct mem ) + i ] );
}
void memalloc_debug_heap( struct mem const* ptr ) {
	for( ; ptr; ptr = ptr->next )
		memalloc_debug_struct_info( ptr );
}

