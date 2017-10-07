//
// Created by semitro on 07.10.17.
//
#include "list_serialize.h"
// not pure
bool err = false;
FILE* file = NULL;
static void print_to_file(list_content v){
    if(fprintf(file,"%d ",v) <= 0)
        err = true;
}
bool list_save(list_node* lst, const char* const filename){
    err = false;
    file = fopen(filename,"w");

    if(!file)
        return false;

    list_for_each(lst,print_to_file);

    fclose(file);
    return !err;
}

list_node* read_list_from_stream(FILE* stream,const size_t max_buffer){
    char input_buffer[max_buffer];
    fgets(input_buffer, max_buffer,stream);

    int n;
    list_node* input_list = NULL;
    int i,j;
    for(i=j=0; sscanf(input_buffer+i,"%d%n",&n,&j) == 1; i+=j)
        if(input_list)
            list_add_front(n,&input_list);
        else
            input_list = list_create(n);
    return input_list;
}

list_node* read_list_from_std(size_t max_buffer){
    return read_list_from_stream(stdin,max_buffer);
}


bool list_load(list_node** lst, const char* const filename){
    file = fopen(filename,"r");
    if(!file)
        return false;

    *lst = read_list_from_stream(file,MAX_INPUT_BUFFER_SIZE);

    fclose(file);
    return true;
}

