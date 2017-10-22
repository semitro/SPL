#ifndef _SCALAR_
#define _SCALAR_

#include "stdio.h"

#define SIZE 4

int array1[SIZE] = {1, 2, -3, 0};
int array2[SIZE] = {4, 2, 1, 15};

int scalarProduct(int *v1, int *v2, const size_t size){
   long ans = 0;
   for(unsigned int i=0; i<size;i++)
       ans += v1[i]*v2[i];

   return ans;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    printf("%i\n", scalarProduct(array1,array2, SIZE));
    return 0;
}

#endif
