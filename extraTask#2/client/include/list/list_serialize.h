//
// Created by semitro on 07.10.17.
//

#ifndef LAB4_LIST_SERIALIZE_H
#define LAB4_LIST_SERIALIZE_H

#include "list.h"
#include "list_functions.h"

#include <stdbool.h>
#include <stdio.h>

#define MAX_INPUT_BUFFER_SIZE 1024

bool list_save        (list_node*  lst, const char* const filename);
bool list_save_binary (list_node*  lst, const char* const filename);

bool list_load        (list_node** lst, const char* const filename);
bool list_load_binary (list_node** lst, const char* const filename);

list_node* read_list_from_stream(FILE* stream, const size_t max_buffer);
list_node* read_list_from_std(size_t max_buffer);

bool list_save_abstract(
        list_node* lst, const char* const filename,
        const char* const file_mode,
        void(print_function)(list_content));

#endif //LAB4_LIST_SERIALIZE_H
