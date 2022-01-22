#include"ex2_queue.h"
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}//初始化队列：最多申请m个元素
QUEUE::QUEUE(const QUEUE& q) :elems(new int[q.max]),max(q.max),head(q.head),tail(q.tail)
{
	for (int i = 0; i < q.max; i++)
		elems[i] = q.elems[i];
}//用q深拷贝初始化队列
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max), head(q.head), tail(q.tail)
{
	*(int **)&q.elems = 0;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
}//用q移动初始化队列
QUEUE::operator int() const noexcept
{
	if (elems)
		return (tail - head + max) % max;
	return 0;
}//返回队列的实际元素个数
int QUEUE::size() const noexcept
{
	return max;
}//返回队列申请的最大元素个数max
QUEUE& QUEUE::operator<<(int e)
{
	if ((tail + 1) % max == head)
		throw"QUEUE is full!";
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}//将e入队列尾部，并返回当前队列
QUEUE& QUEUE::operator>>(int& e)
{
	if (head == tail)
		throw"QUEUE is empty!";
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}//从队首出元素到e，并返回当前队列
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
}//深拷贝赋值并返回被赋值队列
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
}//移动赋值并返回被赋值队列
char* QUEUE::print(char* s) const noexcept
{
	for (int i = 0; i < (*this); i++)
		s += sprintf(s, "%d,", elems[(head + i) % max]);
	return s;
}//打印队列至s并返回s
QUEUE::~QUEUE()
{
	if (elems)
	{
		delete[] elems;
		*(int**)&elems = 0;
		head = tail = *(int*)&max = 0;
	}
}//销毁当前队列