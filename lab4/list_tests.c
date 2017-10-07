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



void test_1(list_node* list){
    puts("\n*******\nTesting following list:");
    print_list(list);
    puts("\n*******");
    printf("Sum = %d\n",(int)list_sum(list));
    puts("Using list_map(e->return e*5)");
    list_for_each( list_map(list,mul5), function_print); // Yeah, there's a memory leak.

    printf("\nUsing list_foldl to find the sum: %d\n", list_foldl(list,0,fold_function));
    printf("Using list_iterate to generate first %d powers of two:\n", (int)list_length(list));
    list_node* list_power2 = list_iterate(1,mul2,list_length(list));
    print_list(list_power2);
    list_free(&list_power2);
    puts("\n*That's it*");
}

void print_style_one(list_content v){
    printf("%d=>",v);
}
void print_style_two(list_content v){
    printf("%d, ",v);
}
int sqr(int v){
    return v*v;
}
int cube(int v){
    return v*v*v;
}
int max(int v1, int v2){
    return v1 > v2? v1 : v2;
}
int min(int v1, int v2){
    return v1 < v2? v1 : v2;
}
int abs(int v1){
    return v1 >= 0? v1 : -v1;
}
void test_2(list_node* list){
    puts("\n*******");
    puts("A set of tests #2");
    puts("\n*******\nTesting following list:");
    print_list(list);
    puts("\n******");
    puts("Testing for_each to write out the list different ways:");
    list_for_each(list,print_style_one);
    putchar('\n');
    list_for_each(list,print_style_two);
    puts("\nTesting foldl to find min and max:");
    printf("Max: %d\n", list_foldl(list,INT_MIN,max));
    printf("Min: %d\n", list_foldl(list,INT_MAX,min));
    puts("Testing map to write out cubes and squares of the elements:");
    list_node* temp = list_map(list,sqr);
    print_list(temp);
    list_free(&temp);
    putchar('\n');
    temp = list_map(list,cube);
    print_list(temp);
    list_free(&temp);
    puts("\nUsing list_map_mut(e->return asb(e))");
    list_map_mut(list,abs);
    list_for_each(list,function_print);
}

void test_3_serialize(list_node* list, const char* const file_name){
    puts("\n*******");
    puts("A set of tests about the serializing");
    printf("\n*******\nTesting following list with file '%s'\n",file_name);
    print_list(list);
    puts("\n******");
    if(list_save(list,file_name))
        puts("Save's OK");
    else
        puts("!Save error!");
    if(list_load(&list,file_name + ".txt"))
        puts("Load's OK");
    else
        puts("Load error!");
    if(list_save_binary(list,file_name + ".bin"))
        puts("Save binary's OK");
    else
        puts("!Save error!");
}