#include"ex1_queue_c.h"

void initQueue(Queue* const p, int m)
{
    *(int**)&p->elems = new int[m];
    *(int*)&p->max = m;
    p->head = p->tail = 0;
}//��ʼ��pָ���У��������m��Ԫ��

void initQueue(Queue* const p, const Queue& s)
{
    *(int**)&p->elems = new int[s.max];
    *(int*)&p->max = s.max;
    p->head = s.head;
    p->tail = s.tail;
    for (int i = 0; i < s.max; i++)
        p->elems[i] = s.elems[i];
} //��s�����ʼ��pָ����

void initQueue(Queue* const p, Queue&& s)
{
    *(int*)&p->max = s.max;
    *(int**)&p->elems = s.elems;
    p->tail = s.tail;
    p->head = s.head;
    *(int**)&s.elems = NULL;
    *(int*)&s.max = 0;
    s.tail = s.head = 0;
}//��s�ƶ���ʼ��pָ����

int number(const Queue* const p)
{
    if(p->elems)
        return (p->tail - p->head + p->max) % p->max;
    return 0;
}//����pָ���е�ʵ��Ԫ�ظ���

int  size(const Queue* const p)
{
    return p->max;
}//����pָ������������Ԫ�ظ���max

Queue* const enter(Queue* const p, int e)
{
    if ((p->tail + 1) % p->max == p->head)
        throw"Queue is full!";
    p->elems[p->tail] = e;
    p->tail = (p->tail + 1) % p->max;
    return p;
}//��e�����β����������p

Queue* const leave(Queue* const p, int& e)
{
    if (p->head == p->tail) 
        throw"Queue is empty!";
    e = p->elems[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}//�Ӷ��׳�Ԫ�ص�e��������p

Queue* const assign(Queue* const p, const Queue& q)
{
    if (p == &q) return p;
    if (p->elems)
    {
        delete[] p->elems;
        *(int**)&p->elems = NULL;
    }
    *(int**)&p->elems = new int[q.max];
    *(int*)&p->max = q.max;
    p->head = q.head;
    p->tail = q.tail;
    for (int i = 0; i < q.max; i++)
        p->elems[i] = q.elems[i];
    return p;
}//�����s�����в�����p

Queue* const assign(Queue* const p, Queue&& q)
{
    if (p==&q) return p;
    if (p->elems) {
        delete[] p->elems;
        *(int**)&p->elems = NULL;
    }
    *(int**)&p->elems = q.elems;
    *(int*)&p->max = q.max;
    p->tail = q.tail;
    p->head = q.head;
    *(int**)&q.elems = NULL;
    *(int*)&q.max = 0;
    q.head = q.tail = 0;
    return p;
}//�ƶ���s�����в�����p

char* print(const Queue* const p, char* s)
{
    for (int i = 0; i < number(p); i++)
        s += sprintf(s, "%d,", p->elems[(p->head + i) % p->max]);
    return s;
}//��ӡpָ������s������s

void destroyQueue(Queue* const p)
{
    if (p->elems)
    {
        delete[] p->elems;
        *(int**)&p->elems = 0;
        p->head = p->tail = *(int*)&p->max = 0;
    }
}//����