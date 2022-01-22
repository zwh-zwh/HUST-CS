#include"ex3_stack.h"
STACK::STACK(int m) :QUEUE(m), q(m) {}
//初始化栈：最多存放2m-2个元素
STACK::STACK(const STACK& s) : QUEUE((QUEUE&)s), q((QUEUE&)s.q) {}         		
//用栈s深拷贝初始化栈
STACK::STACK(STACK&& s)noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {} 		
//用栈s移动拷贝初始化栈
int STACK::size()const noexcept
{
	return 2 * q.size();
}//返回栈的容量即2m
STACK::operator int() const noexcept
{
	return q + QUEUE::operator int();
}//返回栈的实际元素个数
STACK& STACK::operator<<(int e)
{
	if (*this == size()-2)
		throw("STACK is full!");
	if (QUEUE::operator int()<QUEUE::size()-1)
		QUEUE::operator<<(e);
	else q << e;
	return *this;
}//将e入栈，并返回当前栈
STACK& STACK::operator>>(int& e)
{
	if(*this == 0)
		throw("STACK is empty!");
	if (QUEUE::operator int() && q==0)
	{
		int temp;
		int count = QUEUE::operator int() - 1;
		while (count)
		{
			QUEUE::operator>>(temp);
			QUEUE::operator<<(temp);
			count--;
		}
		QUEUE::operator>>(e);
	}
	else
	{
		int temp;
		int count = q - 1;
		while (count)
		{
			q >> temp;
			q << temp;
			count--;
		}
		q >> e;
	}
	return *this;
}//出栈到e，并返回当前栈
STACK& STACK::operator=(const STACK& s)
{
	if (this == &s) return *this;
	QUEUE::operator=((QUEUE&)s);
	q = s.q;
	return *this;
}//深拷贝赋值并返回被赋值栈
STACK& STACK::operator=(STACK&& s)noexcept
{
	if (this == &s) return *this;
	QUEUE::operator=((QUEUE&&)s);
	q =(QUEUE&&)s.q;
	return *this;
}//移动赋值并返回被赋值栈
char* STACK::print(char* b)const noexcept
{
	QUEUE::print(b);
	
	//((QUEUE)*this).print(b); 等价于QUEUE &p = (QUEUE &)(*this);  p.QUEUE:: print(b);
	q.print(b + strlen(b));
	return b;
}//从栈底到栈顶打印栈元素 
STACK::~STACK()noexcept {}//销毁栈