#include "ex4_mat.h"
extern const char* TestMAT(int& s);
int main(int argc, char* argv[]) 					//请扩展main()测试其他运算
{
	int s;
	const char* q = TestMAT(s);
	printf("%d, %s\n", s, q);
	return 0;
}
