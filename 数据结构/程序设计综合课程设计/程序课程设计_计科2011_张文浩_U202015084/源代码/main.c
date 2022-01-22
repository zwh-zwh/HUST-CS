#include "SAT_SUDOKU.h"

int main() {
	srand(time(0));
	Total SATList = NULL;
	int sudoku[10][10] = { 0 }, dsudoku[10][10] = { 0 }, holes[10][10] = { 0 }, origin[100] = { 0 };
	FILE* fp;
	int op = 1, op1 = 1, op2 = 1, op3 = 1, dresult, temp1, temp2, temp3, holescount;
	double t1, t2;
	int n, m, k, i, j, flag = 0, flag1 = 0;
	while (op) { //һ���˵�
		system("cls");
		printf("\n               Menu for SUDOKU or SAT              \n");
		printf("------------------------------------------------------\n");
		printf("            1.SAT                  2.SUDOKU           \n");
		printf("            0.�˳�                                   \n");
		printf("------------------------------------------------------\n");
		printf("�����������0-2����\n");
		scanf("%d", &op);
		switch (op) {
		case 1: {
			op1 = 1;
			while (op1) { //�����˵�1
				system("cls");
				printf("\n              Menu for SAT                \n");
				printf("--------------------------------------------\n");
				printf("  1.����cnf�ļ�             2.�����ǰ�Ӿ伯  \n");
				printf("  3.��Ⲣ�����          4.����Ϊcnf�ļ� \n");
				printf("  5.���ٵ�ǰ�Ӿ伯          0.�˳�\n");
				printf("--------------------------------------------\n");
				scanf("%d", &op1);
				switch (op1) {
				case 1: {
					if (SATList != NULL)
						printf("�Ѷ���cnf�ļ��������ظ�����\n");
					else {
						printf("�����ļ���: ");
						scanf("%s", filename);
						strcpy(savefile, filename);//���渱��
						SATList = fileload(SATList, filename);
					}
					system("pause");
					break;
				}
				case 2: {
					if (SATList == NULL)
						printf("δ����cnf�ļ�\n");
					else {
						temp1 = Traverse(SATList);
						if (temp1 == 1)
							printf("����ɹ�\n");
						else
							printf("���ʧ��\n");
					}
					system("pause");
					break;
				}
				case 3: {
					if (SATList == NULL)
						printf("δ����cnf�ļ�\n");
					else {
						dresult = -1;
						printf("�����ɺ��Զ��������ɵ��Ӿ伯\n��ѡ���Ԫѡȡ���ԣ�\n1.��һ�Ӿ�ĵ�һ���� 2.�Ż��㷨\n");
						scanf("%d", &temp3);
						if (temp3 == 1) {
							t1 = clock();
							dresult = DPLL2(SATList);
							t2 = clock();
							SATList = NULL;
						}
						else if (temp3 == 2) {
							t1 = clock();
							dresult = DPLL1(SATList);
							t2 = clock();
							SATList = NULL;
						}
						printf("������\n\n");
						if (dresult) {
							printf("����һ�������£�\n");
							for (int i = 1; i <= varcount; i++) {
								if (result[i] == 1)
									printf("%d ", i);
								else
									printf("%d ", -i);
							}
							printf("\n\n�������ʱ��Ϊ%lfms\n\n", t2 - t1);
						}
						else if (dresult == 0) {
							printf("�������޽�\n");
							printf("\n�������ʱ��Ϊ%lfms\n\n", t2 - t1);
						}
						saveanswer(SATList, dresult, t2 - t1);
					}
					system("pause");
					break;
				}
				case 4: {
					if (SATList == NULL)
						printf("δ����cnf�ļ�\n");
					else
						savecnf(SATList);
					system("pause");
					break;
				}
				case 5: {
					if (SATList == NULL)
						printf("�Ӿ伯������\n");
					else
					{
						SATList = destroy(SATList);
						printf("�������\n");
					}
					system("pause");
					break;
				}
				case 0:
					break;
				default:
					printf("�������\n");
					system("pause");
					break;
				}
			}
			break;
		}
		case 2: {
			op2 = 1;
			while (op2) {
				//�����˵�2
				system("cls");
				printf("\n              Menu for Sudoku                \n");
				printf("-------------------------------------------\n");
				printf("     1.��������           2.��ʼ��Ϸ    \n");
				printf("     0.�˳�  \n");
				printf("-------------------------------------------\n");
				printf("�����������0-2����\n");
				scanf("%d", &op2);
				switch (op2) {
				case 1: {
					memset(sudoku, 0, sizeof(sudoku));
					memset(holes, 0, sizeof(holes));
					memset(dsudoku, 0, sizeof(dsudoku));
					memset(origin, 0, sizeof(origin));
					createsudoku2(sudoku, 1, 1);
					printf("\n��������Ϊ��\n");
					printsudoku(sudoku);
					printf("�������ڶ�����������Խ�࣬�Ѷ�Խ�ߣ����ɴ��������Խ����:\n"); //�������ɵ������Ļ������ڶ�
					scanf("%d", &holescount);
					for (i = 1; i <= 9; i++)
						for (j = 1; j <= 9; j++)
							dsudoku[i][j] = sudoku[i][j];
					allresult = 0;
					digholes(dsudoku, holescount, holes);
					system("pause");
					break;
				}
				case 2: {
					flag1 = 0;
					for (i = 1; i <= 9; i++)
					{
						for (j = 1; j <= 9; j++)
							if (dsudoku[i][j] == 0)
							{
								flag1 = 1;
								break;
							}
						if (flag1 == 1) break;
					}
					if (flag1 == 0)
					{
						printf("δ����������\n");
						system("pause");
					}
					else
					{
						op3 = 1;
						while (op3) {
							flag = 0;
							system("cls");
							printsudoku(dsudoku);
							printf("�ɲ���λ��Ϊ��\n");
							int count = 0;
							for (i = 1; i <= 9; i++)
								for (j = 1; j <= 9; j++)
									if (holes[i][j]) {
										printf("%d %d  ", i, j);
										origin[i * 10 + j] = 1;
										count++;
										if (count == 7) {
											printf("\n");
											count = 0;
										}
									}
							printf("\n");
							printf("1.��д����         2.ɾ������     \n"); //��ʼ��Ϸ
							printf("3.�鿴�𰸲��˳�   0.�˳�     \n");
							printf("�����������0-3����\n");
							scanf("%d", &op3);
							if (op3 == 1) {
								printf("���������������λ�ã��������������1-9�������1-9����\n");
								scanf("%d%d", &n, &m);
								if (m >= 1 && m <= 9 && n >= 1 && n <= 9 && dsudoku[n][m] != 0) {
									printf("��λ�ò�Ϊ��,�����²���\n");
									system("pause");
								}
								else if (m >= 1 && m <= 9 && n >= 1 && n <= 9 && dsudoku[n][m] == 0) {
									printf("��ѡ�������������ֵ��1-9����\n");
									scanf("%d", &k);
									dsudoku[n][m] = k;
								}
								else if (m < 1 || m > 9 || n < 1 || n > 9) {
									printf("����λ�ô���\n");
									system("pause");
								}
							}
							else if (op3 == 2) {
								printf("����������ɾ����λ�ã��������������1-9�������1-9��:\n");
								scanf("%d%d", &n, &m);
								if (m >= 1 && m <= 9 && n >= 1 && n <= 9) {
									if (dsudoku[n][m] == 0) {
										printf("��λ���Ѿ�Ϊ�գ�����ɾ��\n");
										system("pause");
									}
									else if (origin[n * 10 + m] == 0)
									{
										printf("��λ��Ϊԭʼ���ݣ�����ɾ��\n");
										system("pause");
									}
									else dsudoku[n][m] = 0;
								}
								else {
									printf("����λ������");
									system("pause");
								}
							}
							else if (op3 == 3) {
								for (i = 1; i <= 9; i++) {
									//�ж��û��������Ƿ���ȷ
									for (j = 1; j <= 9; j++)
										if (dsudoku[i][j] != sudoku[i][j]) {
											flag = 1;
											break;
										}
									if (flag == 1)
										break;
								}
								if (flag == 1) {
									printf("����д����������");
									printf("������ȷ�Ľ�Ϊ��\n");
								}
								else
									printf("������Ľ���ȷ��\n");
								printsudoku(sudoku);//�����ȷ��������
								system("pause");
								break;
							}
							else if (op3 == 0)
								break;
							else {
								printf("�������\n");
								system("pause");
							}
						}
					}
					break;
				}
				case 0:
					break;
				default:
					printf("�������\n");
					system("pause");
					break;
				}
			}
			break;
		}
		case 0:
			break;
		default:
			printf("�������\n");
			system("pause");
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´�ʹ�ñ�ϵͳ��\n");
	system("pause");
	return 0;
}//end of main()

