#include <stdio.h>
#include "list_tests.h"
#include "list.h"
#include "list_functions.h"

int main() {
    printf("%s","SPL.Lab #4.\nGive me some integers: ");
    list_node* input_list = read_list_from_std(512);

    size_t len = list_length(input_list);
    printf("List's length = %d", (int)len);
    if(0 == len){
        puts(", so bye-bye");
        return 0;
    }

    test_1(input_list);
/*   printf("%d\n", list_create(5)->value);
//    printf("%d\n",(int)  list_get(1000000000000000000,list_create(5)));
//    printf("%p\n",(void*)list);

//    list_add_front(2,list);
//    printf("%p\n",(void*)list);
    list_node* list = list_create(15);

    list_add_front(4, &list);
   // list_add_front(156, &list);
    list_add_back(12,&list);
    list_add_back(-12,&list);
    */

  /*  printf("Node nx: %d\n",list_get(0,list));
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
    */
    list_free(&input_list);
    return 0;
}

