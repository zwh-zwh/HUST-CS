#include<iostream>
#include"ex1_queue_c.h"
extern const char* TestQueue(int& s);
int main()
{
	int s;
	const char* q = TestQueue(s);
	printf("%d, %s\n", s, q);
	return 0;
}