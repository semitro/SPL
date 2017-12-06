#include <stdio.h>
#include <unistd.h>
#include "mallo_cat.h"

int main(void)
{
	printf("sizeof(one block): %lu\n", sizeof(struct mem));
	printf("Page size: %luв\n", sysconf(_SC_PAGESIZE));
	heap_init(40960 - 17);
	puts("meow_llocs:");
	printf("#1\t%p\n", meow_lloc(3));
	printf("#2\t%p\n", meow_lloc(63));
	printf("#3\t%p\n", meow_lloc(10));
	printf("#4\t%p\n", meow_lloc(500));
	printf("#5\t%p\n", meow_lloc(5000));

	printf("#6\t%p\n", meow_lloc(50000));
	printf("#7\t%p\n", meow_lloc(50000));


	return 0;
}

