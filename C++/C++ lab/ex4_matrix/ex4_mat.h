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
	T* const e;							        //指向所有整型矩阵元素的指针
	const int r, c;							    //矩阵的行r和列c大小
public:
	MAT(int r, int c);						    //矩阵定义
	MAT(const MAT& a);				            //深拷贝构造
	MAT(MAT&& a)noexcept;			            //移动构造
	virtual ~MAT()noexcept;                     //析构
	virtual T* const operator[ ](int r);        //取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;				//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
	virtual char* print(char* s)const noexcept; //print输出至s并返回s：列用空格隔开，行用回车结束
};


template<typename T>
MAT<T>::MAT(int r, int c) :e(new T[r*c]), r(r), c(c) {}//矩阵定义

template<typename T>
MAT<T>::MAT(const MAT& a) :e(new T[a.r*a.c]), r(a.r), c(a.c)
{
	for (int i = 0; i < r * c; i++)
		e[i] = a.e[i];
}//深拷贝构造

template<typename T>
MAT<T>::MAT(MAT&& a)noexcept :e(a.e), r(a.r), c(a.c)
{
	*(T **)&a.e = 0;
	*(int *)&a.r = 0;
	*(int *)&a.c = 0;
}//移动构造

template<typename T>
MAT<T>::~MAT()noexcept
{
	if (e)
	{
		delete[] e;
		*(T**)&e = 0;
		*(int*)&r = *(int*)&c = 0;
	}
}//析构函数

template<typename T>
T* const MAT<T>::operator[ ](int r)
{
	if (r<0 || r>=this->r)
		throw("error");
	return e + r * c;
}//取矩阵r行的第一个元素地址，r越界抛异常

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
}//矩阵加法，不能加抛异常

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
}//矩阵减法，不能减抛异常

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
}//矩阵乘法，不能乘抛异常

template<typename T>
MAT<T> MAT<T>::operator~()const
{
	MAT ans(c, r);
	for (int i = 0; i < c; i++)
		for (int j = 0; j < r; j++)
			ans[i][j] = ((MAT&)(*this))[j][i];
	return ans;
}//矩阵转置

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
}//深拷贝赋值运算

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
}//移动赋值运算

template<typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a)
{
	return *this = *this + a;
}//“+=”运算

template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a)
{
	return *this = *this - a;
}//“-=”运算

template<typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a)
{
	return *this = *this * a;
}//“*=”运算

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
}//print输出至s并返回s：列用空格隔开，行用回车结束

template MAT<int>;			
template MAT<long long>;		