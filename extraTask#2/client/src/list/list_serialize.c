//
// Created by semitro on 07.10.17.
//
#include "list/list_serialize.h"
// not pure. May be problems with concurrency


bool err = false;
FILE* file = NULL;
static void print_to_file(list_content v){
    if(fprintf(file,"%d ",v) <= 0)
        err = true;
}
static void print_binary(const list_content v){
    if( fwrite(&v, sizeof v, 1,file) <= 0)
        err = true;
}
bool list_save_abstract(
                        list_node* lst, const char* const filename,
                                        const char* const file_mode,
                        void(print_function)(list_content)){
    err = false;
    file = fopen(filename,file_mode);

    if(!file)
        return false;

    list_for_each(lst,print_function);

    fclose(file);
    return !err;
}

bool list_save(list_node* lst, const char* const filename){
    return list_save_abstract(lst,filename,"w",print_to_file);
}
bool list_save_binary(list_node* lst, const char* const filename){
    return list_save_abstract(lst,filename,"wb",print_binary);
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
    return lst;
}

bool list_load_binary (list_node** lst, const char* const filename){
    FILE* file = fopen(filename,"rb");
    if(!file)
        return false;

    list_content n = NULL;
    list_free(lst);
    while(fread(&n, sizeof n,1,file))
        if(*lst)
            list_add_back(n,lst);
        else
            *lst = list_create(n);

    fclose(file);
    // If fread has not been worked as least once, list = NULL and it's an error
    // Otherwise, everything's ok, so we can just return list
    return *lst;
}

