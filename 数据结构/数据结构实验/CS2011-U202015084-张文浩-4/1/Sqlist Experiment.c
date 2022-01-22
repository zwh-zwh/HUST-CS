#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int status;
typedef int ElemType; //数据元素类型定义
typedef struct { //线性表（顺序结构）的定义
	ElemType* elem; //元素指针
	int length; //线性表长度
	int listsize; //线性表最大长度
} SqList;

typedef struct { //线性表的集合类型定义
	struct {
		char name[30]; //线性表名称
		SqList L; //线性表
	} elem[10]; //线性表数组
	int length; //线性表集合长度
} LISTS;

LISTS Lists;    //线性表集合的定义Lists

/***********函数声明************/
status InitList(SqList* L);
status DestroyList(SqList* L);
status ClearList(SqList* L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType* e);
status LocateElem(SqList L, ElemType e); 
status PriorElem(SqList L, ElemType e, ElemType* pre);
status NextElem(SqList L, ElemType e, ElemType* next);
status ListInsert(SqList* L, int i, ElemType e);
status ListDelete(SqList* L, int i, ElemType* e);
status ListTrabverse(SqList L);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList* L, char FileName[]);
status AddList(LISTS* Lists, char ListName[]);
status RemoveList(LISTS* Lists, char ListName[]);
status LocateList(LISTS Lists, char ListName[]);
status ClearLists(LISTS* Lists);
status ListsEmpty(LISTS Lists);
status ListsLength(LISTS Lists);
status PrintAllLists(LISTS Lists);
status Initlists(LISTS* Lists);

