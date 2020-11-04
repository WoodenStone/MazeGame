// Adventrue.cpp : ̽��ģʽ���ļ�
//by @Mango-wen

#include "Game.h"	// ��Ϸͷ�ļ�

using namespace std;
#include <queue>
#include <iostream>
#include <stack>
// ȫ�ֱ���

extern char ch_msg;						// ������Ϣ
extern long long times, start_time;	// ��ʱ��
int mark[1000][1000];
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int path[1000][1000];

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
	/*��������±��Ƿ�Խ��*/
	if (x == 1 || y == 1 || x == maze.size_n || y == maze.size_m)
	{
		return 0;
	}
	/*����Ƿ��Ѿ���ͨ*/
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
	
void CAdventure::printQueueSteps(int rows, int cols,int num) {
	/**��ʼ����·��*/
	int endX, endY;      // ��¼��������
	int i=0, j=0;            // ��ά���������
	int g=0, h=0;            //���ݵ�λ������
	int direction;      //��ǰ��Ϊ֮ǰ��ķ���
	// �ҵ��Թ����� 
	for (i = 1; i <= rows; i++)
	{
		for (j = 1; j <= cols; j++)
		{
			if (maze.map[i][j] == END)
			{
				g = endX = i;
				h = endY = j;
				direction = path[i][j]; /*�ҵ��������֮ǰ��ķ���*/
				break;
			}
		}
	}
	while (!(g == 2 && h == 2))
	{
		g = g - dir[direction][0]; /*δ�����ڣ�����֮ǰ��λ������*/
		h = h - dir[direction][1];
		direction = path[g][h];  /*���·���*/
		path[g][h] = -1;         /*�߹���·����path�б�־Ϊ�����ܵ�ֵ-1*/
	}
	if (num == 4) {
		for (i = x - 6; i <= x + 6; i++)
		{
			for (j = y - 6; j <= y + 6; j++)
			{
				if (path[i][j] == -1 && !(i == 2 && j == 2))
				{
					/*�߹���·�����Ϊ*������path[][]ҲΪ-1��Ҫ��ӡ@*/
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
					/*�߹���·�����Ϊ*������path[][]ҲΪ-1��Ҫ��ӡ@*/
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
	//path�������ڶ����пɼ�¼���б��������У���ǰ��Ϊ֮ǰ��ͨ��i����ִiΪdir�����е�0-3
	memset(path, 0, sizeof(path));
	int find = 0;       // ��¼�Ƿ�ﵽ���ڣ����Թ����ҵ�·��
	int i, j;            //��ά���������
	int g, h;            // ��ǰ�����еĶ�ͷλ��
	int tempG, tempH;    //��ǰλ����Χ�ĸ����������λ��
	
	std::queue<QueueNode> q;
	QueueNode temp, temp2;
	temp.x = 2;
	temp.y = 2;
	q.push(temp); // �ҵ���㣬����㿪ʼ��̽�����䷽����λ�����*/
	
	while (!q.empty()&&!find)   //�����зǿ�ʱ��δ�ҵ�ʱ����ִ�У������㷨������
	{
		//������ȡ��ͷλ�ã��ھ���mark[][]�б�Ƿ��ʹ���λ�á�
		temp = q.front();
		q.pop();
		mark[temp.x][temp.y] = 1;
		//������λ����Χ�ĸ�����
		for (i = 0; i <= 3; i++)
		{
			tempG = temp.x + dir[i][0];
			tempH = temp.y + dir[i][1];
			//����ͨ����δ���ʵ�λ������У���path[][]�м�¼��ʱ�ķ���
			if (maze.map[tempG][tempH] == ROAD && mark[tempG][tempH] == 0)
			{
				temp2.x = tempG;
				temp2.y = tempH;
				q.push(temp2);
				path[temp2.x][temp2.y] = i;
				mark[temp2.x][temp2.y] = 1;
			}
			//�����ҵ��յ㣬��ʼ����·���˳�
			if (maze.map[tempG][tempH] == END)
			{
				//setbkcolor(RED);
				temp2.x = tempG;
				temp2.y = tempH;
				q.push(temp2);
				path[tempG][tempH] = i;
				find = 1;   /*�������*/
			}
		}
	}
	/**�����Ƿ��ҵ�·�������Ӧ������*/
	if (find)
	{
		printQueueSteps(rows, cols,num);
		outtextxy(60, 60, "��������ƶ�");
	}
	else
	{
		//setbkcolor(BROWN);
		outtextxy(60, 60, "�������һ�Σ�����������Ŭ��~\(�R���Q)/~");
		return;
	}
}

void CAdventure::SolveByStack(int rows, int cols, int num) {
	/** ����ջ����Թ�·�� */
	memset(mark, 0, sizeof(mark));      //mark[][]��ʼ��Ϊ0,��δ������
	int dirCount;       //��̽���ķ���
	int dirTemp;        //����GetTop�з��صķ�����ʵ���ô�
	int find = 0;       //�Ƿ��Ѵﵽ���ڣ��ҵ�·��
	int i, j;            //��λ���������
	int g, h;            //Ϊ��ǰ̽���ĵ�λ������
	typedef struct StackNode {
		/* ջ�д洢�Ľڵ� **/
		int x;
		int y;
		int dirCount;   /*��ʾ��һ���ߵ��ò��ķ���*/
	}StackNode;

	StackNode temp;
	stack<StackNode> s;
	/** �ҵ���� */
	g = 2;
	h = 2;
	dirCount = 0;
	temp.x = g;
	temp.y = h;
	temp.dirCount = dirCount;
	s.push(temp);
	mark[g][h] = 1;
	while (!s.empty()) /*ջ����*/
	{
		g = g + dir[dirCount][0];   /*��һ����̽��Χλ��*/
		h = h + dir[dirCount][1];
		if (maze.map[g][h] == END && mark[g][h] == 0)
		{
			mark[g][h] = 1;
			temp.x = g;
			temp.y = h;
			temp.dirCount = dirCount;
			s.push(temp);
			find = 1;       /*�����յ㣬��ջ��find=1,�˳�ѭ��*/
			break;
		}
		if (maze.map[g][h] == ROAD && mark[g][h] == 0)/*��ǰλ�ÿ�ͨ�Ҳ�δ���ʹ�*/
		{
			mark[g][h] = 1;
			temp.x = g;
			temp.y = h;
			temp.dirCount = dirCount;
			s.push(temp);
			dirCount = 0;       /*������һ��֮ǰ�ı�dirCount = 0Ϊ��ʼ����*/
		}
		else if (dirCount < 3 && (!s.empty()))     /*��������������δ̽��*/
		{
			temp = s.top();
			g = temp.x;
			h = temp.y;
			dirTemp = temp.dirCount; /*�ò����ߣ�g,h����Ϊ��һ����ֵ*/
			dirCount += 1;        /*����Ϊ��һ����������̽*/
		}
		else
		{
			/*��ջ���յ�ջ��λ�����ܾ�����ͨ*/
			while ((dirCount == 3) && (!s.empty()))
			{
				temp = s.top();
				g = temp.x;
				h = temp.y;
				dirCount = temp.dirCount; /*�ò����ߣ�g,h����Ϊ��һ����ֵ*/
				s.pop();  /*g,h����ַ�������ò���λ�ú������һ������*/
				mark[g][h] = 0;    /*����ջ���ҽ�mark[][]���±��Ϊδ����*/
			}
			if (!s.empty())/*������������ͨ����λ�ã�ջ����*/
			{
				temp = s.top();
				g = temp.x;
				h = temp.y;
				dirTemp = temp.dirCount;
				dirCount += 1;       /*��һ������������̽*/
			}
		}
	}
	/**�����ҵ���������Ӧ�Ľ��*/
	if (find) {
		/** ���ջ����Թ�������·��*/
		memset(path, 0, sizeof(path)); //path�����¼ջ������Ԫ�أ����ҵ���·��

		StackNode temp;
		StackNode stackNode = s.top();
		s.pop();
		int i, j;
		//Tips:����ջ�õ������̣���������·��
		while (!s.empty())
		{
			temp = stackNode;   /*����ջ�г��ֵ�Ԫ��Ϊ·������path��¼*/
			path[stackNode.x][stackNode.y] = 1;
			stackNode = s.top();
			s.pop();
		}
		for (i = 1; i <= rows; i++)
		{
			for (j = 1; j <= cols; j++)
			{
				/*��ȥ����յ㣬·��ȫ��ӡΪ* */
				if (path[i][j])
				{
					setfillcolor(BLACK);
					fillellipse((j - y - 1) * 50 + 25 + 265, (i - x - 1) * 50 + 265 + 25, 10, 10);
				}
			}
		}
	}

}