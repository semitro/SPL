// Created by semitro on 05.10.17.
#ifndef LAB4_LIST_H
#define LAB4_LIST_H

#include <stddef.h>

typedef int list_content;
typedef struct list_node{
    list_content value;
    struct list_node* next;
}list_node;


list_node*    list_create    (list_content value);
list_node*    list_node_at   (const size_t index);
list_content  list_get       (const size_t index);
size_t        list_length    (list_node*   list);
// Add the element. Change the pointer to the new beginning
void          list_add_front (list_content value,  list_node* list);
void          list_add_back  (list_content value,  list_node* list);

void          list_free      (list_node*   list);

long long     list_sum       (list_node*   list);
#endif //LAB4_LIST_H_H
