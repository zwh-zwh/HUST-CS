#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
#include <sstream>
using namespace std;
template <typename T>
class MAT {
	T* const e;							        //ָ���������;���Ԫ�ص�ָ��
	const int r, c;							    //�������r����c��С
public:
	MAT(int r, int c);						    //������
	MAT(const MAT& a);				            //�������
	MAT(MAT&& a)noexcept;			            //�ƶ�����
	virtual ~MAT()noexcept;                     //����
	virtual T* const operator[ ](int r);        //ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;				//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
	virtual char* print(char* s)const noexcept; //print�����s������s�����ÿո���������ûس�����
};


template<typename T>
MAT<T>::MAT(int r, int c) :e(new T[r*c]), r(r), c(c) {}//������

template<typename T>
MAT<T>::MAT(const MAT& a) :e(new T[a.r*a.c]), r(a.r), c(a.c)
{
	for (int i = 0; i < r * c; i++)
		e[i] = a.e[i];
}//�������

template<typename T>
MAT<T>::MAT(MAT&& a)noexcept :e(a.e), r(a.r), c(a.c)
{
	*(T **)&a.e = 0;
	*(int *)&a.r = 0;
	*(int *)&a.c = 0;
}//�ƶ�����

template<typename T>
MAT<T>::~MAT()noexcept
{
	if (e)
	{
		delete[] e;
		*(T**)&e = 0;
		*(int*)&r = *(int*)&c = 0;
	}
}//��������

template<typename T>
T* const MAT<T>::operator[ ](int r)
{
	if (r<0 || r>=this->r)
		throw("error");
	return e + r * c;
}//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣

template<typename T>
MAT<T> MAT<T>::operator+(const MAT& a)const
{
	if (r != a.r || c != a.c)
		throw("error");
	MAT ans(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			ans[i][j] = ((MAT &)(*this))[i][j] + (*(MAT*)&a)[i][j];
	return ans;
}//����ӷ������ܼ����쳣

template<typename T>
MAT<T> MAT<T>::operator-(const MAT& a)const
{
	if (r != a.r || c != a.c)
		throw("error");
	MAT ans(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			ans[i][j] = ((MAT&)(*this))[i][j] - (*(MAT*)&a)[i][j];
	return ans;
}//������������ܼ����쳣

template<typename T>
MAT<T> MAT<T>::operator*(const MAT& a)const
{
	if(c!=a.r)
		throw("error");
	MAT ans(r, a.c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < a.c; j++)
		{
			ans[i][j] = 0;
			for (int k = 0; k < c; k++)
				ans[i][j] += ((MAT&)(*this))[i][k] * (*(MAT*)&a)[k][j];
		}
	return ans;
}//����˷������ܳ����쳣

template<typename T>
MAT<T> MAT<T>::operator~()const
{
	MAT ans(c, r);
	for (int i = 0; i < c; i++)
		for (int j = 0; j < r; j++)
			ans[i][j] = ((MAT&)(*this))[j][i];
	return ans;
}//����ת��

template<typename T>
MAT<T>& MAT<T>::operator=(const MAT& a)
{
	if (this == &a) 
		return *this;
	if (e)
	{
		delete[] e;
		*(T**)&e = 0;
	}
	*(T**)&e = new T[a.r*a.c];
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	for (int i = 0; i < r * c; i++)
		e[i] = a.e[i];
	return *this;
}//�����ֵ����

template<typename T>
MAT<T>& MAT<T>::operator=(MAT&& a)noexcept
{
	if (this == &a) 
		return *this;
	if (e)
	{
		delete[] e;
		*(T**)&e = 0;
	}
	*(T**)&e = a.e;
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	*(T**)&a.e = 0;
	*(int*)&a.r = 0;
	*(int*)&a.c = 0;
	return *this;
}//�ƶ���ֵ����

template<typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a)
{
	return *this = *this + a;
}//��+=������

template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a)
{
	return *this = *this - a;
}//��-=������

template<typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a)
{
	return *this = *this * a;
}//��*=������

template<typename T>
char* MAT<T>::print(char* s)const noexcept
{
	stringstream ss;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			ss << ((MAT&)(*this))[i][j]<<",";
		ss << '\n';
	}
	string str = ss.str();
	strcpy(s, str.c_str());
	return s;
}//print�����s������s�����ÿո���������ûس�����

template MAT<int>;			
template MAT<long long>;		