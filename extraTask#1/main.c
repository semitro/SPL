#include "StrangeRunner.h"
#include "FileInteraction.h"

int main(int argc, char **argv){
    if(argc != 3){
        puts("Usage: elf_file.o text_file.txt");
        return 0;
    }

    void* elf = load_object_file(argv[1]);
    if(!elf){
        if(get_error() == _NOT_ELF_FILE_ERR)
            puts("The file is not an elf object!");
        else
            puts("Something wrong with file loading.");
        return 0;
    }

    int(*function)(char*) = get_function(elf);
    apply_for_each_stroke_show_int(function,argv[2]);
    return 0;
}
