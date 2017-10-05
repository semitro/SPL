// Creatded by semitro on 05.10.17.
#ifndef LAB4_LIST_H
#define LAB4_LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef int list_content;
typedef struct list_node{
    list_content value;
    struct list_node* next;
}list_node;


list_node*    list_create    (const list_content value);
list_node*    list_node_at   (size_t index, const list_node* const list);
list_content  list_get       (size_t index, const list_node* const list);
size_t        list_length    (const list_node* const list);
// Add the element. Change the pointer to the new beginning
void          list_add_front (const list_content value, list_node** list);
void          list_add_back  (const list_content value, list_node** list);

void          list_free      (list_node**   list);

long long     list_sum       (const list_node* const  list);

#endif //LAB4_LIST_H_H
