#include "SAT_SUDOKU.h"

Total fileload(Total SATList, char* filename) //��ȡcnf�ļ�
{
    SATList = (Total)malloc(sizeof(total));
    FILE* fp;
    char ch;
    int temp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        return NULL;
    }
    while (fread(&ch, sizeof(char), 1, fp)) //���ע��
    {
        if (ch != 'p') putchar(ch);
        else
        {
            fread(&ch, sizeof(char), 1, fp);
            if (ch == ' ') break;
        }
    }
    for (int i = 0; i < 4; i++) //���롰 cnf ��
        fread(&ch, sizeof(char), 1, fp);
    fscanf(fp, "%d", &SATList->varcount); //�����������͹�ʽ��
    fscanf(fp, "%d", &SATList->clacount);
    printf("cnf�ļ��е���������%d\t��ʽ����%d\n", SATList->varcount, SATList->clacount);
    varcount = SATList->varcount;
    result = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    for (int i = 1; i <= SATList->varcount; i++) result[i] = 0;
    SATList->clahead = (Clause)malloc(sizeof(clause)); //���µ�forѭ����Ϊ��ʼ��
    SATList->clahead->next = NULL;
    SATList->clahead->head = (Varnode)malloc(sizeof(varnode));
    SATList->clahead->head->next = NULL;
    SATList->clahead->count_of_var = 0;
    SATList->emptyclause = SATList->singleclause = 0;
    SATList->count_of_clause = SATList->clacount;
    Clause c = SATList->clahead;
    for (int i = 1; fscanf(fp, "%d", &temp) != EOF && i <= SATList->clacount;)
    {
        if (temp != 0) //��Ϊ0˵����һ�乫ʽ�Ķ���û�����
        {
            Varnode p = (Varnode)malloc(sizeof(varnode));
            p->data = temp;
            p->next = NULL;
            Varnode q = c->head;
            if (q->next == NULL && abs(q->data) > SATList->varcount) //�׽��
                c->head = p;
            else { //�������
                while (q->next) q = q->next;
                q->next = p;
            }
            c->count_of_var++;
        }
        else //Ϊ0˵����乫ʽ�Ѿ����꣬i����������һ�乫ʽ�Ķ��룬����Ϊ����һ�乫ʽ�ĳ�ʼ��
        {
            if (i == SATList->clacount) //�Ѷ��꣬���ض���һ����г�ʼ��
            {
                c->next = NULL;
                break;
            }
            if (c->count_of_var == 1) SATList->singleclause++; //���Ӿ������һ
            c->next = (Clause)malloc(sizeof(clause)); //����Ϊ��һ�����ĳ�ʼ��
            c->next->head = (Varnode)malloc(sizeof(varnode));
            c->next->next = NULL;
            c->next->head->next = NULL;
            c->next->count_of_var = 0;
            c = c->next;
            i++;
        }
    }
    printf("��ȡ���!\n");
    fclose(fp);
    return SATList;
}
Total Duplicate(Total SATList) //�����Ӿ伯
{
    Total temp = (Total)malloc(sizeof(total));  //�����ĳ�ʼ��
    temp->varcount = SATList->varcount;
    temp->clacount = SATList->clacount;
    temp->singleclause = SATList->singleclause;
    temp->emptyclause = SATList->emptyclause;
    temp->count_of_clause = SATList->count_of_clause;
    temp->clahead = (Clause)malloc(sizeof(clause));
    temp->clahead->next = NULL;
    temp->clahead->head = (Varnode)malloc(sizeof(varnode));
    temp->clahead->head->next = NULL;
    Clause c = SATList->clahead;
    Clause ctemp = temp->clahead;
    while (c) //�����Ӿ伯���򸱱���д������
    {
        ctemp->count_of_var = c->count_of_var;
        Varnode p = c->head, ptemp = ctemp->head;
        while (p)//�����Ӿ�
        {
            ptemp->data = p->data;
            p = p->next;
            if (p == NULL) //���һ������
            {
                ptemp->next = NULL;
                break;
            }
            ptemp->next = (Varnode)malloc(sizeof(varnode)); //��һ�����ֵĳ�ʼ��
            ptemp = ptemp->next;
            ptemp->next = NULL;
        }
        c = c->next;
        if (c == NULL) //���һ��
        {
            ctemp->next = NULL;
            break;
        }
        ctemp->next = (Clause)malloc(sizeof(clause)); //��һ��ĳ�ʼ��
        ctemp = ctemp->next;
        ctemp->next = NULL;
        ctemp->head = (Varnode)malloc(sizeof(varnode));
        ctemp->head->next = NULL;
    }
    return temp;
}
status Traverse(Total SATList) //���cnf�ļ�
{
    Clause c = SATList->clahead;
    while (c) //�����Ӿ伯
    {
        Varnode p = c->head;
        printf("(");
        while (p)
        {
            printf("%d", p->data);
            if (p->next != NULL) printf("��"); //�������һ�����ֵ�ʱ�����
            p = p->next;
        }
        printf(")");
        if (c->next != NULL) printf("��"); //�������һ���ʱ�����

        c = c->next;
    }
    return OK;
}
int findsingleclause(Total SATList) //Ѱ�ҵ��Ӿ�
{
    Clause c = SATList->clahead;
    if (SATList->singleclause == 0) return 0; //û�е��Ӿ�
    while (c) //�����Ӿ伯�ҵ�һ�����Ӿ�
    {
        if (c->count_of_var == 1)
            return c->head->data;
        c = c->next;
    }
    return 0;
}
status deleteclause(Total SATList, int temp) //ɾ������Ҫ����Ӿ�
{
    Clause c = SATList->clahead;
    while (c) //�����Ӿ伯
    {
        int flag = 0;
        Varnode p = c->head, q;
        while (p) //�����Ӿ�
        {
            if (p->data == temp) //�ҵ�������
            {
                flag = 1; //�ı�ı��
                if (c->count_of_var == 1) SATList->singleclause--; //����ǵ��Ӿ���õ��Ӿ���������
                p = c->head;
                q = p->next;
                while (q) //���ٸ��Ӿ���׽��֮��Ľ��
                {
                    p->next = p->next->next;
                    free(q);
                    q = p->next;
                }
                free(p); //�����׽��
                c->head = NULL;
                SATList->count_of_clause--; //�Ӿ���������
                if (c != SATList->clahead) //c�������Ӿ䣬����c����
                {
                    Clause ctemp = SATList->clahead;
                    while (ctemp->next != c) ctemp = ctemp->next; //�ҵ�c��ǰһ���Ӿ�
                    ctemp->next = c->next;
                    ctemp = ctemp->next;
                    free(c);
                    c = ctemp; //ʵ����c�����˺���
                }
                else if (c == SATList->clahead && c->next == NULL) //c�����Ӿ���ֻ��cһ���Ӿ�
                {
                    free(SATList->clahead);
                    SATList->clahead = NULL;
                }
                else if (c == SATList->clahead && c->next != NULL) //c�����Ӿ䵫���������Ӿ�
                {
                    SATList->clahead = c->next; //���Ӿ�ָ��c����һ�Ӿ�
                    free(c);
                    c = SATList->clahead; //c��ָ�����Ӿ�
                }
                break;
            }
            p = p->next;
        }
        if (SATList->clahead == NULL) break; //�Ӿ伯Ϊ�գ�ֱ�ӷ���
        else
        {
            if (flag == 0) c = c->next; //δ�ı䣬c����
        }
    }
    return OK;
}
status deleteword(Total SATList, int temp) //ɾ������Ҫ�������
{
    Clause c = SATList->clahead;
    while (c) //�����Ӿ伯
    {
        int flag = 0;
        Varnode p = c->head, q;
        while (p) //�����Ӿ�
        {
            if (p->data == -temp) //�ҵ�������
            {
                flag = 1; //�ı�ı��
                c->count_of_var--; //���Ӿ�����������
                if (c->count_of_var == 0)
                    SATList->emptyclause++; //������Ϊ0�����Ӿ�������
                if (p != c->head) //p�����׽�㣬���ټ���
                {
                    q = c->head;
                    while (q->next != p) q = q->next;
                    q->next = p->next;
                    free(p);
                    q = q->next;
                    p = q; //ʵ����p��������
                }
                else if (p == c->head && p->next != NULL) //p���׽�㵫����Ψһһ�����
                {
                    c->head = p->next;//�׽��ָ����һ�����
                    free(p);
                    p = c->head;
                }
                else if (p == c->head && p->next == NULL) //p���׽������Ψһһ����� 
                {
                    free(c->head); //�����׽��
                    c->head = NULL;
                    break;
                }
                continue; //���������Ӿ�
            }
            p = p->next;
        }
        if (c->count_of_var == 1 && flag == 1) SATList->singleclause++; //�������Ӿ䣬���Ӿ���������
        c = c->next;
    }
    return OK;
}
status addclause(Total SATList, int temp) //���ӵ��Ӿ�
{
    Clause c = SATList->clahead;
    while (c->next) c = c->next;//�ҵ����һ���Ӿ�
    Clause ctemp = (Clause)malloc(sizeof(clause));
    ctemp->count_of_var = 1;
    ctemp->next = NULL;
    ctemp->head = (Varnode)malloc(sizeof(varnode));
    ctemp->head->data = temp;
    ctemp->head->next = NULL;
    c->next = ctemp;
    SATList->count_of_clause++;
    SATList->singleclause++;
    return OK;
}

