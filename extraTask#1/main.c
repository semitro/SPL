#include "StrangeRunner.h"

int main(int argc, char **argv){
    if(argc != 2){
        puts("Enter the object-file to input.");
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
    int answer = function("privet epta");
    printf("The function said: %d\n", answer);
    return 0;
}
