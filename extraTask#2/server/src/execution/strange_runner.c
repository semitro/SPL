#include "execution/strange_runner.h"

static char last_error;

char get_error(){
    return last_error;
}


// Load the file's content into memory as it
// Returns a pointer to memory location where it loaded
static void* load_into_memory(char* file_name){
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
    void* addr = mmap(0, stat_buffer.st_size, PROT_EXEC | PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return addr;

    err:
        last_error = _LOAD_ERR;
        return NULL;
}

void* load_object_file(char* file_name) {
    Elf64_Ehdr *elf_header = load_into_memory(file_name);
    if (elf_header &&
               !(elf_header->e_type == ET_REL
              || elf_header->e_type == ET_EXEC)) {
        last_error = _NOT_ELF_FILE_ERR;
        return NULL;
    }

    return (void*)elf_header;
}


static Elf64_Shdr* get_section_by_index(const Elf64_Ehdr* elf_header, unsigned int index)
{
    Elf64_Shdr* section_ptr = (Elf64_Shdr*)((char*)elf_header + elf_header->e_shoff);
    while(index--) section_ptr++;
    return section_ptr;
}


// Находим все функции из таблицы символов
static void* handle_sym_tab(Elf64_Sym* sym_ptr, const size_t count, const Elf64_Ehdr* elf_header){

    for(unsigned int i=0; i<count; i++){

        if(ELF64_ST_TYPE(sym_ptr->st_info) == STT_FUNC){
            Elf64_Shdr* section_to_go =  get_section_by_index(elf_header, sym_ptr->st_shndx);
            int(*function)(char* ) = (void*)((char*)elf_header + section_to_go->sh_offset);
            return function;
        }

        sym_ptr++;
    }
    return NULL;
}

// Таблица символов указывает лишь на индекс секции, поэтому возникает необходимость в данной функции

// Перебирает все секции и вызывает обработчик для символьной
static void* handle_sections(const Elf64_Ehdr* elf_header){
    // Elf-section Header is located in the RAM witch the offset
    // shoff - section offset from file
    // Почему char*? потому что стандарт гарантирует, char = 8 бит
    Elf64_Shdr* elf_section = get_section_by_index(elf_header,0);
    size_t sections_num = elf_header->e_shnum;

    for(unsigned int i = 0; i < sections_num;i++){
        if(elf_section->sh_type == SHT_SYMTAB )
            return handle_sym_tab(
                    (Elf64_Sym*) (elf_section->sh_offset + (char*)elf_header),
                    elf_section->sh_size / elf_section->sh_entsize,
                    elf_header
            );
        elf_section++;
    }
    last_error = _NO_SYMBOL_SECTION;
    return NULL;
}


void* get_function(void* elf_in_memory){
    Elf64_Ehdr* elf_header = (Elf64_Ehdr*)elf_in_memory;

	if (elf_header &&
				 !(elf_header->e_type == ET_REL
				|| elf_header->e_type == ET_EXEC)) {
		  last_error = _NOT_ELF_FILE_ERR;
		  return NULL;
	  }

    return handle_sections(elf_header);

}
