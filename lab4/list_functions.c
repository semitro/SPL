//
// Created by semitro on 06.10.17.
//
#include "list_functions.h"

void list_for_each(list_node* const list, void(*function)(list_content)){
    list_node* current_node = (list_node*)list;
    while(current_node){
        function(current_node->value);
        current_node = current_node->next;
    }
}
