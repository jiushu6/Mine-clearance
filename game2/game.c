#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisPlayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("-------扫雷游戏--------\n");
	//打印列号
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);

		}
		printf("\n");
	}
	printf("-------扫雷游戏--------\n");
}
 
void SetMine(char mine[ROWS][COLS], int row, int col)
{ 
	//布置10个雷
	int count = EASY_COUNT;
	while (count)
	{
		//生成随机下标
		int x = rand()% row + 1;
		int y = rand()% col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x + 1][y - 1] - 8 * '0';
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;


	while (win<row*col- EASY_COUNT)
	{
		printf("请输入要排除的坐标：>");
		scanf ("%d %d", &x, &y);//x-1-9,y-1-9
		//判断坐标的合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				printf("很遗憾，寄\n");
				DisPlayBoard(mine, row, col);
				break;
			}
			else
			{
				//不是雷情况下，统计x，y坐标旁边有没有雷，有几个雷
				int count = get_mine_count(mine, x, y);
				show[x][y] = count + '0';
				//显示排查出的信息
				DisPlayBoard(show, ROW, COL);
				win++;
			}
		}
		else
		{
			printf("坐标不合法，请重新输入\n");
		}
	}
	if(win==row*col- EASY_COUNT)
	{
		printf("排雷成功\n");
		DisPlayBoard(mine, ROW, COL);
	}
}