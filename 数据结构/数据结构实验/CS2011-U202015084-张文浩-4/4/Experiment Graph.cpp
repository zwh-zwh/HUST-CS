#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
	int adjvex;              //����λ�ñ��
	struct ArcNode *nextarc;       //��һ������ָ��
} ArcNode;
typedef struct VNode {                //ͷ��㼰���������Ͷ���
	VertexType data;           //������Ϣ
	ArcNode *firstarc;           //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
	AdjList vertices;          //ͷ�������
	int vexnum;
	int arcnum;         //������������
	GraphKind  kind;        //ͼ������
} ALGraph;
typedef struct { //ͼ�ļ������Ͷ���
	struct {
		char name[30]; //ͼ����
		ALGraph G; //ͼ
	} elem[10]; //ͼ����
	int length; //ͼ���ϳ���
}ALGraphs;
typedef struct{
	int queue[MAX_VERTEX_NUM];
	int front;
	int tail;
}Queue;
int visited[MAX_VERTEX_NUM]={0};
void (*Visit)(VertexType); 
void initqueue(Queue &Q);
int queueempty(Queue Q);
void inqueue(Queue &Q,int v);
int dequeue(Queue &Q,int e);
status Judge(int a[], int n);
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
void print(ALGraph G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void visit(VertexType v);
void DFS(ALGraph &G,int v);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status AddALGraph(ALGraphs* ALGraphs, char ALGraphName[]);
status RemoveALGraph(ALGraphs* ALGraphs, char ALGraphName[]);
status LocateALGraph(ALGraphs ALGraphs, char ALGraphName[]);
status ClearALGraphs(ALGraphs* ALGraphs);
status ALGraphsEmpty(ALGraphs ALGraphs);
status ALGraphsLength(ALGraphs ALGraphs);
status PrintAllALGraphs(ALGraphs ALGraphs);
status InitALGraphs(ALGraphs* ALGraphs);
void printall(ALGraph G);
int main() {
	ALGraphs ALGraphs;
	VertexType value,c,a[100];
	KeyType b[100][2];
	char ALGraphName1[100], ALGraphName2[100], ALGraphName3[100], name[100], name2[100];
	int op1 = 1, op2 = 1, n, k = 1, choice, i, j, flag = 0, flag2 = 0,flag3=0, e, LR;
	int ltmp1, ltmp2, ltmp3;
	int num1, num;
	int tmp1, tmp2, tmp3, tmp4, tmp0, temp0, temp00, elem2,temp;
	int v,w;
	while (op1) {
		system("cls");
		printf("\n\n");
		printf("Menu for ALgraph \n");
		printf("-------------------------------------------\n");
		printf("    1.InitALgraphs       2.AddALgraph\n");
		printf("    3.RemoveALgraph      4.LocateALgraph\n");
		printf("    5.ClearALgraphs      6.ALgraphsEmpty\n");
		printf("    7.ALgraphsLength     8.PrintAllALgraphs\n");
		printf("    9.OperateALgraph     0.Exit\n");
		printf("-------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~9]:");
		scanf("%d", &op1);
		switch (op1) {
		case 0:
			break;
		case 1:
			InitALGraphs(&ALGraphs);
			printf("��ʼ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("��������Ҫ��ӵ�ͼ�����ƣ�\n");
			do
			{
				flag = 0;
				scanf("%s", ALGraphName1);
				for (j = 0; j < ALGraphs.length; j++)
					if (!strcmp(ALGraphName1, ALGraphs.elem[j].name)) //���Ҽ������Ƿ������ָø����Ƶ�ͼ
					{
						flag = 1;
						printf("�����ظ������������룡\n");
						break;
					}
			} while (flag == 1);
			AddALGraph(&ALGraphs, ALGraphName1);
			printf("��ӳɹ���\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("��������Ҫɾ����ͼ�����ƣ�\n");
			scanf("%s", ALGraphName2);

			ltmp1 = RemoveALGraph(&ALGraphs, ALGraphName2);
			if (ltmp1 == ERROR)
				printf("ͼ������û�и�ͼ��\n");
			else
				printf("ɾ���ɹ���\n");
			getchar();
			getchar();
			break;
		case 4:

			printf("��������Ҫ��λ��ͼ�����ƣ�\n");
			scanf("%s", ALGraphName3);

			ltmp2 = LocateALGraph(ALGraphs, ALGraphName3);
			if (ltmp2 == ERROR)
				printf("ͼ������û�и�ͼ��\n");
			else
				printf("��ͼ��λ��Ϊ%d\n", LocateALGraph(ALGraphs, ALGraphName3));
			getchar();
			getchar();
			break;
		case 5:
			ClearALGraphs(&ALGraphs);
			printf("��ճɹ���\n");
			getchar();
			getchar();
			break;
		case 6:
			ltmp3 = ALGraphsEmpty(ALGraphs);
			if (ltmp3 == TRUE)
				printf("��ͼ����Ϊ�գ�\n");
			else
				printf("��ͼ���ϲ�Ϊ�գ�\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("��ͼ���ϳ���Ϊ%d\n", ALGraphsLength(ALGraphs));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllALGraphs(ALGraphs))
				printf("��ͼ������û��Ԫ�أ�\n");
			getchar();
			getchar();
			break;
		case 9:
			flag3 = 0;
			printf("��������Ҫ������ͼ����ţ�\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > ALGraphs.length) {
				printf("�����������\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if (flag3 == 1)
				{
					op2=1;
					break;
				} //ͼ�Ѿ������٣����˻�һ���˵�
				system("cls");
				printf("\n\n");
				printf("Menu for ALgraph \n");
				printf("-------------------------------------------\n");
				printf("    1. CreateALgraph    2. DestroyALgraph\n");
				printf("    3. LocateVex        4. PutVex\n");
				printf("    5. FirstAdjVex      6. NextAdjVex \n");
				printf("    7. InsertVex        8. DeleteVex \n");
				printf("    9. InsertArc        10.DeleteArc \n");
				printf("    11.printall         12.DFS&BFS\n");
				printf("    13.SaveGraph        0.Exit \n");
				printf("-------------------------------------------\n");
				printf("��ѡ����Ĳ���[0~13]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("���س��˳���\n");
					break;
				case 1:
					k = 1;
					printf("��ѡ��ͨ�����̶�ͼ��Ԫ�ظ�ֵ��1������ͨ�������ļ���ֵ��2����\n");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("����������(��������ֵΪ-1��������\n");
						for (i = 0; i < n+1; i++)
						CreateGraph(ALGraphs.elem[num].G,a,b);
						printf("����ɹ�\n");
					}
					else
					{
						printf("�������ļ�����\n");
						scanf("%s", name);
						temp0 = LoadGraph(ALGraphs.elem[num].G, name);
						if (temp0 == ERROR) printf("����ʧ�ܣ�\n");
						else
							printf("����ɹ���\n");
					}
					getchar();
					getchar();
					break;
				case 2:
					flag3=0;
					tmp0 = DestroyGraph(ALGraphs.elem[num].G);
					RemoveALGraph(&ALGraphs,ALGraphs.elem[num].name);
					if (tmp0 == OK)
						printf("ͼ���ٳɹ���\n");
					flag3=1;
					getchar();
					getchar();
					break;
				case 3:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫ���ҵ�Ԫ�ص���ֵ��\n");
					scanf("%d", &tmp1);
					temp = LocateVex(ALGraphs.elem[num].G, tmp1);
					if (temp!=-1) 
						printf("�ý��λ��Ϊ%d,�ý������Ϊ %d %s\n",temp,ALGraphs.elem[num].G.vertices[temp].data.key,ALGraphs.elem[num].G.vertices[temp].data.others);
					else printf("ͼ��û�и�Ԫ��\n");
					getchar();
					getchar();
					break;
				case 4:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫ��ֵ�Ľ�����ֵ��\n");
					scanf("%d", &flag2);
					printf("�������µ���ֵ�ʹ���\n");
					scanf("%d%s", &value.key, value.others);
					tmp2 = PutVex(ALGraphs.elem[num].G, flag2, value);
					if (tmp2 == ERROR) printf("��ֵʧ��\n");
					else printf("��ֵ�ɹ�\n");
					getchar();
					getchar();
					break;
				case 5:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫ��ȡ���һ�ڽӽ��Ľ����ֵ��\n");
					scanf("%d", &tmp3);
					temp =FirstAdjVex(ALGraphs.elem[num].G, tmp3);
					if (temp==-1) printf("��ȡʧ��\n");
					else
						printf("�ý��λ��Ϊ%d,�ý������Ϊ %d %s\n",temp,ALGraphs.elem[num].G.vertices[temp].data.key,ALGraphs.elem[num].G.vertices[temp].data.others);
					getchar();
					getchar();
					break;
				case 6:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҷ������Զ��㣺\n");
					scanf("%d%d",&v,&w);
					temp0=NextAdjVex(ALGraphs.elem[num].G,v,w);
					if (temp0==-1) printf("��ȡʧ��\n");
					else
						printf("�ý��λ��Ϊ%d,�ý������Ϊ %d %s\n",temp0,ALGraphs.elem[num].G.vertices[temp0].data.key,ALGraphs.elem[num].G.vertices[temp0].data.others);
					getchar();
					getchar();
					break;
				case 7:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("����������������ֵ�ʹ�:\n");
					scanf("%d%s",&c.key, c.others);
					if (InsertVex(ALGraphs.elem[num].G,c) == ERROR) printf("����ʧ��\n");
					else printf("����ɹ�\n");
					getchar();
					getchar();
					break;
				case 8:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫɾ���Ľ�����ֵ��\n");
					scanf("%d", &elem2);
					if (DeleteVex(ALGraphs.elem[num].G, elem2) == ERROR)
						printf("ɾ��ʧ��\n");
					else
						printf("ɾ���ɹ�\n");
					getchar();
					getchar();
					break;
				case 9:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫ���ӵĻ����������㣺\n");
					scanf("%d%d",&v,&w);
					temp=InsertArc(ALGraphs.elem[num].G,v,w);
					if(temp==ERROR) printf("����ʧ��\n");
					else printf("����ɹ�\n");
					getchar();
					getchar();
					break;
				case 10:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ҫɾ���Ļ����������㣺\n");
					scanf("%d%d",&v,&w);
					temp=DeleteArc(ALGraphs.elem[num].G,v,w);
					if(temp==ERROR) printf("ɾ��ʧ��\n");
					else printf("ɾ���ɹ�\n");
					getchar();
					getchar();
					break;
				case 11:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("��������Ϊ��\n");
					printall(ALGraphs.elem[num].G);
					getchar();
					getchar();
					break;
				case 12:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("�������������\n");
					DFSTraverse(ALGraphs.elem[num].G,visit);
					printf("�������������\n");
					BFSTraverse(ALGraphs.elem[num].G,visit);
					getchar();
					getchar();
					break;
				case 13:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("ͼΪ�գ�\n");
						getchar();
						getchar();
						break;
					}
					printf("�����봢�����ݵ��ļ���:\n");
					scanf("%s", name2);
					temp00 = SaveGraph(ALGraphs.elem[num].G, name2);
					if (temp00 == ERROR) printf("д��ʧ�ܣ�\n");
					else
						printf("д��ɹ���\n");
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
void initqueue(Queue &Q)
{
	Q.front=0;
	Q.tail=-1;
	memset(Q.queue,0,sizeof(Q.queue));
}
int queueempty(Queue Q)
{
	if(Q.tail==-1)
		return 0;
	return 1;
}
void inqueue(Queue &Q,int v)
{
	Q.queue[++Q.tail]=v;
}
int dequeue(Queue &Q,int e)
{
	e=Q.queue[Q.front];
	for(int i=0;i<Q.tail;i++)
	{
		Q.queue[i]=Q.queue[i+1];
	}
	Q.tail--;
	return e;
}
status Judge(int a[], int n) {
	int judge[100] = { 0 };
	for (int i = 0; i < n; i++)
		judge[a[i]]++;
	for (int j = 0; j < n; j++)
		if (judge[j] > 1)
			return ERROR;
	return OK;
}
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
	int key[100], k = 0, cnt = 0, m = 0,l=0, i, j;
	ArcNode *p,*q;
	G.kind = UDG;
	G.arcnum = 0;
	G.vexnum = 0;
	scanf("%d%s", &V[l].key, V[l].others);
    if(V[l].key==-1) return ERROR;
	while (V[l].key != -1) {
		key[k] = V[l].key;
		if (Judge(key, k) == ERROR)
			return ERROR;
        k++;
		G.vertices[cnt].data.key = V[l].key;
		strcpy(G.vertices[cnt].data.others, V[l].others);
		G.vertices[cnt].firstarc = NULL;
        cnt++;
		G.vexnum++;
        l++;
		scanf("%d%s", &V[l].key, V[l].others);
	}
    if(G.vexnum>20) return ERROR;
	scanf("%d%d", &VR[m][0], &VR[m][1]);
	while (VR[m][0] != -1) {
		p = (ArcNode *)malloc(sizeof(ArcNode));
        q = (ArcNode *)malloc(sizeof(ArcNode));
		for (i = 0; i < G.vexnum; i++)
			if (G.vertices[i].data.key == VR[m][1])
				break;
        if(i==G.vexnum) return ERROR;
		for (j = 0; j < G.vexnum; j++)
			if (G.vertices[j].data.key == VR[m][0])
				break;
        if(j==G.vexnum) return ERROR;
		p->adjvex = i;
        q->adjvex = j;
		p->nextarc = G.vertices[j].firstarc;
        q->nextarc = G.vertices[i].firstarc;
		G.vertices[j].firstarc = p;
        G.vertices[i].firstarc = q;
		G.arcnum++;
		m++;
        scanf("%d%d", &VR[m][0], &VR[m][1]);
	}
    return OK;
}
status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
	ArcNode *p,*q;
	for(int i=0;i<G.vexnum;i++)
	{
        if(G.vertices[i].firstarc==NULL)
            continue;
		p=G.vertices[i].firstarc->nextarc;
		q=G.vertices[i].firstarc;
		while(p){
			q=p->nextarc;
			free(p);
			p=q;
		}
		p=G.vertices[i].firstarc;
		free(p);
		G.vertices[i].firstarc=NULL;
	}
	G.arcnum=0;
	G.vexnum=0;
	return OK;
}
void print(ALGraph G)
{
	for(int i=0;i<G.vexnum;i++)
	{
		ArcNode *p=G.vertices[i].firstarc;
		printf("%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
		while(p)
		{
			printf("%d ",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}
int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.key==u)
			return i;
	return -1;
    /********** End **********/
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int flag[20]={0};
	flag[value.key]++;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[u]==0||flag[value.key]==2&&value.key!=u) 
		return ERROR;
	for(int i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.key==u)
		{
			G.vertices[i].data=value;
			return OK;
		}

    /********** End **********/
}
int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data.key==u)
		{
			if(G.vertices[i].firstarc==NULL)
				return -1;
			return G.vertices[i].firstarc->adjvex;
		}
	}
	return -1;
    /********** End **********/
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int flag[20]={0},k=0;
	for(int i=0;i<G.vexnum;i++)
	{
		flag[G.vertices[i].data.key]++;
		if(G.vertices[i].data.key==w)
			k=i;
	}
	if(flag[v]==0) 
		return -1;
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data.key==v)
		{
			ArcNode *p=G.vertices[i].firstarc;
			while(p)
			{
				if(p->adjvex==k)
				{
					if(p->nextarc==NULL) return -1;
					else return p->nextarc->adjvex;
				}
				p=p->nextarc;
			}
			return -1;
		}
	}  
	/********** End **********/
}
status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int flag[20]={0};
	flag[v.key]++;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[v.key]==2||G.vexnum+1>20) 
		return ERROR;
	G.vertices[G.vexnum].data.key=v.key;
	strcpy(G.vertices[G.vexnum].data.others,v.others);
	G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
	return OK;
    /********** End **********/
}
status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(G.vexnum==1&&v==G.vertices[0].data.key) return ERROR;
	int flag[20]={0},i;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[v]==0) 
		return ERROR;
	ArcNode *p,*q;
	for(i=0;i<G.vexnum;i++) //ɾ�����
	{
		if(G.vertices[i].data.key==v)
		{
			if(G.vertices[i].firstarc==NULL)
				break;
			p=G.vertices[i].firstarc->nextarc;
			q=G.vertices[i].firstarc;
			while(p){
				q=p->nextarc;
				free(p);
				p=q;
				G.arcnum--;
			}
			p=G.vertices[i].firstarc;
			free(p);
            G.arcnum--;
			G.vertices[i].firstarc=NULL;
			break;
		}
	}
	for(int j=i+1;j<G.vexnum;j++) //����ڵ�ǰ��
	{
		G.vertices[j-1].data.key=G.vertices[j].data.key;
		strcpy(G.vertices[j-1].data.others,G.vertices[j].data.others);
		G.vertices[j-1].firstarc=G.vertices[j].firstarc;
	}
	G.vexnum--;
	for(int k=0;k<G.vexnum;k++)
	{
		if(G.vertices[k].firstarc==NULL) continue;
		ArcNode *p=G.vertices[k].firstarc,*r=G.vertices[k].firstarc,*q=p->nextarc;
		if(p->adjvex==i)
		{
			G.vertices[k].firstarc=q;
			free(p);
			continue;
		}
		p=G.vertices[k].firstarc->nextarc;
		while(p)
		{
			if(p->adjvex==i)
			{
				r->nextarc=p->nextarc;
				free(p);
				break;
			}
			p=p->nextarc;
			r=r->nextarc;
		}
	}
	for(int l=0;l<G.vexnum;l++)
	{
		ArcNode *p=G.vertices[l].firstarc;
		while(p)
		{
			if(p->adjvex>i) p->adjvex--;
			p=p->nextarc;
		}
	}
	return OK;
    /********** End **********/
}
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int flag[20]={0},i,j;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[v]==0||flag[w]==0) 
		return ERROR;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			break;
	for (j = 0; j < G.vexnum; j++)
		if (G.vertices[j].data.key == w)	
			break;
	ArcNode *p=G.vertices[i].firstarc;
	while(p)
	{
		if(p->adjvex==j) return ERROR;
		p=p->nextarc;
	}
    p=(ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex=j;
	p->nextarc=G.vertices[i].firstarc;
	G.vertices[i].firstarc=p;
	ArcNode *q=(ArcNode *)malloc(sizeof(ArcNode));
	q->adjvex=i;
	q->nextarc=G.vertices[j].firstarc;
	G.vertices[j].firstarc=q;
	return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int flag[20]={0},i,j,tag=0;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[v]==0||flag[w]==0) 
		return ERROR;
	for (i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == v)
			break;
	for (j = 0; j < G.vexnum; j++)
		if (G.vertices[j].data.key == w)	
			break;
	ArcNode *m=G.vertices[i].firstarc;
	while(m)
	{
		if(m->adjvex==j)
		{
			tag=1;
			break;
		}
		m=m->nextarc;
	}
	if(tag==0) return ERROR;
	ArcNode *p=G.vertices[i].firstarc,*r=G.vertices[i].firstarc,*q=p->nextarc;
	if(p->adjvex==j)
	{
		G.vertices[i].firstarc=q;
		free(p);
		p=NULL;
	}
	else
	{
		p=G.vertices[i].firstarc->nextarc;
		while(p)
		{
			if(p->adjvex==j)
			{
				r->nextarc=p->nextarc;
				free(p);
				p=NULL;
				break;
			}
			p=p->nextarc;
			r=r->nextarc;
		}
	}
	p=G.vertices[j].firstarc,r=G.vertices[j].firstarc,q=p->nextarc;
	if(p->adjvex==i)
	{
		G.vertices[j].firstarc=q;
		free(p);
		p=NULL;
	}
	else
	{
		p=G.vertices[j].firstarc->nextarc;
		while(p)
		{
			if(p->adjvex==i)
			{
				r->nextarc=p->nextarc;
				free(p);
				p=NULL;
				break;
			}
			p=p->nextarc;
			r=r->nextarc;
		}
	}
	G.arcnum--;
	return OK;
}


