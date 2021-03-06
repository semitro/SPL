#include "list/list.h"

list_node* list_create (const list_content value){
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
    list_node* node = list_node_at(index,list);
    if(node)
        return node->value;
    else
        return 0;
}

size_t list_length(const list_node* const list) {
    size_t ans = 0;
    list_node* current_node = (list_node*)list;
    while(current_node){
        ans++;
        current_node = current_node->next;
    }
    return ans;
}

void list_add_front(const list_content value, list_node** list){
    list_node* new_node = list_create(value);
    if(new_node){
        new_node->next = (list_node*)*(list);
        *list = new_node;
    }
}

void list_add_back(const list_content value, list_node** const const list){

    list_node* current_node = (list_node*)*(list);

    while(current_node->next)
        current_node = current_node->next;

    list_node* new_node = list_create(value);
    if(new_node)
       current_node->next = new_node;

}

void list_free( list_node**   list){

    list_node* to_free = (list_node*)*list;
    list_node* next;

    while(to_free){
        next = to_free->next;
        free(to_free);
        to_free = next;
    }
    (*list) = NULL;
}

long long list_sum(const list_node* const list){
    long long sum = 0;
    list_node* current_node = (list_node*)list;
    while(current_node){
        sum += current_node->value;
        current_node = current_node->next;
    }
    return sum; //list && list->next ? list->value + list_sum(list->next) : list->value;// by Yakov G. 2017
}

