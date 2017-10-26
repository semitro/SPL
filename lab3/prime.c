#ifndef _PRIME_C
#define _PRIME_C

#include "math.h"
#include "stdio.h"

// Nowadays, math does not consider 1 as a prime or not prime number
_Bool isPrime(const unsigned long n){
    if(0 == n)
        return 0;

    for(unsigned int i=2;i<=sqrt(n);i++)
        if(0 == n % i)
            return 0;
            
    return 1;
}

int main(int argc, char** argv){
    unsigned long n;
    (void)argc;
    (void)argv;
    if(scanf("%lu", &n) == 1) 
        if(isPrime(n))
            puts("yes");
        else
            puts("no");
    else
        puts("Input data's incorrect!");

    return 0;
}

#endif