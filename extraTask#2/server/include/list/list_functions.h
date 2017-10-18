//
// Created by semitro on 06.10.17.
//
#ifndef LAB4_LIST_FUNCTIONS_H
#define LAB4_LIST_FUNCTIONS_H

#include "list.h"
#include "stdio.h"

void list_for_each(const list_node* const list, void(*function)(list_content));
// It returns a new list containing the results of the f,
// applied to all elements of the source list.
// The source list is not affected.
list_node* list_map(const list_node* const list, list_content(*function)(list_content));
// As the list_map, but it changes the source list. Return the same pointer witch accepts
list_node* list_map_mut(list_node* const list, list_content(*function)(list_content));

// Ordered apply for each element of the list this way: accumulator = f(accumulator, list_node_i->value)
list_content list_foldl (const list_node* const list,
                         const list_content accumulator,
                         list_content(*function)(list_content,list_content));

// iterate accepts the initial value s, list length n, and function f. It then generates a list
// of length n as follows: s, f(s), f(f(s))
list_node* list_iterate( const list_content s,
                         list_content(*function)(list_content), size_t length);

void print_list(list_node const * const l);
#endif //LAB4_LIST_FUNCTIONS_H
