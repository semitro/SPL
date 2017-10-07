//
// Created by semitro on 07.10.17.
//
#include "list_tests.h"

void function_print(list_content v){
    printf("%d>",v);
}

void print_list(list_node* list){
    list_for_each(list,function_print);
}

list_content mul5(list_content v){
    return v*5;
}

list_content fold_function(list_content a,list_content b){
    return a+b;
}

list_content mul2(list_content v){
    return v*2;
}

list_node* read_list_from_std(size_t max_buffer){
    char input_buffer[max_buffer];
    fgets(input_buffer, max_buffer,stdin);

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

void test_1(list_node* list){
    puts("\n*******\nTesting following list:");
    print_list(list);
    puts("\n*******");
    printf("Sum = %d\n",(int)list_sum(list));
    puts("Using list_map(e->return e*5)");
    list_for_each( list_map(list,mul5), function_print); // Yeah, there's a memory leak.
    puts("\nUsing list_map_mut(e->return e*5)");
    list_map_mut(list,mul5);
    list_for_each(list,function_print);
    printf("\nUsing list_foldl to find the sum: %d\n", list_foldl(list,0,fold_function));
    printf("Using list_iterate to generate first %d powers of two:\n", (int)list_length(list));
    list_node* list_power2 = list_iterate(1,mul2,list_length(list));
    print_list(list_power2);
    list_free(&list_power2);
    puts("\n*That's it*");
}