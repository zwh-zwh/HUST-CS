#include<iostream>
#include"ex3_stack.h"
extern const char* TestSTACK(int& s);
int main()
{
	int s;
	const char* q = TestSTACK(s);
	printf("%d, %s\n", s, q);
	return 0;
}