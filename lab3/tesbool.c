#include <stdio.h>
struct s {
};


int array1[10] = {1,1,1,1,2,2,2,2,3,3};
int main(){
    void* p = NULL;
    struct s x;
    printf("%d\n",(int)sizeof( p ));
    printf("struc {} size == %d\n", (int)sizeof(x));
    printf("size of the array == %d\n", 
            (int) (sizeof(array1)/sizeof(array1[0])));

    int ii = 7;
    sizeof(ii++);
    printf("%d\n",ii);
    
    return 0;
}