void visit(VertexType v)
{
	printf("%d %s\n",v.key,v.others);
}
void DFS(ALGraph &G,int v)
{
	visited[v]=1;
	Visit(G.vertices[v].data);
	for(int w=FirstAdjVex(G,G.vertices[v].data.key);w>=0;w=NextAdjVex(G,G.vertices[v].data.key,G.vertices[w].data.key))
	{
		if(!visited[w])
			DFS(G,w);
	}
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	Visit=visit;
	for(int v=0;v<G.vexnum;v++)
	{
		if(!visited[v])
			DFS(G,v);
	}
	memset(visited,0,sizeof(visited));
	return OK;
    /********** End **********/
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	Visit=visit;
	Queue Q;
	initqueue(Q);
	for(int v=0;v<G.vexnum;v++)
	{
		if(!visited[v])
		{
			visited[v]=1;
			Visit(G.vertices[v].data);
			inqueue(Q,v);
			while(queueempty(Q))
			{
				int e;
				e=dequeue(Q,e);
				for(int w=FirstAdjVex(G,G.vertices[e].data.key);w>=0;w=NextAdjVex(G,G.vertices[e].data.key,G.vertices[w].data.key))
				{
					if(!visited[w])
					{
						visited[w]=1;
						Visit(G.vertices[w].data);
						inqueue(Q,w);
					}
				}
			}
		}
	}
	memset(visited,0,sizeof(visited));
	return 0;
    /********** End **********/
}
status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
	FILE *fp;
	if((fp=fopen(FileName,"w"))==NULL)
		return ERROR;
	for(int v=0;v<G.vexnum;v++)
	{
		fprintf(fp,"%d %s ",G.vertices[v].data.key,G.vertices[v].data.others);
	}
	fprintf(fp,"-1 nil ");
	for(int v=0;v<G.vexnum;v++)
	{
		ArcNode *p=G.vertices[v].firstarc;
		while(p)
		{
			fprintf(fp,"%d %d ",G.vertices[v].data.key,G.vertices[p->adjvex].data.key);
			p=p->nextarc;
		}
	}
	fprintf(fp,"-1 -1 ");
	fprintf(fp,"%d ",G.arcnum);
	fclose(fp);
	return OK;
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    ArcNode *p,*q;
	G.kind = UDG;
	G.arcnum = 0;
	G.vexnum = 0;
	FILE *fp;
	if((fp=fopen(FileName,"r"))==NULL)
		return ERROR;
	int key=0;
	char others[100];
	int cnt=0;		
	fscanf(fp,"%d%s",&key,others);
	while(key!=-1)
	{
		G.vertices[cnt].data.key=key;
		strcpy(G.vertices[cnt].data.others,others);
		G.vertices[cnt].firstarc = NULL;
		cnt++;
		G.vexnum++;
		fscanf(fp,"%d%s",&key,others);
	}
	int m,n,i,j;
	fscanf(fp,"%d%d",&m,&n);
	while (m!= -1) {
		p = (ArcNode *)malloc(sizeof(ArcNode));
		for (i = 0; i < G.vexnum; i++)
			if (G.vertices[i].data.key == n)
				break;
		for (j = 0; j < G.vexnum; j++)
			if (G.vertices[j].data.key == m)
				break;
		ArcNode *p1=G.vertices[j].firstarc;
		while(p1&&p1->nextarc)
			p1=p1->nextarc;
		p->adjvex = i;
		p->nextarc = NULL;
		if(!p1) G.vertices[j].firstarc=p;
		else p1->nextarc = p;
        fscanf(fp,"%d%d",&m,&n);
	}
	fscanf(fp,"%d",&G.arcnum);
	fclose(fp);
	return OK;
    /********** End 2 **********/
}
status AddALGraph(ALGraphs* ALGraphs, char ALGraphName[])
// ֻ��Ҫ��ALGraphs������һ������ΪALGraphName�Ŀ�ͼ��ͼ�����ɺ�̨���Գ�����롣
{
	ALGraphs->elem[ALGraphs->length].G.kind = UDG;
	ALGraphs->elem[ALGraphs->length].G.arcnum = 0;
	ALGraphs->elem[ALGraphs->length].G.vexnum = 0;
	strcpy(ALGraphs->elem[ALGraphs->length].name, ALGraphName);
	ALGraphs->length++;
	return OK;
}

