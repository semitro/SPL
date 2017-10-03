

int function(char* str){
/*	__asm__(
		"xor %rdi, %rdi;\n\t"
		"movb %0, %rdi;\n\t"
		:"=r"(*str)
		:"r"(*str)
		:"%rdi"
		);
*/
	int x = str[1];
//	str[2] = 42;
	return 42;
}
//		"movb 42, (%%rdi);\n\t"

void function2(){

}

