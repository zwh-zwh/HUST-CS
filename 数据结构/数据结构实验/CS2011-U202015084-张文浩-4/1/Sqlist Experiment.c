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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef struct { //���Ա�˳��ṹ���Ķ���
	ElemType* elem; //Ԫ��ָ��
	int length; //���Ա���
	int listsize; //���Ա���󳤶�
} SqList;

typedef struct { //���Ա�ļ������Ͷ���
	struct {
		char name[30]; //���Ա�����
		SqList L; //���Ա�
	} elem[10]; //���Ա�����
	int length; //���Ա��ϳ���
} LISTS;

LISTS Lists;    //���Ա��ϵĶ���Lists

/***********��������************/
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

/***********������************/
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
			printf("��������Ҫ��ӵ����Ա�����ƣ�\n");
			do
			{
				flag=0;
				scanf("%s", ListName1);
				for(j=0;j<Lists.length;j++)
					if(!strcmp(ListName1,Lists.elem[j].name)) //���Ҽ������Ƿ������ָø����Ƶ����Ա�
					{
						flag=1;
						printf("�����ظ������������룡\n");
						break;
					}
			}while(flag==1); 
			AddList(&Lists, ListName1);
			printf("��ӳɹ���\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("��������Ҫɾ�������Ա�����ƣ�\n");
			scanf("%s", ListName2);
			
			ltmp1 = RemoveList(&Lists, ListName2);
			if (ltmp1 == ERROR)
				printf("���Ա�����û�и����Ա�\n");
			else
				printf("ɾ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 4:
			
			printf("��������Ҫ��λ�����Ա�����ƣ�\n");
			scanf("%s", ListName3);
			
			ltmp2 = LocateList(Lists, ListName3);
			if (ltmp2 == ERROR)
				printf("���Ա�����û�и����Ա�\n");
			else
				printf("�����Ա��λ��Ϊ%d\n", LocateList(Lists, ListName3));
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
				printf("�����Ա���Ϊ�գ�\n");
			else
				printf("�����Ա��ϲ�Ϊ�գ�\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("�����Ա��ϳ���Ϊ%d\n", ListsLength(Lists));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllLists(Lists))
				printf("�����Ա�����û��Ԫ�أ�\n");
			getchar();
			getchar();
			break;
		case 9:
			flag2=0;
			printf("��������Ҫ���������Ա����ţ�\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > Lists.length) {
				printf("�����������\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if(flag2==1) //���Ա��Ѿ������٣����˻�һ���˵�
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
				printf("��ѡ����Ĳ���[0~14]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("���س��˳���\n");
					break;
				case 1:
					if (InitList(&Lists.elem[num].L) == INFEASIBLE) 
						printf("���Ա��Ѿ���ʼ����\n");
					else 
						printf("��ʼ���ɹ���\n");
					getchar();
					getchar();
					break;
				case 2:
					flag2=0; //flag2���ã���������״̬
					if (DestroyList(&Lists.elem[num].L) == OK)
					{
						RemoveList(&Lists, Lists.elem[num].name);
						printf("���Ա����ٳɹ���\n");
						flag2=1;
					}
					else
						printf("���Ա�����ʧ�ܣ�\n");
					getchar();
					getchar();
					break;
				case 3:
					tmp0=ClearList(&Lists.elem[num].L);
					if (tmp0 == OK)
						printf("���Ա���ճɹ���\n");
					else if(tmp0==ERROR)
						printf("���Ա�Ϊ�գ�\n");
					else printf("���Ա�δ��ʼ����\n");
					getchar();
					getchar();
					break;
				case 4:
					tmp1 = ListEmpty(Lists.elem[num].L);
					if (tmp1 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
					else if (tmp1 == TRUE)
						printf("���Ա�Ϊ�գ�\n");
					else
						printf("���Ա�Ϊ�գ�\n");
					getchar();
					getchar();
					break;
				case 5:
					tmp2 = ListLength(Lists.elem[num].L);
					if (tmp2 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
					else
						printf("���Ա�ĳ���Ϊ%d\n", ListLength(Lists.elem[num].L));
					getchar();
					getchar();
					break;
				case 6:
					printf("��������Ҫ��ȡ��Ԫ�ص�λ�ã�\n");
					scanf("%d", &i);
					tmp3 = GetElem(Lists.elem[num].L, i, &e);
					if (tmp3 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
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
						printf("���Ա�δ��ʼ����\n");
					else if (tmp4 == ERROR)
						printf("���Ա���û�и�Ԫ�أ�\n");
					else
						printf("��Ԫ�������Ա��е�λ��Ϊ%d \n", tmp4);
					getchar();
					getchar();
					break;
				case 8:
					printf("��������Ҫ��ȡ�ĸ�Ԫ�ص�ǰ����\n");
					scanf("%d", &elem2);
					tmp5 = PriorElem(Lists.elem[num].L, elem2, &pre);
					if (tmp5 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
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
						printf("���Ա�δ��ʼ����\n");
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
						printf("���Ա�δ��ʼ����\n");
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
						printf("���Ա�δ��ʼ����\n");
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
						printf("���Ա��ǿձ�\n");
					else if (tmp9 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
					getchar();
					getchar();
					break;
				case 13:
					k=1;
					printf("��ѡ��ͨ�����̶����Ա���Ԫ�ظ�ֵ��1������ͨ�������ļ���ֵ��2����\n");
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
							printf("���Ա�δ��ʼ����\n");
						else if (temp0 == ERROR) printf("����ʧ�ܣ�\n");
						else if(temp0==OK)
							printf("����ɹ���\n");
					}
					getchar();
					getchar();
					break;
				case 14:
					
					printf("�����봢�����ݵ��ļ���:\n");
					scanf("%s", name2);
					temp00=SaveList(Lists.elem[num].L, name2);
					if (temp00 == INFEASIBLE)
						printf("���Ա�δ��ʼ����\n");
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

status InitList(SqList* L)
// ���Ա�Lδ��ʼ��������һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ�����������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ����ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ�����ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ�����������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else
		return L.length;
}

status GetElem(SqList L, int i, ElemType* e)
// ������Ա�L�ѳ�ʼ������ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ��������Ԫ��e�����Ա�L�е�λ����Ų�����OK�����e�����ڣ�����ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ������ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ������ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ������Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ����ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR�����򷵻�INFEASIBLE��
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
// ������Ա�L�ѳ�ʼ����������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK�����򷵻�INFEASIBLE��
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else if (L.length == 0) return ERROR;
	else {
		int i;
		printf("Ԫ������Ϊ��\n");
		for (i = 0; i < L.length - 1; i++)
			printf("%d ", L.elem[i]);
		if (L.length > 0)
			printf("%d", L.elem[L.length - 1]);
		return OK;
	}
}

status SaveList(SqList L, char FileName[])
// ������Ա�L�ѳ�ʼ���������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	if (L.elem == NULL)
		return INFEASIBLE;
	else {
		FILE* fp;
		if ((fp = fopen(FileName, "w")) == NULL)
			return ERROR;
		for (int i = 0; i < L.length; i++)
			fwrite(&L.elem[i], sizeof(ElemType), 1, fp); //��ѭ��д��
		fclose(fp);
		return OK;
	}
}

status LoadList(SqList* L, char FileName[])
{ // ������Ա�L�ѳ�ʼ������FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
	if (L->elem==NULL)
		return INFEASIBLE;
	else {
		if(L->length!=0)
		{
			printf("���Ա����Ѿ���Ԫ�أ�\n");
			return -2;
		}
		FILE* fp;
		if ((fp = fopen(FileName, "r")) == NULL)
			return ERROR;
		while (fread(&L->elem[L->length], sizeof(ElemType), 1, fp)) //��ѭ����ȡ
			L->length++;
		fclose(fp);
		return OK;
	}
}

status AddList(LISTS* Lists, char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ɺ�̨���Գ�����롣
{
	strcpy(Lists->elem[Lists->length].name, ListName);
	Lists->elem[Lists->length].L.elem = NULL;
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