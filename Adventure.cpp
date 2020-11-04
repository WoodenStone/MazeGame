// Adventrue.cpp : 探索模式类文件
//by @Mango-wen

#include "Game.h"	// 游戏头文件

using namespace std;
#include <queue>
#include <iostream>
#include <stack>
// 全局变量

extern char ch_msg;						// 键盘消息
extern long long times, start_time;	// 计时器
int mark[1000][1000];
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int path[1000][1000];

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
	/*检查数组下标是否越界*/
	if (x == 1 || y == 1 || x == maze.size_n || y == maze.size_m)
	{
		return 0;
	}
	/*检查是否已经打通*/
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
	
void CAdventure::printQueueSteps(int rows, int cols,int num) {
	/**开始回溯路径*/
	int endX, endY;      // 记录出口坐标
	int i=0, j=0;            // 二维数组计数器
	int g=0, h=0;            //回溯的位置坐标
	int direction;      //当前点为之前点的方向
	// 找到迷宫出口 
	for (i = 1; i <= rows; i++)
	{
		for (j = 1; j <= cols; j++)
		{
			if (maze.map[i][j] == END)
			{
				g = endX = i;
				h = endY = j;
				direction = path[i][j]; /*找到出口相对之前点的方向*/
				break;
			}
		}
	}
	while (!(g == 2 && h == 2))
	{
		g = g - dir[direction][0]; /*未到出口，计算之前点位置坐标*/
		h = h - dir[direction][1];
		direction = path[g][h];  /*更新方向*/
		path[g][h] = -1;         /*走过的路径在path中标志为不可能的值-1*/
	}
	if (num == 4) {
		for (i = x - 6; i <= x + 6; i++)
		{
			for (j = y - 6; j <= y + 6; j++)
			{
				if (path[i][j] == -1 && !(i == 2 && j == 2))
				{
					/*走过的路径输出为*，起点的path[][]也为-1但要打印@*/
					setfillcolor(WHITE);
					fillellipse((j - y - 1) * 30 + 25 + 265, (i - x - 1) * 30 + 265 + 25, 3, 3);
				}
				else
				{
					continue;
				}
			}
			continue;
		}
	}
	else {
		for (i = x - 4; i <= x + 4; i++)
		{
			for (j = y - 4; j <= y + 4; j++)
			{
				if (path[i][j] == -1 && !(i == 2 && j == 2))
				{
					/*走过的路径输出为*，起点的path[][]也为-1但要打印@*/
					setfillcolor(WHITE);
					fillellipse((j - y - 1) * 50 + 25 + 265, (i - x - 1) * 50 + 265 + 25, 3, 3);
				}
				else
				{
					continue;
				}
			}
			continue;
		}
	}
}


void CAdventure::solveByQueue(int rows, int cols,int num) {
	//setbkcolor(RED);
	memset(mark, 0, sizeof(mark));
	//path矩阵用在队列中可记录队列遍历过程中，当前点为之前点通过i方向抵达，i为dir矩阵中的0-3
	memset(path, 0, sizeof(path));
	int find = 0;       // 记录是否达到出口，在迷宫中找到路径
	int i, j;            //二维数组计数器
	int g, h;            // 当前出队列的队头位置
	int tempG, tempH;    //当前位置周围四个方向的坐标位置
	
	std::queue<QueueNode> q;
	QueueNode temp, temp2;
	temp.x = 2;
	temp.y = 2;
	q.push(temp); // 找到起点，从起点开始试探，将其方向与位置入队*/
	
	while (!q.empty()&&!find)   //当队列非空时且未找到时继续执行，否则算法结束。
	{
		//出队列取队头位置，在矩阵mark[][]中标记访问过该位置。
		temp = q.front();
		q.pop();
		mark[temp.x][temp.y] = 1;
		//遍历该位置周围四个方向
		for (i = 0; i <= 3; i++)
		{
			tempG = temp.x + dir[i][0];
			tempH = temp.y + dir[i][1];
			//将可通行且未访问的位置入队列，在path[][]中记录此时的方向
			if (maze.map[tempG][tempH] == ROAD && mark[tempG][tempH] == 0)
			{
				temp2.x = tempG;
				temp2.y = tempH;
				q.push(temp2);
				path[temp2.x][temp2.y] = i;
				mark[temp2.x][temp2.y] = 1;
			}
			//若已找到终点，则开始回溯路径退出
			if (maze.map[tempG][tempH] == END)
			{
				//setbkcolor(RED);
				temp2.x = tempG;
				temp2.y = tempH;
				q.push(temp2);
				path[tempG][tempH] = i;
				find = 1;   /*到达出口*/
			}
		}
	}
	/**根据是否找到路径输出对应的内容*/
	if (find)
	{
		printQueueSteps(rows, cols,num);
		outtextxy(60, 60, "按任意键移动");
	}
	else
	{
		//setbkcolor(BROWN);
		outtextxy(60, 60, "机会仅有一次，请少侠继续努力~\(≧▽≦)/~");
		return;
	}
}

