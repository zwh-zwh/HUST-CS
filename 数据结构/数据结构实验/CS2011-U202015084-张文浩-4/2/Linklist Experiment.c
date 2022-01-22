#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义
typedef struct LNode {  //单链表（链式结构）结点的定义
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;
typedef struct { //链表的集合类型定义
	struct {
		char name[30]; //链表名称
		LinkList L; //链表
	} elem[10]; //链表数组
	int length; //链表集合长度
} LISTS;

LISTS Lists;    //链表集合的定义Lists

/***********函数声明************/
status InitList(LinkList* L);
status DestroyList(LinkList* L);
status ClearList(LinkList* L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType* e);
status LocateElem(LinkList L, ElemType e);
status PriorElem(LinkList L, ElemType e, ElemType* pre);
status NextElem(LinkList L, ElemType e, ElemType* next);
status ListInsert(LinkList* L, int i, ElemType e);
status ListDelete(LinkList* L, int i, ElemType* e);
status ListTrabverse(LinkList L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList* L, char FileName[]);
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
	LISTS Lists;
	char ListName1[100], ListName2[100], ListName3[100], name[100], name2[100];
	int op1 = 1, op2 = 1, n, k = 1, choice, i, j, flag = 0, flag2 = 0, e;
	int ltmp1, ltmp2, ltmp3;
	int num1, num;
	int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp0, temp0, temp00, elem1, elem2, elem3, elem4, elem5, pre, next;
	int loc, deloc;
	while (op1) {
		system("cls");
		printf("\n\n");
		printf("Menu for Linear Table On Link Structure \n");
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
			printf("请输入需要添加的链表的名称：\n");
			do
			{
				flag = 0;
				scanf("%s", ListName1);
				for (j = 0; j < Lists.length; j++)
					if (!strcmp(ListName1, Lists.elem[j].name)) //查找集合中是否早已又该该名称的链表
					{
						flag = 1;
						printf("名称重复！请重新输入！\n");
						break;
					}
			} while (flag == 1);
			AddList(&Lists, ListName1);
			printf("添加成功！\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("请输入需要删除的链表的名称：\n");
			scanf("%s", ListName2);

			ltmp1 = RemoveList(&Lists, ListName2);
			if (ltmp1 == ERROR)
				printf("链表集合中没有该链表！\n");
			else
				printf("删除成功！\n");
			getchar();
			getchar();
			break;
		case 4:

			printf("请输入需要定位的链表的名称：\n");
			scanf("%s", ListName3);

			ltmp2 = LocateList(Lists, ListName3);
			if (ltmp2 == ERROR)
				printf("链表集合中没有该链表！\n");
			else
				printf("该链表的位置为%d\n", LocateList(Lists, ListName3));
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
				printf("该链表集合为空！\n");
			else
				printf("该链表集合不为空！\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("该链表集合长度为%d\n", ListsLength(Lists));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllLists(Lists))
				printf("该链表集合中没有元素！\n");
			getchar();
			getchar();
			break;
		case 9:
			flag2 = 0;
			printf("请输入需要操作的链表的序号：\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > Lists.length) {
				printf("输入序号有误！\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if (flag2 == 1)
				{
					op2=1;
					break;
				} //链表已经被销毁，就退回一级菜单
				system("cls");
				printf("\n\n");
				printf("Menu for Linear Table On Link Structure \n");
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
						printf("链表已经初始化！\n");
					else
						printf("初始化成功！\n");
					getchar();
					getchar();
					break;
				case 2:
					flag2 = 0; //flag2作用：代表销毁状态
					if (DestroyList(&Lists.elem[num].L) == OK)
					{
						RemoveList(&Lists, Lists.elem[num].name);
						printf("链表销毁成功！\n");
						flag2 = 1;
					}
					else
						printf("链表销毁失败！\n");
					getchar();
					getchar();
					break;
				case 3:
					tmp0 = ClearList(&Lists.elem[num].L);
					if (tmp0 == OK)
						printf("链表清空成功！\n");
					else if (tmp0 == ERROR)
						printf("链表为空！\n");
					else printf("链表未初始化！\n");
					getchar();
					getchar();
					break;
				case 4:
					tmp1 = ListEmpty(Lists.elem[num].L);
					if (tmp1 == INFEASIBLE)
						printf("链表未初始化！\n");
					else if (tmp1 == TRUE)
						printf("链表为空！\n");
					else
						printf("链表不为空！\n");
					getchar();
					getchar();
					break;
				case 5:
					tmp2 = ListLength(Lists.elem[num].L);
					if (tmp2 == INFEASIBLE)
						printf("链表未初始化！\n");
					else
						printf("链表的长度为%d\n", ListLength(Lists.elem[num].L));
					getchar();
					getchar();
					break;
				case 6:
					printf("请输入需要获取的元素的位置：\n");
					scanf("%d", &i);
					tmp3 = GetElem(Lists.elem[num].L, i, &e);
					if (tmp3 == INFEASIBLE)
						printf("链表未初始化！\n");
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
						printf("链表未初始化！\n");
					else if (tmp4 == ERROR)
						printf("链表中没有该元素！\n");
					else
						printf("该元素在链表中的位置为%d \n", tmp4);
					getchar();
					getchar();
					break;
				case 8:
					printf("请输入需要获取哪个元素的前驱：\n");
					scanf("%d", &elem2);
					tmp5 = PriorElem(Lists.elem[num].L, elem2, &pre);
					if (tmp5 == INFEASIBLE)
						printf("链表未初始化！\n");
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
						printf("链表未初始化！\n");
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
						printf("链表未初始化！\n");
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
						printf("链表未初始化！\n");
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
						printf("链表是空表！\n");
					else if (tmp9 == INFEASIBLE)
						printf("链表未初始化！\n");
					getchar();
					getchar();
					break;
				case 13:
					k = 1;
					printf("请选择通过键盘对链表中元素赋值（1）或者通过读入文件赋值（2）：\n");
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
							printf("链表未初始化！\n");
						else if (temp0 == ERROR) printf("读入失败！\n");
						else if (temp0 == OK)
							printf("读入成功！\n");
					}
					getchar();
					getchar();
					break;
				case 14:

					printf("请输入储存数据的文件名:\n");
					scanf("%s", name2);
					temp00 = SaveList(Lists.elem[num].L, name2);
					if (temp00 == INFEASIBLE)
						printf("链表未初始化！\n");
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
status InitList(LinkList* L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if ((*L) != NULL) return INFEASIBLE;
	else
	{
		(*L) = (LinkList)malloc(sizeof(LNode));
		(*L)->next = NULL;
		return OK;
	}

	/********** End **********/
}
status DestroyList(LinkList* L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if ((*L) == NULL) return INFEASIBLE;
	else {
		LNode* p, * q;
		p = (*L)->next;
		q = (*L);
		while (p)
		{
			q = p->next;
			free(p);
			p = q;
		}
		free((*L));
		(*L) = NULL;
		return OK;
	}

	/********** End **********/
}
status ClearList(LinkList* L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if ((*L) == NULL) return INFEASIBLE;
	else {
		LNode* p, * q;
		p = (*L)->next;
		q = (*L);
		while (p)
		{
			q = p->next;
			free(p);
			p = q;
		}
		(*L)->next = NULL;
		return OK;
	}

	/********** End **********/
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else if (L->next == NULL) return TRUE;
	else return FALSE;
	/********** End **********/
}
status ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else
	{
		int len = 0;
		LNode* p = L->next;
		while (p)
		{
			len++;
			p = p->next;
		}
		return len;
	}

	/********** End **********/
}
status GetElem(LinkList L, int i, ElemType* e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else
	{
		int len = 0;
		LNode* p = L->next;
		while (p)
		{
			len++;
			p = p->next;
		}
		if (i<1 || i>len)
			return ERROR;
		else
		{
			int k = 0;
			p = L->next;
			while (k < i - 1 && p)
			{
				p = p->next;
				k++;
			}
			*e = p->data;
			return OK;
		}
	}

	/********** End **********/
}
status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else {
		LNode* p = L->next;
		int i = 1;
		while (p && p->data != e)
		{
			p = p->next;
			i++;
		}
		if (!p) return ERROR;
		else return i;
	}

	/********** End **********/
}
status PriorElem(LinkList L, ElemType e, ElemType* pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else {
		LNode* p = L->next, * q = L;
		while (p && p->data != e)
		{
			q = p;
			p = p->next;
		}
		if (p == L->next || !p) return ERROR;
		else
		{
			*pre = q->data;
			return OK;
		}
	}

	/********** End **********/
}
status NextElem(LinkList L, ElemType e, ElemType* next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else {
		LNode* p = L->next;
		while (p && p->data != e)
			p = p->next;
		if (p == NULL)
			return ERROR;
		if (p->next == NULL)
			return ERROR;
		else
		{
			*next = p->next->data;
			return OK;
		}
	}

	/********** End **********/
}
status ListInsert(LinkList* L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if ((*L) == NULL) return INFEASIBLE;
	else {
		int len = 0;
		LNode* p = (*L)->next, * q = (*L);
		while (p)
		{
			len++;
			p = p->next;
		}
		if (i < 1 || (i > len + 1))
			return ERROR;
		else {
			int k = 0;
			p = (*L)->next;
			while (k < i - 1 && p)
			{
				q = p;
				p = p->next;
				k++;
			}
			LNode* s = (LNode*)malloc(sizeof(LNode));
			s->data = e;
			q->next = s;
			s->next = p;
			return OK;
		}
	}

	/********** End **********/
}
status ListDelete(LinkList* L, int i, ElemType* e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if ((*L) == NULL) return INFEASIBLE;
	else
	{
		int len = 0;
		LNode* p = (*L)->next, * q = (*L);
		while (p)
		{
			len++;
			p = p->next;
		}
		if (i<1 || i>len)
			return ERROR;
		else
		{
			int k = 0;
			p = (*L)->next;
			while (k < i - 1 && p)
			{
				q = p;
				p = p->next;
				k++;
			}
			*e = p->data;
			q->next = p->next;
			free(p);
			return OK;
		}
	}

	/********** End **********/
}
status ListTrabverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
    else if(L->next==NULL) return ERROR;
	else
	{
		LNode* p = L->next;
        printf("元素依次为：\n");
		while (p)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		return OK;
	}

	/********** End **********/
}
status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin 1 *********/
	if (L == NULL)
		return INFEASIBLE;
	else {
		FILE* fp;
		if ((fp = fopen(FileName, "w")) == NULL)
			return ERROR;
		LNode* p = L->next;
		while (p)
		{
			fwrite(&p->data, sizeof(ElemType), 1, fp);
			p = p->next;
		}//用循环写入
		fclose(fp);
		return OK;
	}

	/********** End 1 **********/
}

status LoadList(LinkList* L, char FileName[])
// 如果线性表L已经初始化而且为空，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	// 请在这里补充代码，完成本关任务
	/********** Begin 2 *********/
	if ((*L) == NULL)
		return INFEASIBLE;
	else {
        if((*L)->next!=NULL)
            printf("链表中已经有元素！\n");
        else
        {
            FILE* fp;
            if ((fp = fopen(FileName, "r")) == NULL)
                return ERROR;
            (*L) = (LinkList)malloc(sizeof(LNode));
            LNode* p = (LNode*)malloc(sizeof(LNode));
            LNode* q=NULL, * r=NULL;
            (*L)->next = p;
            while (fread(&p->data, sizeof(ElemType), 1, fp))
            {
                q = (LNode*)malloc(sizeof(LNode));
                q->next = NULL;
                r = p;
                p->next = q;
                p = q;
            }
            free(p);
            r->next = NULL;
            fclose(fp);
            return OK;
        }
	}

	/********** End 2 **********/
}
status AddList(LISTS* Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据由后台测试程序插入。
{
	strcpy(Lists->elem[Lists->length].name, ListName);
	Lists->elem[Lists->length].L = NULL;
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
			free(Lists->elem[i].L);
			Lists->elem[i].L = NULL;
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