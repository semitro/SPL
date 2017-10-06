//
// Created by semitro on 06.10.17.
//
#ifndef LAB4_LIST_FUNCTIONS_H
#define LAB4_LIST_FUNCTIONS_H

#include "list.h"

void list_for_each(const list_node* const list, void(*function)(list_content));
// It returns a new list containing the results of the f,
// applied to all elements of the source list.
// The source list is not affected.
list_node* list_map(const list_node* const list, list_content(*function)(list_content));
#endif //LAB4_LIST_FUNCTIONS_H