int judgeemptyclause(Total SATList) //�ж��Ӿ伯���Ƿ��п��Ӿ�
{
    if (SATList->emptyclause) return 1;
    return 0;
}
int judgeemptytotal(Total SATList) //�ж��Ӿ伯�Ƿ�Ϊ��
{
    if (SATList->count_of_clause == 0) return 1;
    return 0;
}
int getword1(Total SATList) //��ȡ��Ԫ�㷨һ
{
    int pmax = 0, nmax = 0, ptemp = 0, ntemp = 0, temp = 0;
    int* pfre = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    int* nfre = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    for (int i = 1; i <= SATList->varcount; i++)
        pfre[i] = nfre[i] = 0;
    Clause c = SATList->clahead;
    while (c) //ͳ������������Ԫ�ĳ��ִ���
    {
        Varnode p = c->head;
        while (p)
        {
            if (p->data > 0) pfre[p->data]++;
            else nfre[-p->data]++;
            p = p->next;
        }
        c = c->next;
    }
    for (int i = 1; i <= SATList->varcount; i++)
    {
        if (pmax < pfre[i])
        {
            pmax = pfre[i];
            ptemp = i;
        }
        if (nmax < nfre[i])
        {
            nmax = nfre[i];
            ntemp = i;
        }
    }
    free(pfre);
    free(nfre);
    return temp = pmax > nmax ? ptemp : ntemp; //���س��ִ�����������
}