status RemoveALGraph(ALGraphs* ALGraphs, char ALGraphName[])
// ALGraphs��ɾ��һ������ΪALGraphName��ͼ
{
	int  i, k;
	for (i = 0; i < ALGraphs->length; i++) {
		if (strcmp(ALGraphs->elem[i].name, ALGraphName))
			continue;
		else {
			ALGraphs->elem[i].name[0] = '\0';
			for (k = i; k < ALGraphs->length; k++)
				ALGraphs->elem[k] = ALGraphs->elem[k + 1];
			ALGraphs->length--;
			return OK;
		}
	}
	return ERROR;
}

status LocateALGraph(ALGraphs ALGraphs, char ALGraphName[])
// ��ALGraphs�в���һ������ΪALGraphName��ͼ���ɹ������߼���ţ����򷵻�0
{
	int i;
	for (i = 0; i < ALGraphs.length; i++) {
		if (strcmp(ALGraphs.elem[i].name, ALGraphName))
			continue;
		else
			return i + 1;
	}
	return ERROR;
}

status ClearALGraphs(ALGraphs* ALGraphs) {
	//���ͼ����
	ALGraphs->length = 0;
	return OK;
}

status ALGraphsEmpty(ALGraphs ALGraphs) {
	//�ж�ͼ�����Ƿ�Ϊ��
	if (ALGraphs.length == 0)
		return TRUE;
	else
		return FALSE;
}

status ALGraphsLength(ALGraphs ALGraphs) {
	//��ͼ���ϵĳ���
	return ALGraphs.length;
}

status PrintAllALGraphs(ALGraphs ALGraphs) {
	//��ӡͼ�����е�����Ԫ��
	if (ALGraphs.length == 0) return ERROR;
	else {
		printf("����ͼ����Ϊ:\n");
		for (int i = 0; i < ALGraphs.length; i++) {
			printf("%d\t%s\n", i + 1, ALGraphs.elem[i].name);
		}
	}
	return OK;
}

status InitALGraphs(ALGraphs* ALGraphs) {
	//��ʼ��ͼ����
	ALGraphs->length = 0;
	return OK;
}
void printall(ALGraph G)
{

	for(int i=0;i<G.vexnum;i++)
	{
		printf("%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
		ArcNode *p=G.vertices[i].firstarc;
		while(p)
		{
			printf("%d ",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}