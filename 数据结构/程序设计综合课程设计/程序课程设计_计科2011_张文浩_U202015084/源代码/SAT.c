#include "SAT_SUDOKU.h"

Total fileload(Total SATList, char* filename) //读取cnf文件
{
    SATList = (Total)malloc(sizeof(total));
    FILE* fp;
    char ch;
    int temp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("文件打开失败！\n");
        return NULL;
    }
    while (fread(&ch, sizeof(char), 1, fp)) //输出注释
    {
        if (ch != 'p') putchar(ch);
        else
        {
            fread(&ch, sizeof(char), 1, fp);
            if (ch == ' ') break;
        }
    }
    for (int i = 0; i < 4; i++) //读入“ cnf ”
        fread(&ch, sizeof(char), 1, fp);
    fscanf(fp, "%d", &SATList->varcount); //读入文字数和公式数
    fscanf(fp, "%d", &SATList->clacount);
    printf("cnf文件中的文字数：%d\t公式数：%d\n", SATList->varcount, SATList->clacount);
    varcount = SATList->varcount;
    result = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    for (int i = 1; i <= SATList->varcount; i++) result[i] = 0;
    SATList->clahead = (Clause)malloc(sizeof(clause)); //以下到for循环皆为初始化
    SATList->clahead->next = NULL;
    SATList->clahead->head = (Varnode)malloc(sizeof(varnode));
    SATList->clahead->head->next = NULL;
    SATList->clahead->count_of_var = 0;
    SATList->emptyclause = SATList->singleclause = 0;
    SATList->count_of_clause = SATList->clacount;
    Clause c = SATList->clahead;
    for (int i = 1; fscanf(fp, "%d", &temp) != EOF && i <= SATList->clacount;)
    {
        if (temp != 0) //不为0说明这一句公式的读入没有完成
        {
            Varnode p = (Varnode)malloc(sizeof(varnode));
            p->data = temp;
            p->next = NULL;
            Varnode q = c->head;
            if (q->next == NULL && abs(q->data) > SATList->varcount) //首结点
                c->head = p;
            else { //其他结点
                while (q->next) q = q->next;
                q->next = p;
            }
            c->count_of_var++;
        }
        else //为0说明这句公式已经读完，i自增进行下一句公式的读入，这里为对下一句公式的初始化
        {
            if (i == SATList->clacount) //已读完，不必对下一句进行初始化
            {
                c->next = NULL;
                break;
            }
            if (c->count_of_var == 1) SATList->singleclause++; //单子句个数加一
            c->next = (Clause)malloc(sizeof(clause)); //以下为下一个语句的初始化
            c->next->head = (Varnode)malloc(sizeof(varnode));
            c->next->next = NULL;
            c->next->head->next = NULL;
            c->next->count_of_var = 0;
            c = c->next;
            i++;
        }
    }
    printf("读取完毕!\n");
    fclose(fp);
    return SATList;
}
Total Duplicate(Total SATList) //复制子句集
{
    Total temp = (Total)malloc(sizeof(total));  //副本的初始化
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
    while (c) //遍历子句集，向副本中写入数据
    {
        ctemp->count_of_var = c->count_of_var;
        Varnode p = c->head, ptemp = ctemp->head;
        while (p)//遍历子句
        {
            ptemp->data = p->data;
            p = p->next;
            if (p == NULL) //最后一个文字
            {
                ptemp->next = NULL;
                break;
            }
            ptemp->next = (Varnode)malloc(sizeof(varnode)); //下一个文字的初始化
            ptemp = ptemp->next;
            ptemp->next = NULL;
        }
        c = c->next;
        if (c == NULL) //最后一句
        {
            ctemp->next = NULL;
            break;
        }
        ctemp->next = (Clause)malloc(sizeof(clause)); //下一句的初始化
        ctemp = ctemp->next;
        ctemp->next = NULL;
        ctemp->head = (Varnode)malloc(sizeof(varnode));
        ctemp->head->next = NULL;
    }
    return temp;
}
status Traverse(Total SATList) //输出cnf文件
{
    Clause c = SATList->clahead;
    while (c) //遍历子句集
    {
        Varnode p = c->head;
        printf("(");
        while (p)
        {
            printf("%d", p->data);
            if (p->next != NULL) printf("∨"); //不是最后一个文字的时候输出
            p = p->next;
        }
        printf(")");
        if (c->next != NULL) printf("∧"); //不是最后一句的时候输出

        c = c->next;
    }
    return OK;
}
int findsingleclause(Total SATList) //寻找单子句
{
    Clause c = SATList->clahead;
    if (SATList->singleclause == 0) return 0; //没有单子句
    while (c) //遍历子句集找第一个单子句
    {
        if (c->count_of_var == 1)
            return c->head->data;
        c = c->next;
    }
    return 0;
}
status deleteclause(Total SATList, int temp) //删除符合要求的子句
{
    Clause c = SATList->clahead;
    while (c) //遍历子句集
    {
        int flag = 0;
        Varnode p = c->head, q;
        while (p) //遍历子句
        {
            if (p->data == temp) //找到该文字
            {
                flag = 1; //改变的标记
                if (c->count_of_var == 1) SATList->singleclause--; //如果是单子句就让单子句数量减少
                p = c->head;
                q = p->next;
                while (q) //销毁该子句除首结点之外的结点
                {
                    p->next = p->next->next;
                    free(q);
                    q = p->next;
                }
                free(p); //销毁首结点
                c->head = NULL;
                SATList->count_of_clause--; //子句数量减少
                if (c != SATList->clahead) //c不是首子句，销毁c即可
                {
                    Clause ctemp = SATList->clahead;
                    while (ctemp->next != c) ctemp = ctemp->next; //找到c的前一个子句
                    ctemp->next = c->next;
                    ctemp = ctemp->next;
                    free(c);
                    c = ctemp; //实际上c发生了后移
                }
                else if (c == SATList->clahead && c->next == NULL) //c是首子句且只有c一个子句
                {
                    free(SATList->clahead);
                    SATList->clahead = NULL;
                }
                else if (c == SATList->clahead && c->next != NULL) //c是首子句但还有其他子句
                {
                    SATList->clahead = c->next; //首子句指向c的下一子句
                    free(c);
                    c = SATList->clahead; //c仍指向首子句
                }
                break;
            }
            p = p->next;
        }
        if (SATList->clahead == NULL) break; //子句集为空，直接返回
        else
        {
            if (flag == 0) c = c->next; //未改变，c后移
        }
    }
    return OK;
}
status deleteword(Total SATList, int temp) //删除符合要求的文字
{
    Clause c = SATList->clahead;
    while (c) //遍历子句集
    {
        int flag = 0;
        Varnode p = c->head, q;
        while (p) //遍历子句
        {
            if (p->data == -temp) //找到该文字
            {
                flag = 1; //改变的标记
                c->count_of_var--; //该子句文字数减少
                if (c->count_of_var == 0)
                    SATList->emptyclause++; //文字数为0，空子句数增加
                if (p != c->head) //p不是首结点，销毁即可
                {
                    q = c->head;
                    while (q->next != p) q = q->next;
                    q->next = p->next;
                    free(p);
                    q = q->next;
                    p = q; //实际上p发生后移
                }
                else if (p == c->head && p->next != NULL) //p是首结点但不是唯一一个结点
                {
                    c->head = p->next;//首结点指向下一个结点
                    free(p);
                    p = c->head;
                }
                else if (p == c->head && p->next == NULL) //p是首结点且是唯一一个结点 
                {
                    free(c->head); //销毁首结点
                    c->head = NULL;
                    break;
                }
                continue; //继续遍历子句
            }
            p = p->next;
        }
        if (c->count_of_var == 1 && flag == 1) SATList->singleclause++; //产生单子句，单子句数量增加
        c = c->next;
    }
    return OK;
}
status addclause(Total SATList, int temp) //增加单子句
{
    Clause c = SATList->clahead;
    while (c->next) c = c->next;//找到最后一个子句
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

int judgeemptyclause(Total SATList) //判断子句集中是否含有空子句
{
    if (SATList->emptyclause) return 1;
    return 0;
}
int judgeemptytotal(Total SATList) //判断子句集是否为空
{
    if (SATList->count_of_clause == 0) return 1;
    return 0;
}
int getword1(Total SATList) //获取变元算法一
{
    int pmax = 0, nmax = 0, ptemp = 0, ntemp = 0, temp = 0;
    int* pfre = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    int* nfre = (int*)malloc(sizeof(int) * (SATList->varcount + 1));
    for (int i = 1; i <= SATList->varcount; i++)
        pfre[i] = nfre[i] = 0;
    Clause c = SATList->clahead;
    while (c) //统计所有正负变元的出现次数
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
    return temp = pmax > nmax ? ptemp : ntemp; //返回出现次数最多的文字
}

int getword2(Total SATList) //获取变元算法二
{
    return SATList->clahead->head->data; //找第一个子句的第一个文字
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
    while (c) //统计所有正负变元的权重
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
    return temp = pmax > nmax ? ptemp : ntemp; //返回出现次数最多的文字
}
Total destroy(Total SATList)
{
    Clause c = SATList->clahead;
    while (c) //遍历子句集
    {
        if (c->head != NULL) //销毁子句的所有文字
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
    if (c != NULL) //销毁所有子句结点
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
    free(SATList); //销毁子句集
    SATList = NULL;
    return SATList;
}
status DPLL1(Total SATList) //核心算法
{
    int temp;
    temp = findsingleclause(SATList); //找单子句
    while (temp)
    {
        if (temp > 0) result[temp] = 1; //更新结果数组
        else result[-temp] = 0;
        deleteclause(SATList, temp); //删除子句和文字
        deleteword(SATList, temp);
        if (judgeemptytotal(SATList)) //判断是否为空
        {
            SATList = destroy(SATList);
            return OK;
        }
        if (judgeemptyclause(SATList)) //判断有无空子句
        {
            SATList = destroy(SATList);
            return ERROR;
        }
        temp = findsingleclause(SATList); //找单子句
    }
    temp = getword1(SATList); //获取变元算法一
    Total ctemp = Duplicate(SATList); //复制子句集，用于回溯
    addclause(SATList, temp); //添加变元子句
    if (DPLL1(SATList)) //递归调用
        return OK;
    else {
        addclause(ctemp, -temp); //添加负变元子句
        return DPLL1(ctemp); //递归调用
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
    temp = getword2(SATList); //获取变元算法二
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
    DPLLPRO(SATList); //两种情况分别考虑
    addclause(ctemp, -temp);
    DPLLPRO(ctemp);
}
status saveanswer(Total SATList, int dresult, double time) //保存为同名res文件
{
    int len = strlen(savefile);
    savefile[len - 1] = 's'; //更改后缀
    savefile[len - 2] = 'e';
    savefile[len - 3] = 'r';
    FILE* fp;
    if ((fp = fopen(savefile, "wb")) == NULL)
    {
        printf("文件保存失败\n");
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
        printf("文件保存成功\n");
        return OK;
    }
}
status savecnf(Total SATList) //保存为cnf文件
{
    char filename[100];
    printf("请输入保存的文件名：\n");
    scanf("%s", filename);
    FILE* fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("文件保存失败\n");
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
        printf("文件保存成功\n");
        return OK;
    }
}