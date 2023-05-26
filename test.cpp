#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <time.h>
#define ROW 10
#define COL 10
#define MINE_NUM 20
#define GRID_W 40
int cnt = 0;
int map[ROW][COL];
IMAGE img[12];
void gameInit()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MINE_NUM; i++)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++; 
		}
	}
	for(int i=0;i<ROW;i++)
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] ==-1)
			{
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = k - 1; c <= k + 1; c++)
					{
						if ((r >=0 && r<ROW && c>=0 && c<COL) && map[r][c]!=-1)
						{
							map[r][c]++;
						}
					}
				}
			}
		}
	}
	char str[50] = ""; 
	for (int i = 0; i < 12; i++)
	{
		sprintf(str, "./images/%d.jpg", i);
		loadimage(&img[i], str,GRID_W,GRID_W);
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			map[i][k] += 20;
		}
	}
}
void gameDraw()
{
	for (int i = 0; i < ROW; i++) //i->y,k->x
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] >=0&& map[i][k]<=8)
			{
				putimage(k * GRID_W, i * GRID_W, &img[map[i][k]]);
			}
			else if(map[i][k]==-1)
			{
				putimage(k * GRID_W, i * GRID_W, &img[9]);
			}
			else if (map[i][k] >= 19 && map[i][k] <= 28)
			{
				putimage(k * GRID_W, i * GRID_W, &img[10]);
			}
			else if (map[i][k] > 28)
			{
				putimage(k * GRID_W, i * GRID_W, &img[11]);
			}
		}
	}
}
void show();
void openNull(int row, int col);
void jude(int row, int col);
void mouseEvent()
{
	MOUSEMSG msg = GetMouseMsg();
	int row=msg.y / GRID_W;
	int col=msg.x / GRID_W;
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		if (map[row][col]>=19)
		{
			map[row][col] -= 20;
			cnt++;
			openNull(row, col);
			jude(row, col);
		}
	
	}
	else if (msg.uMsg == WM_RBUTTONDOWN)
	{
		if (map[row][col] >= 19 && map[row][col] <= 28)
		{
			map[row][col] += 20;
		}
		else if (map[row][col] > 28)
		{
			map[row][col] -= 20;
		}
		
	}
}
void openNull(int row,int col)
{
	if (map[row][col] == 0)
	{
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int k = col - 1; k <= col + 1; k++)
			{
				if ((i>0&&i<ROW&&k>=0&&k<COL)&&map[i][k]>19)
				{
					cnt++;
					map[i][k] -= 20;
					openNull(i, k);
				}
			}
		}
	}
}
void jude(int row, int col)
{
	if (map[row][col] == -1)
	{
		printf(" ‰¡À");
		exit(0);
	}
	if (cnt == ((ROW * ROW) - 10))
	{
		MessageBox(GetHWnd(), "you win", "∞ÀΩ‰", MB_OK);
	}
}
void show()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			printf("%2d ", map[i][k]);
		}
		printf("\n");
	}
}
int main()
{
	initgraph(COL*GRID_W, ROW*GRID_W,SHOWCONSOLE);
	gameInit();
	show();
	while (1)
	{
		gameDraw();
		mouseEvent();
	}
	system("pause");
}