void CAdventure::SolveByStack(int rows, int cols, int num) {
	/** 运用栈求解迷宫路径 */
	memset(mark, 0, sizeof(mark));      //mark[][]初始化为0,均未被访问
	int dirCount;       //已探索的方向
	int dirTemp;        //用于GetTop中返回的方向，无实际用处
	int find = 0;       //是否已达到出口，找到路径
	int i, j;            //二位数组计数器
	int g, h;            //为当前探索的的位置坐标
	typedef struct StackNode {
		/* 栈中存储的节点 **/
		int x;
		int y;
		int dirCount;   /*表示上一步走到该步的方向*/
	}StackNode;

	StackNode temp;
	stack<StackNode> s;
	/** 找到起点 */
	g = 2;
	h = 2;
	dirCount = 0;
	temp.x = g;
	temp.y = h;
	temp.dirCount = dirCount;
	s.push(temp);
	mark[g][h] = 1;
	while (!s.empty()) /*栈不空*/
	{
		g = g + dir[dirCount][0];   /*下一步试探周围位置*/
		h = h + dir[dirCount][1];
		if (maze.map[g][h] == END && mark[g][h] == 0)
		{
			mark[g][h] = 1;
			temp.x = g;
			temp.y = h;
			temp.dirCount = dirCount;
			s.push(temp);
			find = 1;       /*到达终点，入栈并find=1,退出循环*/
			break;
		}
		if (maze.map[g][h] == ROAD && mark[g][h] == 0)/*当前位置可通且并未访问过*/
		{
			mark[g][h] = 1;
			temp.x = g;
			temp.y = h;
			temp.dirCount = dirCount;
			s.push(temp);
			dirCount = 0;       /*进行下一步之前改变dirCount = 0为初始方向*/
		}
		else if (dirCount < 3 && (!s.empty()))     /*还有其他方向尚未探索*/
		{
			temp = s.top();
			g = temp.x;
			h = temp.y;
			dirTemp = temp.dirCount; /*该步不走，g,h返回为上一步的值*/
			dirCount += 1;        /*更改为下一个方向再试探*/
		}
		else
		{
			/*若栈不空但栈顶位置四周均不可通*/
			while ((dirCount == 3) && (!s.empty()))
			{
				temp = s.top();
				g = temp.x;
				h = temp.y;
				dirCount = temp.dirCount; /*该步不走，g,h返回为上一步的值*/
				s.pop();  /*g,h传地址，弹出该步的位置和相对上一步方向*/
				mark[g][h] = 0;    /*弹出栈顶且将mark[][]重新标记为未访问*/
			}
			if (!s.empty())/*弹出几个不可通过的位置，栈不空*/
			{
				temp = s.top();
				g = temp.x;
				h = temp.y;
				dirTemp = temp.dirCount;
				dirCount += 1;       /*下一个方向重新试探*/
			}
		}
	}
	/**根据找到与否输出对应的结果*/
	if (find) {
		/** 输出栈求解迷宫经过的路径*/
		memset(path, 0, sizeof(path)); //path矩阵记录栈弹出的元素，即找到的路径

		StackNode temp;
		StackNode stackNode = s.top();
		s.pop();
		int i, j;
		//Tips:遍历栈得到求解过程，即经过的路径
		while (!s.empty())
		{
			temp = stackNode;   /*有在栈中出现的元素为路径，用path记录*/
			path[stackNode.x][stackNode.y] = 1;
			stackNode = s.top();
			s.pop();
		}
		for (i = 1; i <= rows; i++)
		{
			for (j = 1; j <= cols; j++)
			{
				/*除去起点终点，路径全打印为* */
				if (path[i][j])
				{
					setfillcolor(BLACK);
					fillellipse((j - y - 1) * 50 + 25 + 265, (i - x - 1) * 50 + 265 + 25, 10, 10);
				}
			}
		}
	}

}