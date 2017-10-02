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

    
    // Elf-header
    Elf64_Ehdr* elf_header = load_into_memory(argv[1]);
    if( !(elf_header->e_type == ET_REL || elf_header->e_type == ET_EXEC) ){
        puts("A file you want to run is not the elf-format\n(or the elf but not an relocatable or executable)");
        return 0;
    }
    printf("The magic number: 0x%x %c %c %c\n", elf_header->e_ident[0],
           elf_header->e_ident[1], elf_header->e_ident[2], elf_header->e_ident[3]);
    
    // Elf-section Header is located in the RAM witch the offset
    Elf64_Shdr* elf_section_header = elf_header + elf_header->e_shoff;
    
    
    Elf64_Sym* elf_sym;
    elf_sym->st-name;
    elf_sym->st_info == STT_FUNC;

    return 0;
}
