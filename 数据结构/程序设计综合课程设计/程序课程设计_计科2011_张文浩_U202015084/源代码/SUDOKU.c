#include "SAT_SUDOKU.h"

status printsudoku(int sudoku[][10]) //输出数独
{
    for (int i = 1; i <= 9; i++)
    {
        if (i % 3 == 1) printf("-------------------------------\n"); //分割线
        for (int j = 1; j <= 9; j++)
        {
            if (j % 3 == 1) printf("|"); //分割线
            printf("%2d ", sudoku[i][j]);
            if (j == 9) printf("|\n"); //分割线
        }
    }
    printf("-------------------------------\n"); //分割线
    return OK;
}
status convertresult(int sudoku[][10]) //结果转换
{
    for (int t = 1; t <= 729; t++)
        if (result[t] == 1)
            for (int i = 1; i <= 9; i++)
                for (int j = 1; j <= 9; j++)
                    for (int n = 1; n <= 9; n++)
                        if (t == (i - 1) * 81 + (j - 1) * 9 + n)
                            sudoku[i][j] = n;
    return OK;
}
status judgenum(int sudoku[][10], int row, int col, int n) //判断填入该数是否可行
{
    int temp1, temp2;
    for (int k = 1; k <= 9; k++)
        if (sudoku[row][k] == n || sudoku[k][col] == n) return ERROR; //所在行和列不能有重复
    for (int k = 1; k <= 9; k++) //找到所在的分块
        if (k >= row && k % 3 == 0)
        {
            temp1 = k;
            break;
        }
    for (int k = 1; k <= 9; k++)
        if (k >= col && k % 3 == 0)
        {
            temp2 = k;
            break;
        }
    for (int i = temp1 - 2; i <= temp1; i++) //分块中不能有重复
        for (int j = temp2 - 2; j <= temp2; j++)
            if (sudoku[i][j] == n) return ERROR;
    return OK;
}
Total initial(Total SATList) //初始化子句集
{
    SATList = (Total)malloc(sizeof(total));
    result = (int*)malloc(sizeof(int) * 730);
    for (int i = 1; i <= 729; i++) result[i] = 0;
    SATList->count_of_clause = SATList->emptyclause = SATList->singleclause = SATList->clacount = 0;
    SATList->varcount = 729;
    SATList->clahead = (Clause)malloc(sizeof(clause));
    SATList->clahead->next = NULL;
    SATList->clahead->count_of_var = 0;
    SATList->clahead->head = (Varnode)malloc(sizeof(varnode));
    SATList->clahead->head->next = NULL;
    return SATList;
}
status createnode(Total SATList, int temp) //创建文字
{
    Clause c = SATList->clahead;
    while (c->next) c = c->next;
    if (temp != 0) //不为0说明这一句公式的读入没有完成
    {
        Varnode p = (Varnode)malloc(sizeof(varnode));
        p->data = temp;
        p->next = NULL;
        Varnode q = c->head;
        if (q->next == NULL && abs(q->data) > SATList->varcount) c->head = p; //首结点
        else { //非首结点
            while (q->next) q = q->next;
            q->next = p;
        }
        c->count_of_var++;
    }
    else //为0说明这句公式已经读完，这里为对下一句公式的初始化
    {
        SATList->clacount++;
        SATList->count_of_clause++;
        if (c->count_of_var == 1) SATList->singleclause++;
        c->next = (Clause)malloc(sizeof(clause));
        c->next->head = (Varnode)malloc(sizeof(varnode));
        c->next->next = NULL;
        c->next->head->next = NULL;
        c->next->count_of_var = 0;
    }
    return OK;
}
status createorigin(Total SATList, int sudoku[][10]) //创建原数独中不为0的数对应的文字
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (sudoku[i][j])
            {
                createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + sudoku[i][j]); //转换公式
                createnode(SATList, 0); //结束标志
            }
    return OK;
}
status createsingle(Total SATList, int sudoku[][10]) //单元格约束
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (sudoku[i][j] == 0) //该单元格可以至少填入一个数字
            {
                for (int k = 1; k <= 9; k++)
                    createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + k);
                createnode(SATList, 0);
                for (int m = 1; m <= 9; m++)
                    for (int n = m + 1; n <= 9; n++) //该单元格只能填入一个数字
                    {
                        createnode(SATList, -((i - 1) * 81 + (j - 1) * 9 + m));
                        createnode(SATList, -((i - 1) * 81 + (j - 1) * 9 + n));
                        createnode(SATList, 0);
                    }

            }
    return OK;
}
status createrow(Total SATList, int sudoku[][10]) //行约束
{
    for (int row = 1; row <= 9; row++)
    {
        for (int j = 1; j <= 9; j++) //该行含有1-9
        {
            for (int i = 1; i <= 9; i++)
                createnode(SATList, (row - 1) * 81 + (i - 1) * 9 + j);
            createnode(SATList, 0);
        }
        for (int n = 1; n <= 9; n++) //该行的每个位置只能填入一个数字
            for (int i = 1; i <= 9; i++)
                for (int j = i + 1; j <= 9; j++)
                {
                    createnode(SATList, -((row - 1) * 81 + (i - 1) * 9 + n));
                    createnode(SATList, -((row - 1) * 81 + (j - 1) * 9 + n));
                    createnode(SATList, 0);
                }
    }
    return OK;
}
status createcol(Total SATList, int sudoku[][10]) //列约束
{
    for (int col = 1; col <= 9; col++)
    {
        for (int i = 1; i <= 9; i++)//该列含有1-9
        {
            for (int j = 1; j <= 9; j++)
                createnode(SATList, (j - 1) * 81 + (col - 1) * 9 + i);
            createnode(SATList, 0);
        }
        for (int n = 1; n <= 9; n++) //该列的每个位置只能填入一个数字
            for (int i = 1; i <= 9; i++)
                for (int j = i + 1; j <= 9; j++)
                {
                    createnode(SATList, -((i - 1) * 81 + (col - 1) * 9 + n));
                    createnode(SATList, -((j - 1) * 81 + (col - 1) * 9 + n));
                    createnode(SATList, 0);
                }
    }
    return OK;
}
status createblock(Total SATList, int sudoku[][10]) //分块约束
{
    for (int x = 1; x <= 3; x++)
    {
        for (int y = 1; y <= 3; y++)
        {
            int erow = x * 3, ecol = y * 3; //找到所在分块
            int brow = erow - 2, bcol = ecol - 2;
            for (int n = 1; n <= 9; n++) //该分块可以填入1-9
            {
                for (int i = brow; i <= erow; i++)
                    for (int j = bcol; j <= ecol; j++)
                        createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + n);
                createnode(SATList, 0);
            }
            for (int k = 1; k <= 9; k++) //对分块中每个单元格，只能填入一个数字
            {
                for (int x = brow; x <= erow; x++)
                    for (int y = bcol; y <= ecol; y++)
                    {
                        for (int m = x; m <= erow; m++)
                            for (int n = (m == x ? y + 1 : bcol); n <= ecol; n++)
                            {
                                createnode(SATList, -((x - 1) * 81 + (y - 1) * 9 + k));
                                createnode(SATList, -((m - 1) * 81 + (n - 1) * 9 + k));
                                createnode(SATList, 0);
                            }
                    }
            }
        }
    }
    return OK;
}
Total createcnf(Total SATList, int sudoku[][10]) //将数独转换为SAT算例
{
    SATList = initial(SATList);
    createorigin(SATList, sudoku);
    createsingle(SATList, sudoku);
    createrow(SATList, sudoku);
    createcol(SATList, sudoku);
    createblock(SATList, sudoku);
    Clause c = SATList->clahead;
    while (c->next->next) c = c->next; //最后一个子句的next指向空，因为多初始化了一次
    free(c->next);
    c->next = NULL;
    return SATList;
}
status createsudoku(Total SATList, int sudoku[][10]) //创建完整答案数独
{
    srand(time(0));
    int count = 1;
    while (count <= 11) //随机赋值
    {

        int i, j, n;
        i = rand() % 9 + 1;
        j = rand() % 9 + 1;
        n = rand() % 9 + 1;
        if (sudoku[i][j] == 0 && judgenum(sudoku, i, j, n))
        {
            sudoku[i][j] = n;
            count++;
        }
    }
    SATList = createcnf(SATList, sudoku); //转化为SAT算例
    DPLL1(SATList); //求解
    convertresult(SATList, sudoku); //转化为数独
    return OK;
}
status createsudoku2(int sudoku[][10], int row, int num)
{
    int c[10];
    srand(time(0));
    for (int i = 1; i <= 9; i++)
        c[i] = i;
    for (int i = 1; i <= 20; i++)
    {
        int k = rand() % 9 + 1;
        int temp = c[1];
        c[1] = c[k];
        c[k] = temp;
    }
    for (int i = 1; i <= 9; i++)
    {
        int col = c[i];
        if (judgenum(sudoku, row, col, num) && !sudoku[row][col])
        {
            sudoku[row][col] = num;
            if (row == 9)
            {
                if (num == 9) return OK;
                if (createsudoku2(sudoku, 1, num + 1)) return OK;
            }
            else
            {
                if (createsudoku2(sudoku, row + 1, num)) return OK;
            }
            sudoku[row][col] = 0;
        }
    }
    return ERROR;
}
status digholes(int sudoku[][10], int count, int holes[][10]) //挖洞法创建需求解的数独

{
    srand(time(0));
    do
    {
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 9; j++)
                if (holes[i][j])
                {
                    sudoku[i][j] = holes[i][j];
                    holes[i][j] = 0;
                }
        int cnt = count;
        while (cnt)
        {
            int x = rand() % 9 + 1;
            int y = rand() % 9 + 1;
            if (sudoku[x][y] != 0)
            {
                holes[x][y] = sudoku[x][y];
                sudoku[x][y] = 0;
                cnt--;
            }
        }
        Total SATList = (Total)malloc(sizeof(total));
        SATList = createcnf(SATList, sudoku);
        allresult = 0;
        DPLLPRO(SATList);
    } while (allresult > 1);
    printf("\n需要求解的数独为：\n");
    printsudoku(sudoku);
}