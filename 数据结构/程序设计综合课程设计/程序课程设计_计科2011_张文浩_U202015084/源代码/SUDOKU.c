#include "SAT_SUDOKU.h"

status printsudoku(int sudoku[][10]) //�������
{
    for (int i = 1; i <= 9; i++)
    {
        if (i % 3 == 1) printf("-------------------------------\n"); //�ָ���
        for (int j = 1; j <= 9; j++)
        {
            if (j % 3 == 1) printf("|"); //�ָ���
            printf("%2d ", sudoku[i][j]);
            if (j == 9) printf("|\n"); //�ָ���
        }
    }
    printf("-------------------------------\n"); //�ָ���
    return OK;
}
status convertresult(int sudoku[][10]) //���ת��
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
status judgenum(int sudoku[][10], int row, int col, int n) //�ж���������Ƿ����
{
    int temp1, temp2;
    for (int k = 1; k <= 9; k++)
        if (sudoku[row][k] == n || sudoku[k][col] == n) return ERROR; //�����к��в������ظ�
    for (int k = 1; k <= 9; k++) //�ҵ����ڵķֿ�
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
    for (int i = temp1 - 2; i <= temp1; i++) //�ֿ��в������ظ�
        for (int j = temp2 - 2; j <= temp2; j++)
            if (sudoku[i][j] == n) return ERROR;
    return OK;
}
Total initial(Total SATList) //��ʼ���Ӿ伯
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
status createnode(Total SATList, int temp) //��������
{
    Clause c = SATList->clahead;
    while (c->next) c = c->next;
    if (temp != 0) //��Ϊ0˵����һ�乫ʽ�Ķ���û�����
    {
        Varnode p = (Varnode)malloc(sizeof(varnode));
        p->data = temp;
        p->next = NULL;
        Varnode q = c->head;
        if (q->next == NULL && abs(q->data) > SATList->varcount) c->head = p; //�׽��
        else { //���׽��
            while (q->next) q = q->next;
            q->next = p;
        }
        c->count_of_var++;
    }
    else //Ϊ0˵����乫ʽ�Ѿ����꣬����Ϊ����һ�乫ʽ�ĳ�ʼ��
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
status createorigin(Total SATList, int sudoku[][10]) //����ԭ�����в�Ϊ0������Ӧ������
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (sudoku[i][j])
            {
                createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + sudoku[i][j]); //ת����ʽ
                createnode(SATList, 0); //������־
            }
    return OK;
}
status createsingle(Total SATList, int sudoku[][10]) //��Ԫ��Լ��
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            if (sudoku[i][j] == 0) //�õ�Ԫ�������������һ������
            {
                for (int k = 1; k <= 9; k++)
                    createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + k);
                createnode(SATList, 0);
                for (int m = 1; m <= 9; m++)
                    for (int n = m + 1; n <= 9; n++) //�õ�Ԫ��ֻ������һ������
                    {
                        createnode(SATList, -((i - 1) * 81 + (j - 1) * 9 + m));
                        createnode(SATList, -((i - 1) * 81 + (j - 1) * 9 + n));
                        createnode(SATList, 0);
                    }

            }
    return OK;
}
status createrow(Total SATList, int sudoku[][10]) //��Լ��
{
    for (int row = 1; row <= 9; row++)
    {
        for (int j = 1; j <= 9; j++) //���к���1-9
        {
            for (int i = 1; i <= 9; i++)
                createnode(SATList, (row - 1) * 81 + (i - 1) * 9 + j);
            createnode(SATList, 0);
        }
        for (int n = 1; n <= 9; n++) //���е�ÿ��λ��ֻ������һ������
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
status createcol(Total SATList, int sudoku[][10]) //��Լ��
{
    for (int col = 1; col <= 9; col++)
    {
        for (int i = 1; i <= 9; i++)//���к���1-9
        {
            for (int j = 1; j <= 9; j++)
                createnode(SATList, (j - 1) * 81 + (col - 1) * 9 + i);
            createnode(SATList, 0);
        }
        for (int n = 1; n <= 9; n++) //���е�ÿ��λ��ֻ������һ������
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
status createblock(Total SATList, int sudoku[][10]) //�ֿ�Լ��
{
    for (int x = 1; x <= 3; x++)
    {
        for (int y = 1; y <= 3; y++)
        {
            int erow = x * 3, ecol = y * 3; //�ҵ����ڷֿ�
            int brow = erow - 2, bcol = ecol - 2;
            for (int n = 1; n <= 9; n++) //�÷ֿ��������1-9
            {
                for (int i = brow; i <= erow; i++)
                    for (int j = bcol; j <= ecol; j++)
                        createnode(SATList, (i - 1) * 81 + (j - 1) * 9 + n);
                createnode(SATList, 0);
            }
            for (int k = 1; k <= 9; k++) //�Էֿ���ÿ����Ԫ��ֻ������һ������
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
Total createcnf(Total SATList, int sudoku[][10]) //������ת��ΪSAT����
{
    SATList = initial(SATList);
    createorigin(SATList, sudoku);
    createsingle(SATList, sudoku);
    createrow(SATList, sudoku);
    createcol(SATList, sudoku);
    createblock(SATList, sudoku);
    Clause c = SATList->clahead;
    while (c->next->next) c = c->next; //���һ���Ӿ��nextָ��գ���Ϊ���ʼ����һ��
    free(c->next);
    c->next = NULL;
    return SATList;
}
status createsudoku(Total SATList, int sudoku[][10]) //��������������
{
    srand(time(0));
    int count = 1;
    while (count <= 11) //�����ֵ
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
    SATList = createcnf(SATList, sudoku); //ת��ΪSAT����
    DPLL1(SATList); //���
    convertresult(SATList, sudoku); //ת��Ϊ����
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
status digholes(int sudoku[][10], int count, int holes[][10]) //�ڶ�����������������

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
    printf("\n��Ҫ��������Ϊ��\n");
    printsudoku(sudoku);
}