/***********主程序************/
int main() {
	SqList L;
	LISTS Lists;
	char ListName1[100],ListName2[100],ListName3[100],name[100],name2[100];
	int op1 = 1, op2 = 1, n, k =1 ,choice,i,j,flag=0,flag2=0,e;
	int ltmp1,ltmp2,ltmp3;
	int num1,num;
	int tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,tmp9,tmp0,temp0,temp00,elem1,elem2,elem3, elem4,elem5,pre,next;
	int loc ,deloc;
	while (op1) {
		system("cls");
		printf("\n\n");
		printf("Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------\n");
		printf("    1.InitLists       2.AddList\n");
		printf("    3.RemoveList      4.LocateList\n");
		printf("    5.ClearLists      6.ListsEmpty\n");
		printf("    7.ListsLength     8.PrintAllLists\n");
		printf("    9.OperateList     0.Exit\n");
		printf("-------------------------------------------\n");
		printf("请选择你的操作[0~9]:");
		scanf("%d", &op1);
		switch (op1) {
		case 0:
			break;
		case 1:
			Initlists(&Lists);
			printf("初始化成功！\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("请输入需要添加的线性表的名称：\n");
			do
			{
				flag=0;
				scanf("%s", ListName1);
				for(j=0;j<Lists.length;j++)
					if(!strcmp(ListName1,Lists.elem[j].name)) //查找集合中是否早已又该该名称的线性表
					{
						flag=1;
						printf("名称重复！请重新输入！\n");
						break;
					}
			}while(flag==1); 
			AddList(&Lists, ListName1);
			printf("添加成功！\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("请输入需要删除的线性表的名称：\n");
			scanf("%s", ListName2);
			
			ltmp1 = RemoveList(&Lists, ListName2);
			if (ltmp1 == ERROR)
				printf("线性表集合中没有该线性表！\n");
			else
				printf("删除成功！\n");
			getchar();
			getchar();
			break;
		case 4:
			
			printf("请输入需要定位的线性表的名称：\n");
			scanf("%s", ListName3);
			
			ltmp2 = LocateList(Lists, ListName3);
			if (ltmp2 == ERROR)
				printf("线性表集合中没有该线性表！\n");
			else
				printf("该线性表的位置为%d\n", LocateList(Lists, ListName3));
			getchar();
			getchar();
			break;
		case 5:
			ClearLists(&Lists);
			printf("清空成功！\n");
			getchar();
			getchar();
			break;
		case 6:
			
			ltmp3 = ListsEmpty(Lists);
			if (ltmp3 == TRUE)
				printf("该线性表集合为空！\n");
			else
				printf("该线性表集合不为空！\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("该线性表集合长度为%d\n", ListsLength(Lists));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllLists(Lists))
				printf("该线性表集合中没有元素！\n");
			getchar();
			getchar();
			break;
		case 9:
			flag2=0;
			printf("请输入需要操作的线性表的序号：\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > Lists.length) {
				printf("输入序号有误！\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if(flag2==1) //线性表已经被销毁，就退回一级菜单
				{
					op2=1;
					break;
				}
				system("cls");
				printf("\n\n");
				printf("Menu for Linear Table On Sequence Structure \n");
				printf("-------------------------------------------\n");
				printf("    1. Initlist         2. DestroyList\n");
				printf("    3. ClearList        4. ListEmpty\n");
				printf("    5. ListLength       6. GetElem \n");
				printf("    7. LocateElem       8. PriorElem \n");
				printf("    9. NextElem         10.ListInsert \n");
				printf("    11.ListDelete       12.ListTrabverse\n");
				printf("    13.InputElem        14.SaveList\n");
				printf("    0. Exit\n");
				printf("-------------------------------------------\n");
				printf("请选择你的操作[0~14]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("按回车退出！\n");
					break;
				case 1:
					if (InitList(&Lists.elem[num].L) == INFEASIBLE) 
						printf("线性表已经初始化！\n");
					else 
						printf("初始化成功！\n");
					getchar();
					getchar();
					break;
				case 2:
					flag2=0; //flag2作用：代表销毁状态
					if (DestroyList(&Lists.elem[num].L) == OK)
					{
						RemoveList(&Lists, Lists.elem[num].name);
						printf("线性表销毁成功！\n");
						flag2=1;
					}
					else
						printf("线性表销毁失败！\n");
					getchar();
					getchar();
					break;
				case 3:
					tmp0=ClearList(&Lists.elem[num].L);
					if (tmp0 == OK)
						printf("线性表清空成功！\n");
					else if(tmp0==ERROR)
						printf("线性表为空！\n");
					else printf("线性表未初始化！\n");
					getchar();
					getchar();
					break;
				case 4:
					tmp1 = ListEmpty(Lists.elem[num].L);
					if (tmp1 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp1 == TRUE)
						printf("线性表为空！\n");
					else
						printf("线性表不为空！\n");
					getchar();
					getchar();
					break;
				case 5:
					tmp2 = ListLength(Lists.elem[num].L);
					if (tmp2 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else
						printf("线性表的长度为%d\n", ListLength(Lists.elem[num].L));
					getchar();
					getchar();
					break;
				case 6:
					printf("请输入需要获取的元素的位置：\n");
					scanf("%d", &i);
					tmp3 = GetElem(Lists.elem[num].L, i, &e);
					if (tmp3 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp3 == ERROR)
						printf("输入位置有误！\n");
					else
						printf("第%d号元素为%d。\n", i, e);
					getchar();
					getchar();
					break;
				case 7:
					printf("请输入需要查找的元素：\n");
					scanf("%d", &elem1);
					tmp4 = LocateElem(Lists.elem[num].L, elem1);
					if (tmp4 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp4 == ERROR)
						printf("线性表中没有该元素！\n");
					else
						printf("该元素在线性表中的位置为%d \n", tmp4);
					getchar();
					getchar();
					break;
				case 8:
					printf("请输入需要获取哪个元素的前驱：\n");
					scanf("%d", &elem2);
					tmp5 = PriorElem(Lists.elem[num].L, elem2, &pre);
					if (tmp5 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp5 == ERROR)
						printf("该元素没有前驱！\n");
					else
						printf("该元素的前驱为%d\n", pre);
					getchar();
					getchar();
					break;
				case 9:
					printf("请输入需要获取哪个元素的后继：\n");
					scanf("%d", &elem3);
					tmp6 = NextElem(Lists.elem[num].L, elem3, &next);
					if (tmp6 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp6 == ERROR)
						printf("该元素没有后继！\n");
					else
						printf("该元素的后继为%d", next);
					getchar();
					getchar();
					break;
				case 10:
					printf("请输入插入元素的位置以及需要插入的元素：\n");
					scanf("%d%d", &loc, &elem4);
					tmp7 = ListInsert(&Lists.elem[num].L, loc, elem4);
					if (tmp7 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp7 == ERROR)
						printf("插入位置有误！\n");
					else
						printf("插入成功\n");
					getchar();
					getchar();
					break;
				case 11:
					printf("请输入需要删除的元素的位置：\n");
					scanf("%d", &deloc);
					tmp8 = ListDelete(&Lists.elem[num].L, deloc, &elem5);
					if (tmp8 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (tmp8 == ERROR)
						printf("删除位置有误！\n");
					else
						printf("删除成功，删除的元素为%d\n", elem5);
					getchar();
					getchar();
					break;
				case 12:
					tmp9 = ListTrabverse(Lists.elem[num].L);
					if (tmp9 == ERROR)
						printf("线性表是空表！\n");
					else if (tmp9 == INFEASIBLE)
						printf("线性表未初始化！\n");
					getchar();
					getchar();
					break;
				case 13:
					k=1;
					printf("请选择通过键盘对线性表中元素赋值（1）或者通过读入文件赋值（2）：\n");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("请输入需要输入的元素个数：\n");
						scanf("%d", &n);
						printf("请输入数据：\n");
						while (k <= n) {
							int temp;
							scanf("%d", &temp);
							ListInsert(&Lists.elem[num].L, k, temp); //相当于一次一次地插入元素
							k++;
						}
						printf("输入成功\n");
					}
					else
					{
						printf("请输入文件名：\n");
						scanf("%s", name);
						temp0 = LoadList(&Lists.elem[num].L, name);
						if (temp0 == INFEASIBLE)
							printf("线性表未初始化！\n");
						else if (temp0 == ERROR) printf("读入失败！\n");
						else if(temp0==OK)
							printf("读入成功！\n");
					}
					getchar();
					getchar();
					break;
				case 14:
					
					printf("请输入储存数据的文件名:\n");
					scanf("%s", name2);
					temp00=SaveList(Lists.elem[num].L, name2);
					if (temp00 == INFEASIBLE)
						printf("线性表未初始化！\n");
					else if (temp00 == ERROR) printf("写入失败！\n");
					else
						printf("写入成功！\n");
					getchar();
					getchar();
					break;
				}
			}
			op2 = 1;
			if(flag2==0)
			{
				getchar();
				getchar();
				break;
			}
		}
	}
	return 0;
}

status InitList(SqList* L)
// 线性表L未初始化，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if (L->elem == NULL) {
		L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
		L->length = 0;
		L->listsize = LIST_INIT_SIZE;
		return OK;
	}
	else
		return INFEASIBLE;
}

status DestroyList(SqList* L)
// 如果线性表L已初始化，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if (L->elem != NULL) {
		free(L->elem);
		L->elem = NULL;
		L->length = 0;
		L->listsize = 0;
		return OK;
	}
	else
		return INFEASIBLE;
}

status ClearList(SqList* L)
// 如果线性表L已初始化，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	if (L->elem == NULL)
		return INFEASIBLE;
	else if(L->length==0) 
		return ERROR;
	else {
		L->length = 0;
		return OK;
	}
}

