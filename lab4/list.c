#include "list.h"
#include "stdio.h"
list_node* list_create (list_content value){
    list_node* node = malloc(sizeof(*node));
    if(node) {
        node->value = value;
        node->next  = NULL;
    }
    return node;
}

// Index is changing. Is it normal?
list_node* list_node_at(size_t index, const list_node* const list){
    list_node* current_node = (list_node*)list;
    while(index--) {
        if(!current_node)
            return NULL;

        current_node = current_node->next;

    }
    return current_node;
}

list_content list_get (size_t index, const list_node* const list){
    list_node* current_node = (list_node*)list;
    while(index--) {
        if(!current_node)
            return 0; // As the task requires, return 0 if index > number of elements

        current_node = current_node->next;

    }
    return current_node->value;
}

size_t list_length(const list_node* const list) {
    size_t ans = 1;
    list_node* current_node = (list_node*)list;
    while(current_node->next){
        ans++;
        current_node = current_node->next;
    }
    return ans;
}

void list_add_front(const list_content value, const list_node** list){
    list_node* new_node = list_create(value);
    if(new_node){
        new_node->next = (list_node*)*(list);
        *list = new_node;
    }
}

void list_add_back(const list_content value, const list_node** list){

    list_node* current_node = (list_node*)*(list);
    while(current_node->next){
        current_node = current_node->next;
    }

    list_node* new_node = list_create(value);
    if(new_node){
       current_node->next = new_node;
    }
}

