//
// Created by semitro on 07.10.17.
//

#ifndef LAB4_TESTS_H
#define LAB4_TESTS_H

#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include "list.h"
#include "list_functions.h"
#include "list_serialize.h"
void function_print(list_content v);

void print_list(list_node* list);

list_content mul5(list_content v);

list_content fold_function(list_content a,list_content b);

list_content mul2(list_content v);

list_node* read_list_from_std(size_t max_buffer);

void test_1(list_node* list);
void test_2(list_node* list);
void test_3_serialize(list_node* list,const char* const file_name);
#endif //LAB4_TESTS_H