status ListEmpty(SqList L)
// 如果线性表L已初始化，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		if (L.length == 0)
			return TRUE;
		else
			return FALSE;
	}
}

status ListLength(SqList L)
// 如果线性表L已初始化，返回线性表L的长度，否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else
		return L.length;
}

status GetElem(SqList L, int i, ElemType* e)
// 如果线性表L已初始化，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		if (i < 1 || i > L.length)
			return ERROR;
		else {
			*e = L.elem[i - 1];
			return OK;
		}
	}
}

status LocateElem(SqList L, ElemType e)
// 如果线性表L已初始化，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		int i = 0;
		while (L.elem[i] != e && i < L.length)
			i++;
		if (i == L.length)
			return ERROR;
		else
			return i + 1;

	}
}

status PriorElem(SqList L, ElemType e, ElemType* pre)
// 如果线性表L已初始化，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		int i = 0;
		while (L.elem[i] != e && i < L.length)
			i++;
		if (i == L.length || i == 0)
			return ERROR;
		else {
			*pre = L.elem[i - 1];
			return OK;
		}
	}
}

status NextElem(SqList L, ElemType e, ElemType* next)
// 如果线性表L已初始化，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		int i = 0;
		while (L.elem[i] != e && i < L.length)
			i++;
		if (i == L.length || i == L.length - 1)
			return ERROR;
		else {
			*next = L.elem[i + 1];
			return OK;
		}
	}
}

