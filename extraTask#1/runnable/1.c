#include <stdio.h>

int function(char* str){
	puts("hello from the otherside!");
/*	__asm__(
		"xor %rdi, %rdi;\n\t"
		"movb %0, %rdi;\n\t"
		:"=r"(*str)
		:"r"(*str)
		:"%rdi"
		);
*/
	//char* cheat = *str;
	
	int i = 0;
	int ans = 0;
	
	while( str[i] != '\0'){
		 if('*' == str[i]) ans++;
		i++;
	}

	
	return  ans;
}
//		"movb 42, (%%rdi);\n\t"

char function2(){
	return 42;
}

