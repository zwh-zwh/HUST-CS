#include "SAT_SUDOKU.h"

int main() {
	srand(time(0));
	Total SATList = NULL;
	int sudoku[10][10] = { 0 }, dsudoku[10][10] = { 0 }, holes[10][10] = { 0 }, origin[100] = { 0 };
	FILE* fp;
	int op = 1, op1 = 1, op2 = 1, op3 = 1, dresult, temp1, temp2, temp3, holescount;
	double t1, t2;
	int n, m, k, i, j, flag = 0, flag1 = 0;
	while (op) { //一级菜单
		system("cls");
		printf("\n               Menu for SUDOKU or SAT              \n");
		printf("------------------------------------------------------\n");
		printf("            1.SAT                  2.SUDOKU           \n");
		printf("            0.退出                                   \n");
		printf("------------------------------------------------------\n");
		printf("请输入操作（0-2）：\n");
		scanf("%d", &op);
		switch (op) {
		case 1: {
			op1 = 1;
			while (op1) { //二级菜单1
				system("cls");
				printf("\n              Menu for SAT                \n");
				printf("--------------------------------------------\n");
				printf("  1.读入cnf文件             2.输出当前子句集  \n");
				printf("  3.求解并保存答案          4.保存为cnf文件 \n");
				printf("  5.销毁当前子句集          0.退出\n");
				printf("--------------------------------------------\n");
				scanf("%d", &op1);
				switch (op1) {
				case 1: {
					if (SATList != NULL)
						printf("已读入cnf文件，不能重复读入\n");
					else {
						printf("输入文件名: ");
						scanf("%s", filename);
						strcpy(savefile, filename);//保存副本
						SATList = fileload(SATList, filename);
					}
					system("pause");
					break;
				}
				case 2: {
					if (SATList == NULL)
						printf("未读入cnf文件\n");
					else {
						temp1 = Traverse(SATList);
						if (temp1 == 1)
							printf("输出成功\n");
						else
							printf("输出失败\n");
					}
					system("pause");
					break;
				}
				case 3: {
					if (SATList == NULL)
						printf("未读入cnf文件\n");
					else {
						dresult = -1;
						printf("求解完成后自动销毁生成的子句集\n请选择变元选取策略：\n1.第一子句的第一文字 2.优化算法\n");
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
						printf("求解完成\n\n");
						if (dresult) {
							printf("其中一个答案如下：\n");
							for (int i = 1; i <= varcount; i++) {
								if (result[i] == 1)
									printf("%d ", i);
								else
									printf("%d ", -i);
							}
							printf("\n\n求解所用时间为%lfms\n\n", t2 - t1);
						}
						else if (dresult == 0) {
							printf("该算例无解\n");
							printf("\n求解所用时间为%lfms\n\n", t2 - t1);
						}
						saveanswer(SATList, dresult, t2 - t1);
					}
					system("pause");
					break;
				}
				case 4: {
					if (SATList == NULL)
						printf("未读入cnf文件\n");
					else
						savecnf(SATList);
					system("pause");
					break;
				}
				case 5: {
					if (SATList == NULL)
						printf("子句集不存在\n");
					else
					{
						SATList = destroy(SATList);
						printf("销毁完成\n");
					}
					system("pause");
					break;
				}
				case 0:
					break;
				default:
					printf("输入错误\n");
					system("pause");
					break;
				}
			}
			break;
		}
		case 2: {
			op2 = 1;
			while (op2) {
				//二级菜单2
				system("cls");
				printf("\n              Menu for Sudoku                \n");
				printf("-------------------------------------------\n");
				printf("     1.生成数独           2.开始游戏    \n");
				printf("     0.退出  \n");
				printf("-------------------------------------------\n");
				printf("请输入操作（0-2）：\n");
				scanf("%d", &op2);
				switch (op2) {
				case 1: {
					memset(sudoku, 0, sizeof(sudoku));
					memset(holes, 0, sizeof(holes));
					memset(dsudoku, 0, sizeof(dsudoku));
					memset(origin, 0, sizeof(origin));
					createsudoku2(sudoku, 1, 1);
					printf("\n数独终盘为：\n");
					printsudoku(sudoku);
					printf("请输入挖洞数量（数量越多，难度越高，生成待求解数独越慢）:\n"); //在已生成的数独的基础上挖洞
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
						printf("未生成数独！\n");
						system("pause");
					}
					else
					{
						op3 = 1;
						while (op3) {
							flag = 0;
							system("cls");
							printsudoku(dsudoku);
							printf("可操作位置为：\n");
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
							printf("1.填写数字         2.删除数字     \n"); //开始游戏
							printf("3.查看答案并退出   0.退出     \n");
							printf("请输入操作（0-3）：\n");
							scanf("%d", &op3);
							if (op3 == 1) {
								printf("请输入你想填入的位置（依次输入行序号1-9和列序号1-9）：\n");
								scanf("%d%d", &n, &m);
								if (m >= 1 && m <= 9 && n >= 1 && n <= 9 && dsudoku[n][m] != 0) {
									printf("该位置不为空,请重新操作\n");
									system("pause");
								}
								else if (m >= 1 && m <= 9 && n >= 1 && n <= 9 && dsudoku[n][m] == 0) {
									printf("请选择你想填入的数值（1-9）：\n");
									scanf("%d", &k);
									dsudoku[n][m] = k;
								}
								else if (m < 1 || m > 9 || n < 1 || n > 9) {
									printf("输入位置错误\n");
									system("pause");
								}
							}
							else if (op3 == 2) {
								printf("请输入你想删除的位置（依次输入行序号1-9和列序号1-9）:\n");
								scanf("%d%d", &n, &m);
								if (m >= 1 && m <= 9 && n >= 1 && n <= 9) {
									if (dsudoku[n][m] == 0) {
										printf("该位置已经为空，不能删除\n");
										system("pause");
									}
									else if (origin[n * 10 + m] == 0)
									{
										printf("该位置为原始数据，不能删除\n");
										system("pause");
									}
									else dsudoku[n][m] = 0;
								}
								else {
									printf("输入位置有误");
									system("pause");
								}
							}
							else if (op3 == 3) {
								for (i = 1; i <= 9; i++) {
									//判断用户的填入是否正确
									for (j = 1; j <= 9; j++)
										if (dsudoku[i][j] != sudoku[i][j]) {
											flag = 1;
											break;
										}
									if (flag == 1)
										break;
								}
								if (flag == 1) {
									printf("你填写的数独错误！");
									printf("数独正确的解为：\n");
								}
								else
									printf("你填入的解正确！\n");
								printsudoku(sudoku);//输出正确的数独解
								system("pause");
								break;
							}
							else if (op3 == 0)
								break;
							else {
								printf("输入错误\n");
								system("pause");
							}
						}
					}
					break;
				}
				case 0:
					break;
				default:
					printf("输入错误\n");
					system("pause");
					break;
				}
			}
			break;
		}
		case 0:
			break;
		default:
			printf("输入错误\n");
			system("pause");
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次使用本系统！\n");
	system("pause");
	return 0;
}//end of main()

