// Adventrue.cpp : 冒险模式类文件

#include "Game.h"	// 游戏头文件

// 全局变量

extern char ch_msg;						// 键盘消息
extern long long times, start_time;	// 计时器

// CAdventure 类函数实现

// 冒险模式核心
// 人物移动处理
void CAdventure::man_Move()
{

	if ((ch_msg == 'w' || ch_msg == 'W') && maze.map[x - 1][y] != WALL)		// 上移处理
	{
		maze.map[x - 1][y] = YOU;
		maze.map[x][y] = ROAD;
		x--;
		ch_msg = '#';									// 赋为其他值，防止人物持续移动
	}
	else if ((ch_msg == 's' || ch_msg == 'S') && maze.map[x + 1][y] != WALL)	// 下移处理
	{
		maze.map[x + 1][y] = YOU;
		maze.map[x][y] = ROAD;
		x++;
		ch_msg = '#';
	}
	else if ((ch_msg == 'a' || ch_msg == 'A')&& maze.map[x][y - 1] != WALL)	// 左移处理
		{
			maze.map[x][y - 1] = YOU;
			maze.map[x][y] = ROAD;
			y--;
			ch_msg = '#';
		}
		else if ((ch_msg == 'd'||ch_msg=='D') && maze.map[x][y + 1] != WALL)	// 右移处理
		{
			maze.map[x][y + 1] = YOU;
			maze.map[x][y] = ROAD;
			y++;
			ch_msg = '#';
		}
	
}

// 清空数据处理
void CAdventure::clear()
{
	for (int i = 1; i <= maze.size_n; i++)
	{
		for (int j = 1; j <= maze.size_m; j++)
		{
			maze.map[i][j] = WALL;
			maze.fmap[i][j] = WALL;
		}
	}
	for (int i = 1; i <= (maze.size_n + 1) / 2 * (maze.size_m + 1) / 2; i++)
	{
		for (int j = 1; j <= (maze.size_n + 1) / 2 * (maze.size_m + 1) / 2; j++)
		{
			maze.reg[i][j] = WALL;
			maze.feg[i][j] = WALL;
		}
	}
	for (int i = 1; i <= (maze.size_n + 1) / 2 * (maze.size_m + 1) / 2; i++)
	{
		for (int j = 0; j < 3; j++)
			flag[j][i] = 0;
		visit[i] = 0;
	}
}

//DFS搜索生成迷宫
void CAdventure::CreateMaze(int x, int y)
{
	int dir[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	int random[4];			//随机方向数组

	//四个方向随机
	for (int i = 0; i < 4; i++)
	{
		random[i] = rand() % 4;
		for (int j = 0; j < i; j++)
		{
			if (random[i] == random[j])
			{
				random[i] = rand() % 4;
				j = -1;
			}
		}
	}

	if (!Check(x, y))
	{
		return;
	}

	int back = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (maze.map[x + dir[i][0]][y + dir[i][1]] == ROAD)
		{
			back++;
		}
	}
	if (back >= 2)		//判断是否形成回路
	{
		back = 0;
		return;
	}

	maze.map[x][y] = ROAD;		//该点打通
	setbkcolor(RED);
	for (int i = 0; i <= 3; i++)
	{
		maze.fmap[x][y] = 1;			//标记
		CreateMaze(x + dir[random[i]][0], y + dir[random[i]][1]);
		maze.fmap[x][y] = 0;			//回溯
	}
	return;
}

//检查所走的点的位置信息
int CAdventure::Check(int x, int y)
{
	//检查数组下标是否越界
	if (x == 1 || y == 1 || x == maze.size_n || y == maze.size_m)
	{
		return 0;
	}
	//检查是否已经打通
	if (maze.map[x][y] == ROAD || maze.fmap[x][y] == 1)
	{
		return 0;
	}

}

//图论DFS搜索生成迷宫核心
void CAdventure::dfs_search(int step)
{
	int random[4];
	//四个方向随机
	for (int i = 0; i < 4; i++)
	{
		random[i] = rand() % 4;
		for (int j = 0; j < i; j++)
		{
			if (random[i] == random[j])
			{
				random[i] = rand() % 4;
				j = -1;
			}
		}
	}

	//随机化处理
	int temp = 0, cst[4];
	temp = step + 1;
	cst[random[0]] = step + 1;
	if (temp > maze.Nv)
		cst[random[0]] = step;

	temp = step - 1;
	cst[random[1]] = step - 1;
	if (temp < 1)
		cst[random[1]] = step;

	temp = step + (maze.size_n - 1) / 2;
	cst[random[2]] = step + (maze.size_n - 1) / 2;
	if (temp > maze.Nv)
		cst[random[2]] = step;

	temp = step - (maze.size_n - 1) / 2;
	cst[random[3]] = step - (maze.size_n - 1) / 2;
	if (temp < 1)
		cst[random[3]] = step;

	for (int i = 0; i <= 3; i++)
	{
		//是否打通以及是否走过
		if ((maze.reg[step][cst[i]] == 1 || maze.reg[cst[i]][step] == 1) && !visit[cst[i]])
		{
			maze.reg[step][cst[i]] = 2;	//标记打通
			maze.reg[cst[i]][step] = 2;	//移除当前迷宫单元与相邻迷宫单元的墙
			visit[cst[i]] = 1;			//标记已经走过
			visit[step] = 1;			//标记已经走过
			dfs_search(cst[i]);
		}
	}
}

//将两点之间进行联通
void CAdventure::Connect(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
			maze.map[x1][(y1 + y2) / 2] = ROAD;
	}
	else if (y1 == y2)
	{
		maze.map[(x1 + x2) / 2][y1] = ROAD;
		
	}
	return;
}