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

void function_to_invoke_prototype();
// Находим все функции из таблицы символов, нам нужно
void handle_sym_tab(Elf64_Sym* sym_ptr, const size_t count, const char* elf_file_start_addr){
    for(int i=0; i<count; i++){
        if(ELF64_ST_TYPE(sym_ptr->st_info) == STT_FUNC){
            puts("Ура!!! Мы нашли функцию!\n");
            printf("The value: %d\n", sym_ptr->st_shndx);
            
            // void(*function)() = elf_file_start_addr + ((Elf64_Shdr*)sym_ptr->st_shndx)->sh_offset;
        
            //function();
        }
        sym_ptr++;
    }
}

// Перебирает все секции и вызывает обработчик для символьных
void handle_sections(const Elf64_Ehdr* elf_header){
    // Elf-section Header is located in the RAM witch the offset
    // shoff - section offset from file
    // Почему char*? потому что стандарт гарантирует, char = 8 бит
    // Явное преобразование добавлено, чтобы избежать предупреждения компилятора. Это правильно?
    Elf64_Shdr* elf_section = (Elf64_Shdr*)((char*)elf_header + elf_header->e_shoff);
    size_t sections_num = elf_header->e_shnum;
    for(unsigned int i = 0; i < sections_num;i++){
        if(elf_section->sh_type == SHT_SYMTAB )
            handle_sym_tab(
                            (Elf64_Sym*) (elf_section->sh_offset + (char*)elf_header), 
                            elf_section->sh_size / elf_section->sh_entsize,
                            (char*)elf_header
                          );
        elf_section++;        
    }
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
    
    handle_sections(elf_header);
    
    return 0;
}
