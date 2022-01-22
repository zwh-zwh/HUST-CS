#include"ex3_stack.h"
STACK::STACK(int m) :QUEUE(m), q(m) {}
//��ʼ��ջ�������2m-2��Ԫ��
STACK::STACK(const STACK& s) : QUEUE((QUEUE&)s), q((QUEUE&)s.q) {}         		
//��ջs�����ʼ��ջ
STACK::STACK(STACK&& s)noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {} 		
//��ջs�ƶ�������ʼ��ջ
int STACK::size()const noexcept
{
	return 2 * q.size();
}//����ջ��������2m
STACK::operator int() const noexcept
{
	return q + QUEUE::operator int();
}//����ջ��ʵ��Ԫ�ظ���
STACK& STACK::operator<<(int e)
{
	if (*this == size()-2)
		throw("STACK is full!");
	if (QUEUE::operator int()<QUEUE::size()-1)
		QUEUE::operator<<(e);
	else q << e;
	return *this;
}//��e��ջ�������ص�ǰջ
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
}//��ջ��e�������ص�ǰջ
STACK& STACK::operator=(const STACK& s)
{
	if (this == &s) return *this;
	QUEUE::operator=((QUEUE&)s);
	q = s.q;
	return *this;
}//�����ֵ�����ر���ֵջ
STACK& STACK::operator=(STACK&& s)noexcept
{
	if (this == &s) return *this;
	QUEUE::operator=((QUEUE&&)s);
	q =(QUEUE&&)s.q;
	return *this;
}//�ƶ���ֵ�����ر���ֵջ
char* STACK::print(char* b)const noexcept
{
	QUEUE::print(b);
	
	//((QUEUE)*this).print(b); �ȼ���QUEUE &p = (QUEUE &)(*this);  p.QUEUE:: print(b);
	q.print(b + strlen(b));
	return b;
}//��ջ�׵�ջ����ӡջԪ�� 
STACK::~STACK()noexcept {}//����ջ