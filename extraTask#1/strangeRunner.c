#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> // The open sys call is here
#include <stdio.h>

// Load the file's content into memory as it
// Returns a pointer to memory location where it loaded
void* load_into_memory(char* file_name){
    int fd = open(file_name, O_RDONLY);

    if(fd < 0)
        goto err;
  
    struct stat stat_buffer;
    if(fstat(fd,&stat_buffer) == -1)
        goto err;
     /*
    extern void *mmap (void *__addr, size_t __len, int __prot,
		   int __flags, int __fd, __off_t __offset) __THROW;
    */
    return mmap(0, stat_buffer.st_size,PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);

    err:
        perror("fsafa");
        return NULL;
}


int main(int argc, char **argv){
    if(argc != 2){
        puts("Enter the object-file to input.");
        return 0;        
    }

    
    
    Elf64_Ehdr* elf_header = load_into_memory(argv[1]);
    printf("The magic number: %d ", elf_header->e_ident[0]);
    (void)argv;

    return 0;
}
