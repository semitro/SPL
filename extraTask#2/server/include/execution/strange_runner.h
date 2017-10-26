#ifndef _STRANGERUNNER_H
#define _STRANGERUNNER_H

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> // The open sys call is here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#define _NOT_ELF_FILE_ERR  1
#define _LOAD_ERR          2
#define _NO_SYMBOL_SECTION 3
/*
 * return last error
 * the errors defined above
 */
char get_error();
/*
 * This function loads the object file into memory and returns
 * a pointer to Elf_header in memory
 * (returns void* because we don't want to user works with elf-terminology).
 * Return NULL if an error happened.
 * You need to use get_error and handle it in this case
 *
 */
void* load_object_file(char* file_name);
void* get_function(void* elf_in_memory);

#endif //EXTRATASK_1_STRANGERUNNER_H
