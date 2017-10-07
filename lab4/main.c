#include <stdio.h>
#include "list.h"
#include "list_functions.h"

void function_print(list_content v){
    printf("%d>",v);
}

void print_list(list_node* list){
    list_for_each(list,function_print);
}

list_content mul5(list_content v){
    return v;
}

list_content fold_function(list_content a,list_content b){
    return a+b;
}

list_node* read_list_from_std(size_t max_buffer){
        char input_buffer[max_buffer];
        fgets(input_buffer, sizeof(max_buffer),stdin);

        int n;
        list_node* input_list = NULL;
        int i,j;
        for(i=j=0; sscanf(input_buffer+i,"%d%n",&n,&j) == 1; i+=j)
            if(input_list)
                list_add_front(n,&input_list);
             else
                 input_list = list_create(n);
    return input_list;
}

int main() {
    printf("%s","SPL.Lab #4.\nGive me some integers: ");
    list_node* input_list = read_list_from_std(512);

    size_t len = list_length(input_list);
    printf("\nList's length = %d", (int)len);
    if(0 == len){
        puts(", so bye-bye");
        return 0;
    }
    puts("\n*******");
    print_list(input_list);
    puts("\n*******");

//    printf("%d\n", list_create(5)->value);
//    printf("%d\n",(int)  list_get(1000000000000000000,list_create(5)));
//    printf("%p\n",(void*)list);

//    list_add_front(2,list);
//    printf("%p\n",(void*)list);
    list_node* list = list_create(15);

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

