//
// Created by semitro on 07.10.17.
//

#ifndef LAB4_TESTS_H
#define LAB4_TESTS_H

#include <stdio.h>
#include <stddef.h>

#include "list.h"
#include "list_functions.h"

void function_print(list_content v);

void print_list(list_node* list);

list_content mul5(list_content v);

list_content fold_function(list_content a,list_content b);

list_content mul2(list_content v);

list_node* read_list_from_std(size_t max_buffer);

void test_1(list_node* list);
#endif //LAB4_TESTS_H
