#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType;
typedef struct {
	KeyType  key;
	char others[20];
} TElemType; //�������������Ͷ���
typedef struct BiTNode {    //���������Ķ���
	TElemType data; //������
	struct BiTNode* lchild, * rchild; //���Һ���ָ��
} BiTNode, * BiTree;
typedef struct { //�������ļ������Ͷ���
	struct {
		char name[30]; //����������
		BiTree T; //������
	} elem[10]; //����������
	int length; //���������ϳ���
} BITREES;
BiTree temp1;
status judge(TElemType definition[]);
status CreateBiTree(BiTree& T, TElemType definition[]);
status ClearBiTree(BiTree& T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree& T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status Traverse(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);
BiTNode* GetFather(BiTree T, KeyType e);
BiTNode* Getlast(BiTree T);
status DeleteNode(BiTree& T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
status AddBiTree(BITREES* BiTrees, char BiTreeName[]);
status RemoveBiTree(BITREES* BiTrees, char BiTreeName[]);
status LocateBiTree(BITREES BiTrees, char BiTreeName[]);
status ClearBiTrees(BITREES* BiTrees);
status BiTreesEmpty(BITREES BiTrees);
status BiTreesLength(BITREES BiTrees);
status PrintAllBiTrees(BITREES BiTrees);
status InitBiTrees(BITREES* BiTrees);
void visit(BiTree T);
TElemType* p;

/***********������************/
int main() {
	BITREES BiTrees;
	char BiTreeName1[100], BiTreeName2[100], BiTreeName3[100], name[100], name2[100];
	int op1 = 1, op2 = 1, n, k = 1, choice, i, j, flag = 0, flag2 = 0,flag3=0, e, LR;
	int ltmp1, ltmp2, ltmp3;
	int num1, num;
	int tmp1, tmp2, tmp3, tmp4,    tmp0, temp0, temp00, elem2;
	TElemType* definition, value, c;
	BiTree temp;
	while (op1) {
		system("cls");
		printf("\n\n");
		printf("Menu for BiTree \n");
		printf("-------------------------------------------\n");
		printf("    1.InitBiTrees       2.AddBiTree\n");
		printf("    3.RemoveBiTree      4.LocateBiTree\n");
		printf("    5.ClearBiTrees      6.BiTreesEmpty\n");
		printf("    7.BiTreesLength     8.PrintAllBiTrees\n");
		printf("    9.OperateBiTree     0.Exit\n");
		printf("-------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~9]:");
		scanf("%d", &op1);
		switch (op1) {
		case 0:
			break;
		case 1:
			InitBiTrees(&BiTrees);
			printf("��ʼ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("��������Ҫ��ӵĶ����������ƣ�\n");
			do
			{
				flag = 0;
				scanf("%s", BiTreeName1);
				for (j = 0; j < BiTrees.length; j++)
					if (!strcmp(BiTreeName1, BiTrees.elem[j].name)) //���Ҽ������Ƿ������ָø����ƵĶ�����
					{
						flag = 1;
						printf("�����ظ������������룡\n");
						break;
					}
			} while (flag == 1);
			AddBiTree(&BiTrees, BiTreeName1);
			printf("��ӳɹ���\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("��������Ҫɾ���Ķ����������ƣ�\n");
			scanf("%s", BiTreeName2);

			ltmp1 = RemoveBiTree(&BiTrees, BiTreeName2);
			if (ltmp1 == ERROR)
				printf("������������û�иö�������\n");
			else
				printf("ɾ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 4:

			printf("��������Ҫ��λ�Ķ����������ƣ�\n");
			scanf("%s", BiTreeName3);

			ltmp2 = LocateBiTree(BiTrees, BiTreeName3);
			if (ltmp2 == ERROR)
				printf("������������û�иö�������\n");
			else
				printf("�ö�������λ��Ϊ%d\n", LocateBiTree(BiTrees, BiTreeName3));
			getchar();
			getchar();
			break;
		case 5:
			ClearBiTrees(&BiTrees);
			printf("��ճɹ���\n");
			getchar();
			getchar();
			break;
		case 6:
			ltmp3 = BiTreesEmpty(BiTrees);
			if (ltmp3 == TRUE)
				printf("�ö���������Ϊ�գ�\n");
			else
				printf("�ö��������ϲ�Ϊ�գ�\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("�ö��������ϳ���Ϊ%d\n", BiTreesLength(BiTrees));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllBiTrees(BiTrees))
				printf("�ö�����������û��Ԫ�أ�\n");
			getchar();
			getchar();
			break;
		case 9:
			flag3 = 0;
			printf("��������Ҫ�����Ķ���������ţ�\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > BiTrees.length) {
				printf("�����������\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if (flag3 == 1)
				{
					op2=1;
					break;
				} //�����Ѿ������٣����˻�һ���˵�
				system("cls");
				printf("\n\n");
				printf("Menu for BiTree \n");
				printf("-------------------------------------------\n");
				printf("    1. CreateBiTree     2. ClearBiTree\n");
				printf("    3. BiTreeDepth      4. LocateNode\n");
				printf("    5. Assign           6. GetSibling \n");
				printf("    7. InsertNode       8. DeleteNode \n");
				printf("    9. Trabverse        10.SaveBiTree \n");
				printf("    11.DestroyBiTree    0. Exit\n");
				printf("-------------------------------------------\n");
				printf("��ѡ����Ĳ���[0~11]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("���س��˳���\n");
					break;
				case 1:
					k = 1;
					printf("��ѡ��ͨ�����̶Զ�������Ԫ�ظ�ֵ��1������ͨ�������ļ���ֵ��2����\n");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("��������Ҫ�����Ԫ�ظ�����\n");
						scanf("%d", &n);
						definition = (TElemType*)malloc(sizeof(TElemType) * n);
						p=definition;
						printf("����������(��������ֵΪ-1��������\n");
						for (i = 0; i < n+1; i++)
							scanf("%d%s", &definition[i].key, definition[i].others);
						CreateBiTree(BiTrees.elem[num].T, definition);
						printf("����ɹ�\n");
					}
					else
					{
						printf("�������ļ�����\n");
						scanf("%s", name);
						temp0 = LoadBiTree(BiTrees.elem[num].T, name);
						if (temp0 == ERROR) printf("����ʧ�ܣ�\n");
						else
							printf("����ɹ���\n");
					}
					getchar();
					getchar();
					break;
				case 2:
					tmp0 = ClearBiTree(BiTrees.elem[num].T);
					if (tmp0 == OK)
						printf("��������ճɹ���\n");
					getchar();
					getchar();
					break;
				case 3:
					tmp0 = BiTreeDepth(BiTrees.elem[num].T);
					printf("���������Ϊ%d\n", tmp0);
					getchar();
					getchar();
					break;
				case 4:
					printf("��������Ҫ���ҵ�Ԫ�ص���ֵ��\n");
					scanf("%d", &tmp1);
					temp = LocateNode(BiTrees.elem[num].T, tmp1);
					if (temp) printf("�ý������Ϊ%d %s\n",temp->data.key,temp->data.others);
					else printf("��������û�и�Ԫ��\n");
					getchar();
					getchar();
					break;
				case 5:
					printf("��������Ҫ��ֵ�Ľ�����ֵ��\n");
					scanf("%d", &flag2);
					printf("�������µ���ֵ�ʹ���\n");
					scanf("%d%s", &value.key, value.others);
					tmp2 = Assign(BiTrees.elem[num].T, flag2, value);
					if (tmp2 == ERROR) printf("��ֵʧ��\n");
					else printf("��ֵ�ɹ�\n");
					getchar();
					getchar();
					break;
				case 6:
					printf("��������Ҫ��ȡ���ֵܽ��Ľ����ֵ��\n");
					scanf("%d", &tmp3);
					temp = GetSibling(BiTrees.elem[num].T, tmp3);
					if (temp == NULL) printf("��ȡʧ��\n");
					else
						printf("�ֵܽ�������Ϊ��%d\t%s", temp->data.key, temp->data.others);
					getchar();
					getchar();
					break;
				case 7:
					printf("���������λ�õ����ݡ���ʽ�������������ֵ�ʹ�:\n");
					scanf("%d%d%d%s", &tmp4, &LR, &c.key, c.others);
					if (InsertNode(BiTrees.elem[num].T, tmp4, LR, c) == ERROR) printf("����ʧ��\n");
					else printf("����ɹ�\n");
					getchar();
					getchar();
					break;
				case 8:
					printf("��������Ҫɾ���Ľ�����ֵ��\n");
					scanf("%d", &elem2);
					if (DeleteNode(BiTrees.elem[num].T, elem2) == ERROR)
						printf("ɾ��ʧ��\n");
					else
						printf("ɾ���ɹ�\n");
					getchar();
					getchar();
					break;
				case 9:
					if(BiTrees.elem[num].T==NULL) 
						printf("��������û��Ԫ�أ�\n");
					else
					{
						printf("ǰ��\n");
						PreOrderTraverse(BiTrees.elem[num].T, &visit);
						printf("����\n");
						InOrderTraverse(BiTrees.elem[num].T, &visit);
						printf("����\n");
						PostOrderTraverse(BiTrees.elem[num].T, &visit);
						printf("����\n");
						LevelOrderTraverse(BiTrees.elem[num].T, &visit);
					}
					getchar();
					getchar();
					break;
				case 10:
					printf("�����봢�����ݵ��ļ���:\n");
					scanf("%s", name2);
					temp00 = SaveBiTree(BiTrees.elem[num].T, name2);
					if (temp00 == INFEASIBLE)
						printf("����δ��ʼ����\n");
					else if (temp00 == ERROR) printf("д��ʧ�ܣ�\n");
					else
						printf("д��ɹ���\n");
					getchar();
					getchar();
					break;
				case 11:
					flag3 = 0; //flag3���ã���������״̬
					ClearBiTree(BiTrees.elem[num].T);
					RemoveBiTree(&BiTrees, BiTrees.elem[num].name);
					printf("�������ٳɹ���\n");
					flag3 = 1;
					getchar();
					getchar();
					break;
				}
			}
			op2=1;
			if(flag3==0)
			{
				getchar();
				getchar();
				break;
			}
		}
	}
	return 0;
}

status judge(TElemType definition[])
{
	int i = 0, j = 0, judge[100] = { 0 };
	for (i = 0; definition[i].key != -1; i++)
		judge[definition[i].key]++;
	for (j = 1; j <= i; j++)
		if (judge[j] > 1) return ERROR;
	return OK;
}

status CreateBiTree(BiTree& T, TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (judge(definition) == ERROR) return ERROR;
	if ((*p).key == -1) return OK;
	else
	{
		if ((*p).key == 0)
			T = NULL;
		else {
			T = (BiTree)malloc(sizeof(BiTNode));
			T->lchild = NULL;
			T->rchild = NULL;
			T->data = *p;
			p++;
			if ((*p).key == -1) return OK;
			CreateBiTree(T->lchild, p);
			if ((*p).key == -1) return OK;
			p++;
			if ((*p).key == -1) return OK;
			CreateBiTree(T->rchild, p);
		}
	}
	/********** End **********/
}
status ClearBiTree(BiTree& T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (T == NULL) return OK;
	else
	{
		ClearBiTree(T->rchild);
		ClearBiTree(T->lchild);
		free(T);
		T = NULL;
		return OK;
	}

	/********** End **********/
}
int BiTreeDepth(BiTree T)
//�������T�����
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (T == NULL) return 0;
	else
	{
		int dept = 0;
		int ldept = BiTreeDepth(T->lchild);
		int rdept = BiTreeDepth(T->rchild);
		dept = ldept >= rdept ? (ldept + 1) : (rdept + 1);
		return dept;
	}

	/********** End **********/
}
BiTNode* LocateNode(BiTree T, KeyType e)
//���ҽ��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (T == NULL) return NULL;
	else
	{
		if (T->data.key == e) return T;
		else {
			temp1=LocateNode(T->lchild, e);
			if(temp1) return temp1;
			else
			{
            	temp1=LocateNode(T->rchild, e);
				if(temp1) return temp1;
				else return NULL;
			}
		}
	}

	/********** End **********/
}
status Assign(BiTree& T, KeyType e, TElemType value)
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	int temp;
	if (T == NULL) return ERROR;
	else
	{
		if (T->data.key == e)
		{
			if (e > value.key)
				return ERROR;
			T->data = value;
			return OK;
		}
		else
		{
			temp=Assign(T->lchild, e, value);
			if(temp) return OK;
			else
			{
				temp=Assign(T->rchild, e, value);
				if(temp) return OK;
				else return ERROR;
			}
		}
	}
	/********** End **********/
}
BiTNode* GetSibling(BiTree T, KeyType e)
//ʵ�ֻ���ֵܽ��
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (T == NULL) return NULL;
	else
	{
		if (!T->lchild || !T->rchild)
			return NULL;
		else if (T->lchild->data.key == e)
			return T->rchild;
		else if (T->rchild->data.key == e)
			return T->lchild;
		else
		{
			temp1=GetSibling(T->lchild, e);
			if(temp1) return temp1;
			else{
				temp1=GetSibling(T->rchild, e);
				if(temp1) return temp1;
				else return NULL;
			}
		}
	}
	/********** End **********/
}

status Traverse(BiTree T, KeyType e)
{
	int temp;
	if (T)
	{
		if (T->data.key == e) return OK;
		temp=Traverse(T->lchild, e);
		if(temp) return OK;
		else{
			temp=Traverse(T->rchild, e);
			if(temp) return OK;
		}
	}
}
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
{
	int temp;
	if (T == NULL) return ERROR;
	if (LR == -1 && Traverse(T, e))
	{
		BiTree m = (BiTree)malloc(sizeof(BiTNode));
		m->data = c;
		m->rchild = T;
		m->lchild = NULL;
		T = m;
		return OK;
	}
	else
	{
		if (c.key <= e) return ERROR;
		else if (LR == 0 && T->data.key == e)
		{
			BiTree m = (BiTree)malloc(sizeof(BiTNode));
			m->data = c;
			m->rchild = T->lchild;
			m->lchild = NULL;
			T->lchild = m;
			return OK;
		}
		else if (LR == 1 && T->data.key == e)
		{
			BiTree m = (BiTree)malloc(sizeof(BiTNode));
			m->data = c;
			m->rchild = T->rchild;
			m->lchild = NULL;
			T->rchild = m;
			return OK;
		}
		else
		{
			temp=InsertNode(T->lchild, e, LR, c);
			if(temp) return OK;
			else{
				temp=InsertNode(T->rchild, e, LR, c);
				if(temp) return OK;
				else return ERROR;
			}
		}
	}
}
BiTNode* GetFather(BiTree T, KeyType e)
//ʵ�ֻ�ø����
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	BiTree temp;
	if (T == NULL) return NULL;
	else
	{
		if ((T->lchild && T->lchild->data.key == e) || (T->rchild && T->rchild->data.key == e))
			return T;
		else
		{
			temp=GetFather(T->lchild, e);
			if(temp) return temp;
			else{
				temp=GetFather(T->rchild, e);
				if(temp) return temp;
				else return NULL;
			}
			
		}
	}
	/********** End **********/
}
BiTNode* Getlast(BiTree T)
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	while (T->rchild) T = T->rchild;
	return T;
	/********** End **********/
}
status DeleteNode(BiTree& T, KeyType e)
{
	if (T == NULL) return ERROR;
	if (T->data.key == e)
	{
		BiTree m = T;
		if (T->lchild && !T->rchild)
		{
			T = T->lchild;
			free(m);
			return OK;
		}
		if (T->rchild && !T->lchild)
		{
			T = T->rchild;
			free(m);
			return OK;
		}
		if (T->lchild && T->rchild)
		{
			BiTree n = Getlast(T->lchild);
			n->rchild = T->rchild;
			T = T->lchild;
			free(m);
			return OK;
		}
		if(!T->lchild&&!T->rchild)
		{
			free(T);
			T=NULL;
			return OK;
		}
	}
	BiTree m = GetFather(T, e);
	if (m == NULL) return ERROR;
	else
	{
		if (m->lchild&&m->lchild->data.key == e)
		{
			BiTree n = m->lchild;
			if (!n->lchild && !n->rchild)
			{
				free(n);
				n = NULL;
				m->lchild = NULL;
				return OK;
			}
			else if (n->lchild && !n->rchild)
			{
				m->lchild = n->lchild;
				free(n);
				n = NULL;
				return OK;
			}
			else if (n->rchild && !n->lchild)
			{
				m->lchild = n->rchild;
				free(n);
				n = NULL;
				return OK;
			}
			else
			{
				m->lchild = n->lchild;
				BiTree p = Getlast(n->lchild);
				p->rchild = n->rchild;
				free(n);
				n = NULL;
				return OK;
			}
		}
		if (m->rchild&&m->rchild->data.key == e)
		{
			BiTree n = m->rchild;
			if (!n->lchild && !n->rchild)
			{
				free(n);
				n = NULL;
				m->rchild = NULL;
				return OK;
			}
			else if (n->lchild && !n->rchild)
			{
				m->rchild = n->lchild;
				free(n);
				n = NULL;
				return OK;
			}
			else if (n->rchild && !n->lchild)
			{
				m->rchild = n->rchild;
				free(n);
				n = NULL;
				return OK;
			}
			else
			{
				m->rchild = n->lchild;
				BiTree p = Getlast(n->lchild);
				p->rchild = n->rchild;
				free(n);
				n = NULL;
				return OK;
			}
		}
	}
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
	if (T)
	{
		visit(T);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
		return OK;
	}
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
	BiTree pt[100];
	int top = 0;
	do
	{
		while (T)
		{
			pt[top++] = T;
			T = T->lchild;
		}
		if (top)
		{
			T = pt[--top];
			visit(T);
			T = T->rchild;
		}
	} while (top || T);
	return OK;
}
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
	if (T)
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T);
	}
	return OK;
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T
{
	BiTree pt[100];
	int in = 0, out = 0;
	pt[in++] = T;
	while (in > out)
	{
		if (pt[out])
		{
			visit(pt[out]);
			pt[in++] = pt[out]->lchild;
			pt[in++] = pt[out]->rchild;
		}
		out++;
	}
	return OK;
}
status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
	/********** Begin 1 *********/
	if (T == NULL) return INFEASIBLE;
	FILE* f = fopen(FileName, "w");
	if (f == NULL) return ERROR;
	BiTree BFS[100];
	int num[100];
	int top = 0;
	int bottom = 0;
	int top1 = 0;
	int bottom1 = 0;
	BFS[++top] = T;
	num[++top1] = 1;
	while (bottom != top)
	{
		int n = num[++bottom1];
		BiTree temp = BFS[++bottom];
		fprintf(f, "%d %d %s ", n, bottom, temp->data.others);
		if (temp->lchild)
		{
			num[++top1] = n * 2;
			BFS[++top] = temp->lchild;
		}
		if (temp->rchild)
		{
			num[++top1] = n * 2 + 1;
			BFS[++top] = temp->rchild;
		}
	}
	fprintf(f, "0 0 null");
	fclose(f);
	return OK;
	/********** End 1 **********/
}
status LoadBiTree(BiTree& T, char FileName[])
{
	BiTree pt[100];
	int n, key;
	char str[100];
	FILE* fp;
	if ((fp = fopen(FileName, "rb")) == NULL)
		return ERROR;
	fscanf(fp, "%d%d%s", &n, &key, str);
	while (n)
	{
		BiTree p = (BiTree)malloc(sizeof(BiTNode));
		p->lchild = NULL;
		p->rchild = NULL;
		p->data.key = key;
		strcpy(p->data.others, str);
		pt[n] = p;
		if (n == 1) T = p;
		else
		{
			if (!(n % 2)) pt[n / 2]->lchild = p;
			else pt[n / 2]->rchild = p;
		}
		fscanf(fp, "%d%d%s", &n, &key, str);
	}
	fclose(fp);
	return OK;
}
status AddBiTree(BITREES* BiTrees, char BiTreeName[])
// ֻ��Ҫ��BiTrees������һ������ΪBiTreeName�Ŀն������������������ɺ�̨���Գ�����롣
{
	strcpy(BiTrees->elem[BiTrees->length].name, BiTreeName);
	BiTrees->elem[BiTrees->length].T = NULL;
	BiTrees->length++;
	return OK;
}