status ListInsert(SqList* L, int i, ElemType e)
// 如果线性表L已初始化，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；否则返回INFEASIBLE。
{
	if (L->elem == NULL)
		return INFEASIBLE;
	else {
		if (i < 1 || i > L->length + 1)
			return ERROR;
		else {
			if (L->length >= L->listsize) {
				ElemType* newbase = (ElemType*)realloc(L->elem, (L->length + LISTINCREMENT) * sizeof(ElemType));
				if (newbase == NULL)
					return OVERFLOW;
				L->elem = newbase;
				L->listsize += LISTINCREMENT;
			}
			int j;
			if (L->length > 0) {
				for (j = L->length - 1; j >= i - 1; j--)
					L->elem[j + 1] = L->elem[j];
			}
			L->elem[i - 1] = e;
			L->length++;
			return OK;
		}
	}
}

status ListDelete(SqList* L, int i, ElemType* e)
// 如果线性表L已初始化，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；否则返回INFEASIBLE。
{
	if (L->elem == NULL)
		return INFEASIBLE;
	else {
		if (i < 1 || i > L->length)
			return ERROR;
		else {
			*e = L->elem[i - 1];
			for (int k = i - 1; k < L->length; k++)
				L->elem[k] = L->elem[k + 1];
			L->length--;
			return OK;
		}
	}
}

status ListTrabverse(SqList L)
// 如果线性表L已初始化，依次显示线性表中的元素，每个元素间空一格，返回OK；否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else if (L.length == 0) return ERROR;
	else {
		int i;
		printf("元素依次为：\n");
		for (i = 0; i < L.length - 1; i++)
			printf("%d ", L.elem[i]);
		if (L.length > 0)
			printf("%d", L.elem[L.length - 1]);
		return OK;
	}
}

status SaveList(SqList L, char FileName[])
// 如果线性表L已初始化，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		FILE* fp;
		if ((fp = fopen(FileName, "w")) == NULL)
			return ERROR;
		for (int i = 0; i < L.length; i++)
			fwrite(&L.elem[i], sizeof(ElemType), 1, fp); //用循环写入
		fclose(fp);
		return OK;
	}
}

status LoadList(SqList* L, char FileName[])
{ // 如果线性表L已初始化，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
	if (L->elem==NULL)
		return INFEASIBLE;
	else {
		if(L->length!=0)
		{
			printf("线性表中已经有元素！\n");
			return -2;
		}
		FILE* fp;
		if ((fp = fopen(FileName, "r")) == NULL)
			return ERROR;
		while (fread(&L->elem[L->length], sizeof(ElemType), 1, fp)) //用循环读取
			L->length++;
		fclose(fp);
		return OK;
	}
}

status AddList(LISTS* Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据由后台测试程序插入。
{
	strcpy(Lists->elem[Lists->length].name, ListName);
	Lists->elem[Lists->length].L.elem = NULL;
	Lists->length++;
	return OK;
}

status RemoveList(LISTS* Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
	int  i, k;
	for (i = 0; i < Lists->length; i++) {
		if (strcmp(Lists->elem[i].name, ListName))
			continue;
		else {
			Lists->elem[i].name[0] = '\0';
			free(Lists->elem[i].L.elem);
			Lists->elem[i].L.elem = NULL;
			Lists->elem[i].L.length = 0;
			Lists->elem[i].L.listsize = 0;
			for (k = i; k < Lists->length; k++)
				Lists->elem[k] = Lists->elem[k + 1];
			Lists->length--;
			return OK;
		}
	}
	return ERROR;
}

status LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	int i;
	for (i = 0; i < Lists.length; i++) {
		if (strcmp(Lists.elem[i].name, ListName))
			continue;
		else
			return i + 1;
	}
	return ERROR;
}

status ClearLists(LISTS* Lists) {
//清空线性表集合
	Lists->length = 0;
	return OK;
}

status ListsEmpty(LISTS Lists) {
//判断线性表集合是否为空
	if (Lists.length == 0)
		return TRUE;
	else
		return FALSE;
}

status ListsLength(LISTS Lists) {
//求线性表集合的长度
	return Lists.length;
}

status PrintAllLists(LISTS Lists) {
//打印线性表集合中的所有元素
	if (Lists.length == 0) return ERROR;
	else {
		printf("所有线性表依次为:\n");
		for (int i = 0; i < Lists.length; i++) {
			printf("%d\t%s\n", i + 1, Lists.elem[i].name);
		}
	}
	return OK;
}

status Initlists(LISTS* Lists) {
//初始化线性表集合
	Lists->length = 0;
	return OK;
}