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
    int data; //数据
    struct varnode* next; //下一个文字
}varnode, * Varnode; //文字类型
typedef struct clause {
    int count_of_var; //文字数量
    struct varnode* head; //第一个文字
    struct clause* next; //第一个子句
}clause, * Clause; //子句类型
typedef struct total
{
    int varcount; //文字数
    int clacount; //公式数
    int singleclause; //单子句数量
    int emptyclause; //空子句个数
    int count_of_clause; //目前子句数量
    struct clause* clahead; //第一个子句
}total, * Total; //公式类型

int allresult;//所有解的个数
int varcount; //文字数
int* result; //结果数组
char filename[100]; //需要读入的文件名
char savefile[100]; //需要写入的文件名

//SAT相关函数
Total fileload(Total SATList, char* filename); //读入cnf文件
Total Duplicate(Total SATList); //复制子句集
status Traverse(Total SATList); //遍历子句集
int findsingleclause(Total SATList); //寻找单子句
status deleteclause(Total SATList, int temp); //删除符合要求的子句
status deleteword(Total SATList, int temp); //删除符合要求的文字
status addclause(Total SATList, int temp); //添加单子句
int judgeemptyclause(Total SATList); //判断子句集中是否含有空子句
int judgeemptytotal(Total SATList); //判断子句集是否为空
int getword1(Total SATList); //获取变元的2种算法
int getword2(Total SATList);
int getword3(Total SATList);
Total destroy(Total SATList); //销毁子句集
status DPLL1(Total SATList); //使用了获取变元算法一的DPLL算法
status DPLL2(Total SATList); //使用了获取变元算法二的DPLL算法
status saveanswer(Total SATList, int dresult, double time); //保存答案为res文件
status savecnf(Total SATList); //保存为cnf文件

//数独相关函数
void DPLLPRO(Total SATList); //返回解的个数的DPLL算法
status printsudoku(int sudoku[][10]); //打印数独
status convertresult(int sudoku[][10]); //结果数组转换为数独
status judgenum(int sudoku[][10], int row, int col, int n); //判断数是否可填
Total initial(Total SATList); //子句集初始化
status createnode(Total SATList, int temp); //创建文字
status createorigin(Total SATList, int sudoku[][10]); //原数独中不为0的数的创建
status createsingle(Total SATList, int sudoku[][10]); //单元格约束
status createrow(Total SATList, int sudoku[][10]); //行约束
status createcol(Total SATList, int sudoku[][10]); //列约束
status createblock(Total SATList, int sudoku[][10]); //分块约束
Total createcnf(Total SATList, int sudoku[][10]); //数独转化为SAT算例
status createsudoku(Total SATList, int sudoku[][10]); //创建数独
status createsudoku2(int sudoku[][10], int row, int num);
status digholes(int sudoku[][10], int count, int holes[][10]); //挖洞法创建待求解数独

#endif