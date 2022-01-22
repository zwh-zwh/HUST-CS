#include<iostream>
#include"ex2_queue.h"
extern const char* TestQUEUE(int& s);
int main()
{
	int s;
	const char* q = TestQUEUE(s);
	printf("%d, %s\n", s, q);
	return 0;
}