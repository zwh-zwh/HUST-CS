#pragma once
#ifndef _SAT_H_
#define _SAT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define OK 1
#define ERROR 0

typedef int status;

typedef struct varnode {
    int data; //����
    struct varnode* next; //��һ������
}varnode, * Varnode; //��������
typedef struct clause {
    int count_of_var; //��������
    struct varnode* head; //��һ������
    struct clause* next; //��һ���Ӿ�
}clause, * Clause; //�Ӿ�����
typedef struct total
{
    int varcount; //������
    int clacount; //��ʽ��
    int singleclause; //���Ӿ�����
    int emptyclause; //���Ӿ����
    int count_of_clause; //Ŀǰ�Ӿ�����
    struct clause* clahead; //��һ���Ӿ�
}total, * Total; //��ʽ����

int allresult;//���н�ĸ���
int varcount; //������
int* result; //�������
char filename[100]; //��Ҫ������ļ���
char savefile[100]; //��Ҫд����ļ���

//SAT��غ���
Total fileload(Total SATList, char* filename); //����cnf�ļ�
Total Duplicate(Total SATList); //�����Ӿ伯
status Traverse(Total SATList); //�����Ӿ伯
int findsingleclause(Total SATList); //Ѱ�ҵ��Ӿ�
status deleteclause(Total SATList, int temp); //ɾ������Ҫ����Ӿ�
status deleteword(Total SATList, int temp); //ɾ������Ҫ�������
status addclause(Total SATList, int temp); //��ӵ��Ӿ�
int judgeemptyclause(Total SATList); //�ж��Ӿ伯���Ƿ��п��Ӿ�
int judgeemptytotal(Total SATList); //�ж��Ӿ伯�Ƿ�Ϊ��
int getword1(Total SATList); //��ȡ��Ԫ��2���㷨
int getword2(Total SATList);
int getword3(Total SATList);
Total destroy(Total SATList); //�����Ӿ伯
status DPLL1(Total SATList); //ʹ���˻�ȡ��Ԫ�㷨һ��DPLL�㷨
status DPLL2(Total SATList); //ʹ���˻�ȡ��Ԫ�㷨����DPLL�㷨
status saveanswer(Total SATList, int dresult, double time); //�����Ϊres�ļ�
status savecnf(Total SATList); //����Ϊcnf�ļ�

//������غ���
void DPLLPRO(Total SATList); //���ؽ�ĸ�����DPLL�㷨
status printsudoku(int sudoku[][10]); //��ӡ����
status convertresult(int sudoku[][10]); //�������ת��Ϊ����
status judgenum(int sudoku[][10], int row, int col, int n); //�ж����Ƿ����
Total initial(Total SATList); //�Ӿ伯��ʼ��
status createnode(Total SATList, int temp); //��������
status createorigin(Total SATList, int sudoku[][10]); //ԭ�����в�Ϊ0�����Ĵ���
status createsingle(Total SATList, int sudoku[][10]); //��Ԫ��Լ��
status createrow(Total SATList, int sudoku[][10]); //��Լ��
status createcol(Total SATList, int sudoku[][10]); //��Լ��
status createblock(Total SATList, int sudoku[][10]); //�ֿ�Լ��
Total createcnf(Total SATList, int sudoku[][10]); //����ת��ΪSAT����
status createsudoku(Total SATList, int sudoku[][10]); //��������
status createsudoku2(int sudoku[][10], int row, int num);
status digholes(int sudoku[][10], int count, int holes[][10]); //�ڶ����������������

#endif