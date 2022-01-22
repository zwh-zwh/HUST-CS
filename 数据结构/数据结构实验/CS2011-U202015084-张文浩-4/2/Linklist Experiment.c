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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef struct LNode {  //��������ʽ�ṹ�����Ķ���
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;
typedef struct { //����ļ������Ͷ���
	struct {
		char name[30]; //��������
		LinkList L; //����
	} elem[10]; //��������
	int length; //�����ϳ���
} LISTS;

LISTS Lists;    //�����ϵĶ���Lists

/***********��������************/
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

/***********������************/
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
		printf("��ѡ����Ĳ���[0~9]:");
		scanf("%d", &op1);
		switch (op1) {
		case 0:
			break;
		case 1:
			Initlists(&Lists);
			printf("��ʼ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("��������Ҫ��ӵ���������ƣ�\n");
			do
			{
				flag = 0;
				scanf("%s", ListName1);
				for (j = 0; j < Lists.length; j++)
					if (!strcmp(ListName1, Lists.elem[j].name)) //���Ҽ������Ƿ������ָø����Ƶ�����
					{
						flag = 1;
						printf("�����ظ������������룡\n");
						break;
					}
			} while (flag == 1);
			AddList(&Lists, ListName1);
			printf("��ӳɹ���\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("��������Ҫɾ������������ƣ�\n");
			scanf("%s", ListName2);

			ltmp1 = RemoveList(&Lists, ListName2);
			if (ltmp1 == ERROR)
				printf("��������û�и�����\n");
			else
				printf("ɾ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 4:

			printf("��������Ҫ��λ����������ƣ�\n");
			scanf("%s", ListName3);

			ltmp2 = LocateList(Lists, ListName3);
			if (ltmp2 == ERROR)
				printf("��������û�и�����\n");
			else
				printf("�������λ��Ϊ%d\n", LocateList(Lists, ListName3));
			getchar();
			getchar();
			break;
		case 5:
			ClearLists(&Lists);
			printf("��ճɹ���\n");
			getchar();
			getchar();
			break;
		case 6:
			ltmp3 = ListsEmpty(Lists);
			if (ltmp3 == TRUE)
				printf("��������Ϊ�գ�\n");
			else
				printf("�������ϲ�Ϊ�գ�\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("�������ϳ���Ϊ%d\n", ListsLength(Lists));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllLists(Lists))
				printf("����������û��Ԫ�أ�\n");
			getchar();
			getchar();
			break;
		case 9:
			flag2 = 0;
			printf("��������Ҫ�������������ţ�\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > Lists.length) {
				printf("�����������\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if (flag2 == 1)
				{
					op2=1;
					break;
				} //�����Ѿ������٣����˻�һ���˵�
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
				printf("��ѡ����Ĳ���[0~14]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("���س��˳���\n");
					break;
				case 1:
					if (InitList(&Lists.elem[num].L) == INFEASIBLE)
						printf("�����Ѿ���ʼ����\n");
					else
						printf("��ʼ���ɹ���\n");
					getchar();
					getchar();
					break;
				case 2:
					flag2 = 0; //flag2���ã���������״̬
					if (DestroyList(&Lists.elem[num].L) == OK)
					{
						RemoveList(&Lists, Lists.elem[num].name);
						printf("�������ٳɹ���\n");
						flag2 = 1;
					}
					else
						printf("��������ʧ�ܣ�\n");
					getchar();
					getchar();
					break;
				case 3:
					tmp0 = ClearList(&Lists.elem[num].L);
					if (tmp0 == OK)
						printf("������ճɹ���\n");
					else if (tmp0 == ERROR)
						printf("����Ϊ�գ�\n");
					else printf("����δ��ʼ����\n");
					getchar();
					getchar();
					break;
				case 4:
					tmp1 = ListEmpty(Lists.elem[num].L);
					if (tmp1 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp1 == TRUE)
						printf("����Ϊ�գ�\n");
					else
						printf("����Ϊ�գ�\n");
					getchar();
					getchar();
					break;
				case 5:
					tmp2 = ListLength(Lists.elem[num].L);
					if (tmp2 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else
						printf("����ĳ���Ϊ%d\n", ListLength(Lists.elem[num].L));
					getchar();
					getchar();
					break;
				case 6:
					printf("��������Ҫ��ȡ��Ԫ�ص�λ�ã�\n");
					scanf("%d", &i);
					tmp3 = GetElem(Lists.elem[num].L, i, &e);
					if (tmp3 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp3 == ERROR)
						printf("����λ������\n");
					else
						printf("��%d��Ԫ��Ϊ%d��\n", i, e);
					getchar();
					getchar();
					break;
				case 7:
					printf("��������Ҫ���ҵ�Ԫ�أ�\n");
					scanf("%d", &elem1);
					tmp4 = LocateElem(Lists.elem[num].L, elem1);
					if (tmp4 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp4 == ERROR)
						printf("������û�и�Ԫ�أ�\n");
					else
						printf("��Ԫ���������е�λ��Ϊ%d \n", tmp4);
					getchar();
					getchar();
					break;
				case 8:
					printf("��������Ҫ��ȡ�ĸ�Ԫ�ص�ǰ����\n");
					scanf("%d", &elem2);
					tmp5 = PriorElem(Lists.elem[num].L, elem2, &pre);
					if (tmp5 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp5 == ERROR)
						printf("��Ԫ��û��ǰ����\n");
					else
						printf("��Ԫ�ص�ǰ��Ϊ%d\n", pre);
					getchar();
					getchar();
					break;
				case 9:
					printf("��������Ҫ��ȡ�ĸ�Ԫ�صĺ�̣�\n");
					scanf("%d", &elem3);
					tmp6 = NextElem(Lists.elem[num].L, elem3, &next);
					if (tmp6 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp6 == ERROR)
						printf("��Ԫ��û�к�̣�\n");
					else
						printf("��Ԫ�صĺ��Ϊ%d", next);
					getchar();
					getchar();
					break;
				case 10:
					printf("���������Ԫ�ص�λ���Լ���Ҫ�����Ԫ�أ�\n");
					scanf("%d%d", &loc, &elem4);
					tmp7 = ListInsert(&Lists.elem[num].L, loc, elem4);
					if (tmp7 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp7 == ERROR)
						printf("����λ������\n");
					else
						printf("����ɹ�\n");
					getchar();
					getchar();
					break;
				case 11:
					printf("��������Ҫɾ����Ԫ�ص�λ�ã�\n");
					scanf("%d", &deloc);
					tmp8 = ListDelete(&Lists.elem[num].L, deloc, &elem5);
					if (tmp8 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (tmp8 == ERROR)
						printf("ɾ��λ������\n");
					else
						printf("ɾ���ɹ���ɾ����Ԫ��Ϊ%d\n", elem5);
					getchar();
					getchar();
					break;
				case 12:
					tmp9 = ListTrabverse(Lists.elem[num].L);
					if (tmp9 == ERROR)
						printf("�����ǿձ�\n");
					else if (tmp9 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					getchar();
					getchar();
					break;
				case 13:
					k = 1;
					printf("��ѡ��ͨ�����̶�������Ԫ�ظ�ֵ��1������ͨ�������ļ���ֵ��2����\n");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("��������Ҫ�����Ԫ�ظ�����\n");
						scanf("%d", &n);
						printf("���������ݣ�\n");
						while (k <= n) {
							int temp;
							scanf("%d", &temp);
							ListInsert(&Lists.elem[num].L, k, temp); //�൱��һ��һ�εز���Ԫ��
							k++;
						}
						printf("����ɹ�\n");
					}
					else
					{
						printf("�������ļ�����\n");
						scanf("%s", name);
						temp0 = LoadList(&Lists.elem[num].L, name);
						if (temp0 == INFEASIBLE)
							printf("����δ��ʼ����\n");
						else if (temp0 == ERROR) printf("����ʧ�ܣ�\n");
						else if (temp0 == OK)
							printf("����ɹ���\n");
					}
					getchar();
					getchar();
					break;
				case 14:

					printf("�����봢�����ݵ��ļ���:\n");
					scanf("%s", name2);
					temp00 = SaveList(Lists.elem[num].L, name2);
					if (temp00 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (temp00 == ERROR) printf("д��ʧ�ܣ�\n");
					else
						printf("д��ɹ���\n");
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
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
	else if (L->next == NULL) return TRUE;
	else return FALSE;
	/********** End **********/
}
status ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (L == NULL) return INFEASIBLE;
    else if(L->next==NULL) return ERROR;
	else
	{
		LNode* p = L->next;
        printf("Ԫ������Ϊ��\n");
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
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
		}//��ѭ��д��
		fclose(fp);
		return OK;
	}

	/********** End 1 **********/
}

status LoadList(LinkList* L, char FileName[])
// ������Ա�L�Ѿ���ʼ������Ϊ�գ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin 2 *********/
	if ((*L) == NULL)
		return INFEASIBLE;
	else {
        if((*L)->next!=NULL)
            printf("�������Ѿ���Ԫ�أ�\n");
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ɺ�̨���Գ�����롣
{
	strcpy(Lists->elem[Lists->length].name, ListName);
	Lists->elem[Lists->length].L = NULL;
	Lists->length++;
	return OK;
}

status RemoveList(LISTS* Lists, char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
	//������Ա���
	Lists->length = 0;
	return OK;
}

status ListsEmpty(LISTS Lists) {
	//�ж����Ա����Ƿ�Ϊ��
	if (Lists.length == 0)
		return TRUE;
	else
		return FALSE;
}

status ListsLength(LISTS Lists) {
	//�����Ա��ϵĳ���
	return Lists.length;
}

status PrintAllLists(LISTS Lists) {
	//��ӡ���Ա����е�����Ԫ��
	if (Lists.length == 0) return ERROR;
	else {
		printf("�������Ա�����Ϊ:\n");
		for (int i = 0; i < Lists.length; i++) {
			printf("%d\t%s\n", i + 1, Lists.elem[i].name);
		}
	}
	return OK;
}

status Initlists(LISTS* Lists) {
	//��ʼ�����Ա���
	Lists->length = 0;
	return OK;
}