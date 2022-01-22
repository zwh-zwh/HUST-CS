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
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
	int adjvex;              //顶点位置编号
	struct ArcNode *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode {                //头结点及其数组类型定义
	VertexType data;           //顶点信息
	ArcNode *firstarc;           //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;          //头结点数组
	int vexnum;
	int arcnum;         //顶点数、弧数
	GraphKind  kind;        //图的类型
} ALGraph;
typedef struct { //图的集合类型定义
	struct {
		char name[30]; //图名称
		ALGraph G; //图
	} elem[10]; //图数组
	int length; //图集合长度
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
		printf("请选择你的操作[0~9]:");
		scanf("%d", &op1);
		switch (op1) {
		case 0:
			break;
		case 1:
			InitALGraphs(&ALGraphs);
			printf("初始化成功！\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("请输入需要添加的图的名称：\n");
			do
			{
				flag = 0;
				scanf("%s", ALGraphName1);
				for (j = 0; j < ALGraphs.length; j++)
					if (!strcmp(ALGraphName1, ALGraphs.elem[j].name)) //查找集合中是否早已又该该名称的图
					{
						flag = 1;
						printf("名称重复！请重新输入！\n");
						break;
					}
			} while (flag == 1);
			AddALGraph(&ALGraphs, ALGraphName1);
			printf("添加成功！\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("请输入需要删除的图的名称：\n");
			scanf("%s", ALGraphName2);

			ltmp1 = RemoveALGraph(&ALGraphs, ALGraphName2);
			if (ltmp1 == ERROR)
				printf("图集合中没有该图！\n");
			else
				printf("删除成功！\n");
			getchar();
			getchar();
			break;
		case 4:

			printf("请输入需要定位的图的名称：\n");
			scanf("%s", ALGraphName3);

			ltmp2 = LocateALGraph(ALGraphs, ALGraphName3);
			if (ltmp2 == ERROR)
				printf("图集合中没有该图！\n");
			else
				printf("该图的位置为%d\n", LocateALGraph(ALGraphs, ALGraphName3));
			getchar();
			getchar();
			break;
		case 5:
			ClearALGraphs(&ALGraphs);
			printf("清空成功！\n");
			getchar();
			getchar();
			break;
		case 6:
			ltmp3 = ALGraphsEmpty(ALGraphs);
			if (ltmp3 == TRUE)
				printf("该图集合为空！\n");
			else
				printf("该图集合不为空！\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("该图集合长度为%d\n", ALGraphsLength(ALGraphs));
			getchar();
			getchar();
			break;
		case 8:
			if (!PrintAllALGraphs(ALGraphs))
				printf("该图集合中没有元素！\n");
			getchar();
			getchar();
			break;
		case 9:
			flag3 = 0;
			printf("请输入需要操作的图的序号：\n");
			scanf("%d", &num1);
			num = num1 - 1;
			while (num1 < 1 || num1 > ALGraphs.length) {
				printf("输入序号有误！\n");
				scanf("%d", &num1);
			}
			while (op2) {
				if (flag3 == 1)
				{
					op2=1;
					break;
				} //图已经被销毁，就退回一级菜单
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
				printf("请选择你的操作[0~13]:");
				scanf("%d", &op2);
				switch (op2) {
				case 0:
					printf("按回车退出！\n");
					break;
				case 1:
					k = 1;
					printf("请选择通过键盘对图中元素赋值（1）或者通过读入文件赋值（2）：\n");
					scanf("%d", &choice);
					if (choice == 1)
					{
						printf("请输入数据(输入结点数值为-1结束）：\n");
						for (i = 0; i < n+1; i++)
						CreateGraph(ALGraphs.elem[num].G,a,b);
						printf("输入成功\n");
					}
					else
					{
						printf("请输入文件名：\n");
						scanf("%s", name);
						temp0 = LoadGraph(ALGraphs.elem[num].G, name);
						if (temp0 == ERROR) printf("读入失败！\n");
						else
							printf("读入成功！\n");
					}
					getchar();
					getchar();
					break;
				case 2:
					flag3=0;
					tmp0 = DestroyGraph(ALGraphs.elem[num].G);
					RemoveALGraph(&ALGraphs,ALGraphs.elem[num].name);
					if (tmp0 == OK)
						printf("图销毁成功！\n");
					flag3=1;
					getchar();
					getchar();
					break;
				case 3:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要查找的元素的数值：\n");
					scanf("%d", &tmp1);
					temp = LocateVex(ALGraphs.elem[num].G, tmp1);
					if (temp!=-1) 
						printf("该结点位序为%d,该结点数据为 %d %s\n",temp,ALGraphs.elem[num].G.vertices[temp].data.key,ALGraphs.elem[num].G.vertices[temp].data.others);
					else printf("图中没有该元素\n");
					getchar();
					getchar();
					break;
				case 4:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要赋值的结点的数值：\n");
					scanf("%d", &flag2);
					printf("请输入新的数值和串：\n");
					scanf("%d%s", &value.key, value.others);
					tmp2 = PutVex(ALGraphs.elem[num].G, flag2, value);
					if (tmp2 == ERROR) printf("赋值失败\n");
					else printf("赋值成功\n");
					getchar();
					getchar();
					break;
				case 5:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要获取其第一邻接结点的结点数值：\n");
					scanf("%d", &tmp3);
					temp =FirstAdjVex(ALGraphs.elem[num].G, tmp3);
					if (temp==-1) printf("获取失败\n");
					else
						printf("该结点位序为%d,该结点数据为 %d %s\n",temp,ALGraphs.elem[num].G.vertices[temp].data.key,ALGraphs.elem[num].G.vertices[temp].data.others);
					getchar();
					getchar();
					break;
				case 6:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入查找顶点和相对顶点：\n");
					scanf("%d%d",&v,&w);
					temp0=NextAdjVex(ALGraphs.elem[num].G,v,w);
					if (temp0==-1) printf("获取失败\n");
					else
						printf("该结点位序为%d,该结点数据为 %d %s\n",temp0,ALGraphs.elem[num].G.vertices[temp0].data.key,ALGraphs.elem[num].G.vertices[temp0].data.others);
					getchar();
					getchar();
					break;
				case 7:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入待插入结点的数值和串:\n");
					scanf("%d%s",&c.key, c.others);
					if (InsertVex(ALGraphs.elem[num].G,c) == ERROR) printf("插入失败\n");
					else printf("插入成功\n");
					getchar();
					getchar();
					break;
				case 8:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要删除的结点的数值：\n");
					scanf("%d", &elem2);
					if (DeleteVex(ALGraphs.elem[num].G, elem2) == ERROR)
						printf("删除失败\n");
					else
						printf("删除成功\n");
					getchar();
					getchar();
					break;
				case 9:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要增加的弧的两个顶点：\n");
					scanf("%d%d",&v,&w);
					temp=InsertArc(ALGraphs.elem[num].G,v,w);
					if(temp==ERROR) printf("插入失败\n");
					else printf("插入成功\n");
					getchar();
					getchar();
					break;
				case 10:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入需要删除的弧的两个顶点：\n");
					scanf("%d%d",&v,&w);
					temp=DeleteArc(ALGraphs.elem[num].G,v,w);
					if(temp==ERROR) printf("删除失败\n");
					else printf("删除成功\n");
					getchar();
					getchar();
					break;
				case 11:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("所有数据为：\n");
					printall(ALGraphs.elem[num].G);
					getchar();
					getchar();
					break;
				case 12:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("深度优先搜索：\n");
					DFSTraverse(ALGraphs.elem[num].G,visit);
					printf("广度优先搜索：\n");
					BFSTraverse(ALGraphs.elem[num].G,visit);
					getchar();
					getchar();
					break;
				case 13:
					if(ALGraphs.elem[num].G.vexnum==0)
					{
						printf("图为空！\n");
						getchar();
						getchar();
						break;
					}
					printf("请输入储存数据的文件名:\n");
					scanf("%s", name2);
					temp00 = SaveGraph(ALGraphs.elem[num].G, name2);
					if (temp00 == ERROR) printf("写入失败！\n");
					else
						printf("写入成功！\n");
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
/*销毁无向图G,删除G的全部顶点和边*/
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
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.key==u)
			return i;
	return -1;
    /********** End **********/
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
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
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum==1&&v==G.vertices[0].data.key) return ERROR;
	int flag[20]={0},i;
	for(int i=0;i<G.vexnum;i++)
		flag[G.vertices[i].data.key]++;
	if(flag[v]==0) 
		return ERROR;
	ArcNode *p,*q;
	for(i=0;i<G.vexnum;i++) //删除结点
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
	for(int j=i+1;j<G.vexnum;j++) //后面节点前移
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
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
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
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
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
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
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
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
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
// 只需要在ALGraphs中增加一个名称为ALGraphName的空图，图数据由后台测试程序插入。
{
	ALGraphs->elem[ALGraphs->length].G.kind = UDG;
	ALGraphs->elem[ALGraphs->length].G.arcnum = 0;
	ALGraphs->elem[ALGraphs->length].G.vexnum = 0;
	strcpy(ALGraphs->elem[ALGraphs->length].name, ALGraphName);
	ALGraphs->length++;
	return OK;
}

status RemoveALGraph(ALGraphs* ALGraphs, char ALGraphName[])
// ALGraphs中删除一个名称为ALGraphName的图
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
// 在ALGraphs中查找一个名称为ALGraphName的图，成功返回逻辑序号，否则返回0
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
	//清空图集合
	ALGraphs->length = 0;
	return OK;
}

status ALGraphsEmpty(ALGraphs ALGraphs) {
	//判断图集合是否为空
	if (ALGraphs.length == 0)
		return TRUE;
	else
		return FALSE;
}

status ALGraphsLength(ALGraphs ALGraphs) {
	//求图集合的长度
	return ALGraphs.length;
}

status PrintAllALGraphs(ALGraphs ALGraphs) {
	//打印图集合中的所有元素
	if (ALGraphs.length == 0) return ERROR;
	else {
		printf("所有图依次为:\n");
		for (int i = 0; i < ALGraphs.length; i++) {
			printf("%d\t%s\n", i + 1, ALGraphs.elem[i].name);
		}
	}
	return OK;
}

status InitALGraphs(ALGraphs* ALGraphs) {
	//初始化图集合
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