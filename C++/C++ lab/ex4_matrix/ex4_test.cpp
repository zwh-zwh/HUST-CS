#include "ex4_mat.h"
extern const char* TestMAT(int& s);
int main(int argc, char* argv[]) 					//����չmain()������������
{
	int s;
	const char* q = TestMAT(s);
	printf("%d, %s\n", s, q);
	return 0;
}
