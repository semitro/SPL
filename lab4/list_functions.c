//
// Created by semitro on 06.10.17.
//
#include "list_functions.h"

void list_for_each(const list_node* const list, void(*function)(list_content)){
    list_node* current_node = (list_node*)list;
    while(current_node){
        function(current_node->value);
        current_node = current_node->next;
    }
}

list_node* list_map(const list_node* const list,list_content(*function)(list_content)){

    if(!list || !function)
        return NULL;

    list_node* const first_node = list_create(function(list->value));

    const list_node* current_node = (list_node*)list;
    while(current_node->next){
        list_add_back( function(current_node->next->value), (list_node**)&first_node);
        current_node = current_node->next;
    }

    return first_node;
}
