#include <stdio.h>
#include <unistd.h>
#include "mallo_cat.h"

int main(void)
{
	printf("sizeof(one block): %lu\n", sizeof(struct mem));
	printf("Page size: %lu\n", sysconf(_SC_PAGESIZE));
	heap_init(1000);
	puts("meow_llocs:");
	printf("#1\t%p\n", meow_lloc(3));
	printf("#2\t%p\n", meow_lloc(63));
	printf("#3\t%p\n", meow_lloc(64));
	printf("#4\t%p\n", meow_lloc(500));

	void* p;
	printf("#5\t%p\n", p = meow_lloc(7));

	float *f1 = meow_lloc(sizeof(float));
	float *f2 = meow_lloc(42);

	*f1 = 15;
	*f2 = 155;
	frrre(f2);
	frrre(f1);
	//memalloc_debug_heap((uint8_t*)f1-sizeof(struct mem));

	//frrre(f1);
	void* big;
	printf("#6.1\t%p\n", big = meow_lloc(320256));
	frrre(big);
	frrre(p);
	printf("#6.2\t%p\n", meow_lloc(500));
	printf("#6.3\t%p\n", meow_lloc(4));
	printf("#6.4\t%p\n", meow_lloc(4));
	printf("#7\t%p\n", meow_lloc(600000000));
	printf("#7.1\t%p\n", meow_lloc(32));
	printf("#7.2\t%p\n", meow_lloc(119));

	puts("We're alive");


	return 0;
}

