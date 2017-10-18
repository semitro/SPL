#include "list/list_functions.h"

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

list_node* list_map_mut(list_node* const list, list_content(*function)(list_content)){
    list_node* current_node = (list_node*)list;
    while(current_node){
        current_node->value = function(current_node->value);
        current_node = current_node->next;
    }
    return list;
}

list_content list_foldl (const list_node* const list,
                    const list_content accumulator,
                    list_content(*function)(list_content,list_content)){
    // Лучше ли использовать отдельную переменную аккумулятора или использовать то, что уже есть на стеке?
    // Функция принимает параметр, и поэтому не может изменить передаваемое значение. Так что явно приводим
    // Just for fun
    return list ?
                    list->next ? list_foldl(list->next, function((list_content)accumulator, list->value),function )
                               :                        function((list_content)accumulator, list->value)
           : 0;
}

list_node* list_iterate(const list_content s,
                        list_content(*function)(list_content), size_t length){

    if(!function || !length)
        return NULL;

    list_content current_result = s;

    list_node* new_list = list_create(current_result);

    while (--length){
        current_result = function(current_result);
        list_add_back(current_result,&new_list);
    }

    return new_list;
}
void print_conent(list_content v){
	printf("%d->",v);
}

void print_list(list_node const * const l){
	list_for_each(l,print_conent);
	puts("");
}