status RemoveBiTree(BITREES* BiTrees, char BiTreeName[])
// BiTrees��ɾ��һ������ΪBiTreeName�Ķ�����
{
	int  i, k;
	for (i = 0; i < BiTrees->length; i++) {
		if (strcmp(BiTrees->elem[i].name, BiTreeName))
			continue;
		else {
			BiTrees->elem[i].name[0] = '\0';
			free(BiTrees->elem[i].T);
			BiTrees->elem[i].T = NULL;
			for (k = i; k < BiTrees->length; k++)
				BiTrees->elem[k] = BiTrees->elem[k + 1];
			BiTrees->length--;
			return OK;
		}
	}
	return ERROR;
}

status LocateBiTree(BITREES BiTrees, char BiTreeName[])
// ��BiTrees�в���һ������ΪBiTreeName�Ķ��������ɹ������߼���ţ����򷵻�0
{
	int i;
	for (i = 0; i < BiTrees.length; i++) {
		if (strcmp(BiTrees.elem[i].name, BiTreeName))
			continue;
		else
			return i + 1;
	}
	return ERROR;
}

status ClearBiTrees(BITREES* BiTrees) {
	//��ն���������
	BiTrees->length = 0;
	return OK;
}

status BiTreesEmpty(BITREES BiTrees) {
	//�ж϶����������Ƿ�Ϊ��
	if (BiTrees.length == 0)
		return TRUE;
	else
		return FALSE;
}

status BiTreesLength(BITREES BiTrees) {
	//����������ϵĳ���
	return BiTrees.length;
}

status PrintAllBiTrees(BITREES BiTrees) {
	//��ӡ�����������е�����Ԫ��
	if (BiTrees.length == 0) return ERROR;
	else {
		printf("���ж���������Ϊ:\n");
		for (int i = 0; i < BiTrees.length; i++) {
			printf("%d\t%s\n", i + 1, BiTrees.elem[i].name);
		}
	}
	return OK;
}

status InitBiTrees(BITREES* BiTrees) {
	//��ʼ������������
	BiTrees->length = 0;
	return OK;
}
void visit(BiTree T)
{
	printf("%d\t%s\n", T->data.key, T->data.others);
}
