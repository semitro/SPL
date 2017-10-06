#include <stdio.h>
#include "list.h"
#include "list_functions.h"
void function_print(list_content v){
    printf("%d>",v);
}

list_content mul5(list_content v){
    return v;
}

list_content fold_function(list_content a,list_content b){
    return a+b;
}

int main() {
      list_node* list = list_create(15);

//    printf("%d\n", list_create(5)->value);
//    printf("%d\n",(int)  list_get(1000000000000000000,list_create(5)));
//    printf("%p\n",(void*)list);

//    list_add_front(2,list);
//    printf("%p\n",(void*)list);

    list_add_front(4, &list);
   // list_add_front(156, &list);
    list_add_back(12,&list);
    list_add_back(-12,&list);

    list_add_front(15,&list);
    printf("Node nx: %d\n",list_get(0,list));
    printf("len: %d\n", (int)list_length(list));
    printf("sum: %d\n", (int)list_sum(list));
    puts("Using for_each to write out the list:");
    list_for_each(list,function_print);
    puts("\nUsing list_map(e->return e*5)");
    list_for_each( list_map(list,mul5), function_print); // Yeah, there's a memory leak.
    puts("\nUsing list_map_mut(e->return e*5)");
    list_map_mut(list,mul5);
    list_for_each(list,function_print);
    printf("\nUsing list_foldl: %d\n", list_foldl(list,0,fold_function));
    list_free(&list);
    return 0;
}

