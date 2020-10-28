// Adventrue.cpp : ð��ģʽ���ļ�

#include "Game.h"	// ��Ϸͷ�ļ�

// ȫ�ֱ���

extern char ch_msg;						// ������Ϣ
extern long long times, start_time;	// ��ʱ��

// CAdventure �ຯ��ʵ��

// ð��ģʽ����
// �����ƶ�����
void CAdventure::man_Move()
{

	if ((ch_msg == 'w' || ch_msg == 'W') && maze.map[x - 1][y] != WALL)		// ���ƴ���
	{
		maze.map[x - 1][y] = YOU;
		maze.map[x][y] = ROAD;
		x--;
		ch_msg = '#';									// ��Ϊ����ֵ����ֹ��������ƶ�
	}
	else if ((ch_msg == 's' || ch_msg == 'S') && maze.map[x + 1][y] != WALL)	// ���ƴ���
	{
		maze.map[x + 1][y] = YOU;
		maze.map[x][y] = ROAD;
		x++;
		ch_msg = '#';
	}
	else if ((ch_msg == 'a' || ch_msg == 'A')&& maze.map[x][y - 1] != WALL)	// ���ƴ���
		{
			maze.map[x][y - 1] = YOU;
			maze.map[x][y] = ROAD;
			y--;
			ch_msg = '#';
		}
		else if ((ch_msg == 'd'||ch_msg=='D') && maze.map[x][y + 1] != WALL)	// ���ƴ���
		{
			maze.map[x][y + 1] = YOU;
			maze.map[x][y] = ROAD;
			y++;
			ch_msg = '#';
		}
	
}

// ������ݴ���
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

//DFS���������Թ�
void CAdventure::CreateMaze(int x, int y)
{
	int dir[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	int random[4];			//�����������

	//�ĸ��������
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
	if (back >= 2)		//�ж��Ƿ��γɻ�·
	{
		back = 0;
		return;
	}

	maze.map[x][y] = ROAD;		//�õ��ͨ
	setbkcolor(RED);
	for (int i = 0; i <= 3; i++)
	{
		maze.fmap[x][y] = 1;			//���
		CreateMaze(x + dir[random[i]][0], y + dir[random[i]][1]);
		maze.fmap[x][y] = 0;			//����
	}
	return;
}

//������ߵĵ��λ����Ϣ
int CAdventure::Check(int x, int y)
{
	//��������±��Ƿ�Խ��
	if (x == 1 || y == 1 || x == maze.size_n || y == maze.size_m)
	{
		return 0;
	}
	//����Ƿ��Ѿ���ͨ
	if (maze.map[x][y] == ROAD || maze.fmap[x][y] == 1)
	{
		return 0;
	}

}

//ͼ��DFS���������Թ�����
void CAdventure::dfs_search(int step)
{
	int random[4];
	//�ĸ��������
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

	//���������
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
		//�Ƿ��ͨ�Լ��Ƿ��߹�
		if ((maze.reg[step][cst[i]] == 1 || maze.reg[cst[i]][step] == 1) && !visit[cst[i]])
		{
			maze.reg[step][cst[i]] = 2;	//��Ǵ�ͨ
			maze.reg[cst[i]][step] = 2;	//�Ƴ���ǰ�Թ���Ԫ�������Թ���Ԫ��ǽ
			visit[cst[i]] = 1;			//����Ѿ��߹�
			visit[step] = 1;			//����Ѿ��߹�
			dfs_search(cst[i]);
		}
	}
}

//������֮�������ͨ
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