int getword2(Total SATList) //��ȡ��Ԫ�㷨��
{
    return SATList->clahead->head->data; //�ҵ�һ���Ӿ�ĵ�һ������
}

int getword3(Total SATList)
{
    double pmax = 0, nmax = 0;
    int ptemp = 0, ntemp = 0, temp = 0;
    double* pfre = (double*)malloc(sizeof(double) * (SATList->varcount + 1));
    double* nfre = (double*)malloc(sizeof(double) * (SATList->varcount + 1));
    for (int i = 1; i <= SATList->varcount; i++)
        pfre[i] = nfre[i] = 0;
    Clause c = SATList->clahead;
    while (c) //ͳ������������Ԫ��Ȩ��
    {
        Varnode p = c->head;
        while (p)
        {
            if (p->data > 0) pfre[p->data] += pow(2, -c->count_of_var);
            else nfre[-p->data] += pow(2, -c->count_of_var);
            p = p->next;
        }
        c = c->next;
    }
    for (int i = 1; i <= SATList->varcount; i++)
    {
        if (pmax < pfre[i])
        {
            pmax = pfre[i];
            ptemp = i;
        }
        if (nmax < nfre[i])
        {
            nmax = nfre[i];
            ntemp = -i;
        }
    }
    free(pfre);
    free(nfre);
    return temp = pmax > nmax ? ptemp : ntemp; //���س��ִ�����������
}
Total destroy(Total SATList)
{
    Clause c = SATList->clahead;
    while (c) //�����Ӿ伯
    {
        if (c->head != NULL) //�����Ӿ����������
        {
            Varnode p = c->head, q = p->next;
            while (q)
            {
                p->next = p->next->next;
                free(q);
                q = p->next;
            }
            free(p);
            c->head = NULL;
        }
        c = c->next;
    }
    c = SATList->clahead;
    if (c != NULL) //���������Ӿ���
    {
        Clause ctemp = c->next;
        while (ctemp)
        {
            c->next = c->next->next;
            free(ctemp);
            ctemp = c->next;
        }
        free(c);
        SATList->clahead = NULL;
    }
    free(SATList); //�����Ӿ伯
    SATList = NULL;
    return SATList;
}
status DPLL1(Total SATList) //�����㷨
{
    int temp;
    temp = findsingleclause(SATList); //�ҵ��Ӿ�
    while (temp)
    {
        if (temp > 0) result[temp] = 1; //���½������
        else result[-temp] = 0;
        deleteclause(SATList, temp); //ɾ���Ӿ������
        deleteword(SATList, temp);
        if (judgeemptytotal(SATList)) //�ж��Ƿ�Ϊ��
        {
            SATList = destroy(SATList);
            return OK;
        }
        if (judgeemptyclause(SATList)) //�ж����޿��Ӿ�
        {
            SATList = destroy(SATList);
            return ERROR;
        }
        temp = findsingleclause(SATList); //�ҵ��Ӿ�
    }
    temp = getword1(SATList); //��ȡ��Ԫ�㷨һ
    Total ctemp = Duplicate(SATList); //�����Ӿ伯�����ڻ���
    addclause(SATList, temp); //��ӱ�Ԫ�Ӿ�
    if (DPLL1(SATList)) //�ݹ����
        return OK;
    else {
        addclause(ctemp, -temp); //��Ӹ���Ԫ�Ӿ�
        return DPLL1(ctemp); //�ݹ����
    }
}
status DPLL2(Total SATList)
{
    int temp;
    temp = findsingleclause(SATList);
    while (temp)
    {
        if (temp > 0) result[temp] = 1;
        else result[-temp] = 0;
        deleteclause(SATList, temp);
        deleteword(SATList, temp);
        if (judgeemptytotal(SATList))
        {
            SATList = destroy(SATList);
            return OK;
        }
        if (judgeemptyclause(SATList))
        {
            SATList = destroy(SATList);
            return ERROR;
        }
        temp = findsingleclause(SATList);
    }
    temp = getword2(SATList); //��ȡ��Ԫ�㷨��
    Total ctemp = Duplicate(SATList);
    addclause(SATList, temp);
    if (DPLL2(SATList))
        return OK;
    else {
        addclause(ctemp, -temp);
        return DPLL2(ctemp);
    }
}
void DPLLPRO(Total SATList)
{
    if (allresult > 1) return;
    int temp;
    temp = findsingleclause(SATList);
    while (temp)
    {
        if (temp > 0) result[temp] = 1;
        else result[-temp] = 0;
        deleteclause(SATList, temp);
        deleteword(SATList, temp);
        if (judgeemptytotal(SATList))
        {
            SATList = destroy(SATList);
            allresult++;
            return;
        }
        if (judgeemptyclause(SATList))
        {
            SATList = destroy(SATList);
            return;
        }
        temp = findsingleclause(SATList);
    }
    temp = getword2(SATList);
    Total ctemp = Duplicate(SATList);
    addclause(SATList, temp);
    DPLLPRO(SATList); //��������ֱ���
    addclause(ctemp, -temp);
    DPLLPRO(ctemp);
}
status saveanswer(Total SATList, int dresult, double time) //����Ϊͬ��res�ļ�
{
    int len = strlen(savefile);
    savefile[len - 1] = 's'; //���ĺ�׺
    savefile[len - 2] = 'e';
    savefile[len - 3] = 'r';
    FILE* fp;
    if ((fp = fopen(savefile, "wb")) == NULL)
    {
        printf("�ļ�����ʧ��\n");
        return ERROR;
    }
    else
    {
        if (dresult == 0 || dresult == 1)
        {
            fprintf(fp, "s %d \n", dresult);
            if (dresult == 1)
            {
                fprintf(fp, "v ");
                for (int i = 1; i <= varcount; i++)
                    fprintf(fp, "%d ", (result[i] == 1) ? i : -i);
                fprintf(fp, "\nt %.0lf", time);
            }
        }
        else
            fprintf(fp, "-1");
        printf("�ļ�����ɹ�\n");
        return OK;
    }
}
status savecnf(Total SATList) //����Ϊcnf�ļ�
{
    char filename[100];
    printf("�����뱣����ļ�����\n");
    scanf("%s", filename);
    FILE* fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("�ļ�����ʧ��\n");
        return ERROR;
    }
    else
    {
        fprintf(fp, "p cnf ");
        fprintf(fp, "%d %d\n", SATList->varcount, SATList->clacount);
        Clause c = SATList->clahead;
        while (c)
        {
            Varnode p = c->head;
            while (p)
            {
                fprintf(fp, "%d ", p->data);
                p = p->next;
            }
            fprintf(fp, "0\n");
            c = c->next;
        }
        printf("�ļ�����ɹ�\n");
        return OK;
    }
}