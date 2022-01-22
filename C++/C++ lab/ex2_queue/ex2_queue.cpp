#include"ex2_queue.h"
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}//��ʼ�����У��������m��Ԫ��
QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]),max(q.max),head(q.head),tail(q.tail)
{
	for (int i = 0; i < q.max; i++)
		elems[i] = q.elems[i];
}//��q�����ʼ������
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max), head(q.head), tail(q.tail)
{
	*(int **)&q.elems = 0;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
}//��q�ƶ���ʼ������
QUEUE::operator int() const noexcept
{
	if (elems)
		return (tail - head + max) % max;
	return 0;
}//���ض��е�ʵ��Ԫ�ظ���
int QUEUE::size() const noexcept
{
	return max;
}//���ض�����������Ԫ�ظ���max
QUEUE& QUEUE::operator<<(int e)
{
	if ((tail + 1) % max == head)
		throw"QUEUE is full!";
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}//��e�����β���������ص�ǰ����
QUEUE& QUEUE::operator>>(int& e)
{
	if (head == tail)
		throw"QUEUE is empty!";
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
QUEUE& QUEUE::operator=(const QUEUE& q)
{
	if (this == &q) return *this;
	if (elems)
	{
		delete[] elems;
		*(int **)&elems = 0;
	}
	*(int**)&elems = new int[q.max];
	*(int*)&max = q.max;
	head = q.head;
	tail = q.tail;
	for (int i = 0; i < q.max; i++)
		elems[i] = q.elems[i];
	return *this;
}//�����ֵ�����ر���ֵ����
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept
{
	if (this == &q) return *this;
	if (elems)
	{
		delete[] elems;
		*(int**)&elems = 0;
	}
	*(int**)&elems = q.elems;
	*(int*)&max = q.max;
	tail = q.tail;
	head = q.head;
	*(int**)&q.elems = 0;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
	return *this;
}//�ƶ���ֵ�����ر���ֵ����
char* QUEUE::print(char* s) const noexcept
{
	for (int i = 0; i < (*this); i++)
		s += sprintf(s, "%d,", elems[(head + i) % max]);
	return s;
}//��ӡ������s������s
QUEUE::~QUEUE()
{
	if (elems)
	{
		delete[] elems;
		*(int**)&elems = 0;
		head = tail = *(int*)&max = 0;
	}
}//���ٵ�ǰ����