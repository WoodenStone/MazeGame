/*
Forest.cpp:
���̿����߼������������Թ��㷨
by @WoodenStone 
�����Թ� ���prim�㷨
by @Mango-wen
*/

#include "Game.h"
using namespace std;

//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��
int GameLevel_forest = 1;


//���ƽ���
void CForest::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50],gamelevel[20];	//��ʱ����ǰ�ؿ����ܹؿ����Ѷȵȼ�
	
	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass );
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times );
	swprintf_s(gamelevel, L"�Ѷȵȼ���%d\0", GameLevel_forest);

	//������ʽ����
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480,25,cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	//��ȡͼ����Դ
	PIMAGE pimg_forest_road = newimage();
	getimage(pimg_forest_road, "JPG", MAKEINTRESOURCEA(FOREST_ROAD));
	PIMAGE pimg_forest_wall = newimage();
	getimage(pimg_forest_wall, "JPG", MAKEINTRESOURCEA(FOREST_WALL));
	PIMAGE pimg_forest_player = newimage();
	getimage(pimg_forest_player, "JPG", MAKEINTRESOURCEA(FOREST_PLAYER));
	PIMAGE pimg_forest_end = newimage();
	getimage(pimg_forest_end, "JPG", MAKEINTRESOURCEA(FOREST_END));

	//�����Թ�
	for (int i = x - 4; i <= x + 4; i++)
	{
		for (int j = y - 4; j <= y + 4; j++)
		{
			if (i < 1 || j < 1) {
				continue;
			}
			if (maze.map[i][j] == WALL)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_forest_wall, 0, 0, 300, 300);
			}
			else if (maze.map[i][j] == ROAD)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_forest_road,0,0,300,300);
			}
			else if (maze.map[i][j] == END)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_forest_end, 0, 0, 98, 98);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_forest_player, 0, 0, 59, 59);
				x = i;
				y = j;
			}
		}
	}
	delimage(pimg_forest_player);
	delimage(pimg_forest_road);
	delimage(pimg_forest_wall);
	delimage(pimg_forest_end);
	
}

//ɭ��stage����
void CForest::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	//ģ���ʶ
	Stage.num = 1;
	bool ifhelped = false;
	//�趨��ťλ�ò���
	msgBoxPosition msg_back;
	msg_back.x = 120;
	msg_back.y = 165;
	msg_back.weight = 400;
	msg_back.height = 150;

	msgBoxPosition msg_Pause;
	msg_Pause.x = 170;
	msg_Pause.y = 165;
	msg_Pause.weight = 300;
	msg_Pause.height = 150;

	//��������
	const int buffsize = 10;
	char strbuff[150] = "";
	memset(strbuff, 0, sizeof(strbuff));
	bool error = false;
	bool ifInput = false;
	//�Ѷ�ѡ��
	switch (GameLevel_forest) {
	case 1:
		break;
	case 2:
		maze.size_m += 6;
		maze.size_n += 6;
		break;
	case 3:
		maze.size_m += 10;
		maze.size_n += 10;
		break;
	case 4:
		maze.size_m += 14;
		maze.size_n += 14;
		break;
	case 5:
		maze.size_m += 28;
		maze.size_n += 28;
		break;
	default:
		GameLevel_forest = 1;
		break;
	}

	int xClick=0, yClick=0;
	bool click_flag = false;
	PIMAGE pimg_forest_bg = newimage();
	getimage(pimg_forest_bg, "images\\forest_bg.jpg", 0, 0);
	//���̿���
	for (; is_run(); delay_fps(60))
	{
		clear();//������ݺ���

		prim();//�Թ����ɺ���

		x = 2;
		y = 2;//��������

		start_time = int(time(NULL));//���ó�ʼʱ��Ϊ0

		for (; is_run(); delay_fps(60))
		{
			times = int(time(NULL)) - start_time;//�ۼ�ʱ��

			ch_msg = (char)'#';	//��ռ�����Ϣ

			if (kbhit())	//������Ϣ��ȡ
				ch_msg = getch();
				

			click_flag = false;
			while (mousemsg())	//�����Ϣ��ȡ
			{
				m_msg = getmouse();
				if (m_msg.is_left() && m_msg.is_down())	//�����������¼�
				{
					click_flag = true;
					xClick = m_msg.x;
					yClick = m_msg.y;
				}
			}

			man_Move();			//�����ƶ�����

			if (x == maze.des_x && y == maze.des_y)
				break;			//�����յ��ж�

			//���Ʊ���
			button->drawBackground();
			setbkcolor(EGERGB(153, 204, 153));

			//������Ϸ��
			putimage(16, 16, 450, 483, pimg_forest_bg, 0, 0, 658, 494);

			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//���ư�ť
			button->putButton_(513, 390, 603, 420, "�ص���ҳ");
			button->putButton_(513, 350, 603, 380, "��ͣ");
			button->putButton_(513, 310, 603, 340, "��ʾ·��");
			//��һ��ʱ���Ը����Ѷ�
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "�����Ѷ�");
			}
			//����ص���ҳ
			if (button->ifClick(xClick, yClick, 513, 390, 603, 420))
			{
				long long t = times;
				flushkey();
				wchar_t* text[10];
				text[0] = L"ȷ���ص���ҳ��\n";
				
				if (button->putMessageBox(msg_back, L"�ص���ҳ", text, 1, MY_CHOICE))
				{
					delete button;
					button = NULL;
					return;
				}
				else {
					click_flag = false;
					xClick = 0, yClick = 0;
					start_time = int(time(NULL)) - t;
					times = t;
				}
			}

			//�����ͣ
			if (button->ifClick(xClick, yClick, 513, 350, 603, 380))
			{
				long long t1 = times;
				wchar_t* text[10];
				text[0] = L"����ȷ����������ͣ\n";
				do {
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"��ͣ", text, 1, 0)));

				start_time = int(time(NULL)) - t1;
				times = t1;
				//IMPORTANT!���ñ�־ֵ���ѻ�ȡ�����λ����Ϣ������ᵼ�½���ͣ������
				click_flag = false;
				xClick = 0, yClick = 0;
			}
			//��ʾ·��
			if (button->ifClick(xClick, yClick, 513, 310, 603, 340))
			{
				click_flag = false;
				xClick = 0, yClick = 0;

				long long t = times;
				//����һ����·����
				if (!ifhelped) {
					do {
						solveByQueue(maze.size_m, maze.size_n, Stage.num);
					} while (!(getch()));
					ifhelped = true;
				}
				else {
					do {
						outtextxy(60, 60, "�������һ�Σ�����������Ŭ��~\(�R���Q)/~");
					} while (!(getch()));
				}
				start_time = int(time(NULL)) - t;
				times = t;
				click_flag = false;
				xClick = 0, yClick = 0;
			}

			//ֻ�е�һ�ؿ��Ը����Ѷ�
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "�����Ѷ�");
				if (button->ifClick(xClick, yClick, 513, 430, 603, 460))
				{
					click_flag = false;
					xClick = 0, yClick = 0;
					//��ȡ�û�����
					inputbox_getline("�������Ѷȵȼ�", "�����Ѷȵȼ�1~5,1Ϊ���,5Ϊ���\n������������س�", strbuff, buffsize);
					
					if (strbuff[0] == '\0')
					{
						error = false;
					}
					else if (strlen(strbuff) > 5) {
						ifInput = true;
						error = true;
					}
					else if (sscanf(strbuff, "%d", &GameLevel_forest) == 1)
					{
						error = false;
						ifInput = true;
					}
					else {
						ifInput = true;
						error = true;
					}

					if (ifInput)
					{
						if (error)
						{
							setcolor(WHITE);
							xyprintf(100, 60, "�������");
							delay_ms(1000);
						}
						else
						{
							mainGame();
						}
					}
				}

			}
		}
		//ͨ��һ�ؿ�
		if (oneLevelClear())
			break;
		//ͨ��ȫ�ؿ�
		if (single_pass == all_pass)
		{
			gameClear();
			break;
		}
		//������һ��
		single_pass++;
		maze.size_m += 6;
		maze.size_n += 6;
		if (maze.size_n > 99 || maze.size_m > 99)
		{
			maze.size_n = 99;
			maze.size_m = 99;
		}
	}
	delimage(pimg_forest_bg);
	delete(ad);
	ad = NULL;
	delete button;
	button = NULL;
	
}

//Prim ��������Թ�
void CForest::prim()
{
	/* �ߵĽṹ�嶨�� */
	struct Edge
	{
		int head, tail;      /* �����<head,tail> */
	};
	maze.Nv = 0;				//�ڵ������
	maze.Ne = 0;
	//maze.size_n = 25;
	//maze.size_m = 25;

	std::vector <Edge> e;		//��ߵ���������
	
	for (int i = 1; i <= maze.size_n; i++)		//��ʼ��
	{
		for (int j = 1; j <= maze.size_m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0 && i != maze.size_n && j != maze.size_m)
			{
				maze.map[i][j] = ROAD;
				flag[0][++maze.Nv] = maze.Nv;
				flag[1][maze.Nv] = i;
				flag[2][maze.Nv] = j;
			}
			else
			{
				maze.map[i][j] = WALL;
			}
		}
	}

	//��ʼ���ڽӾ�������ɴ�
	for (int i = 1; i <= maze.Nv; i++)
	{
		for (int j = 1; j <= maze.Nv; j++)
		{
			maze.reg[i][j] = INF;
			maze.feg[i][j] = INF;
		}
	}

	for (int i = 1; i <= maze.Nv; i++)
	{
		visit[i] = 0;
		if (i % ((maze.size_n - 1) / 2) != 0)
		{
			maze.feg[i][i + 1] = 1;
			maze.feg[i + 1][i] = 1;
		}
		if (i <= maze.Nv - (maze.size_n - 1) / 2)
		{
			maze.feg[i][i + (maze.size_n - 1) / 2] = 1;
			maze.feg[i + (maze.size_n - 1) / 2][i] = 1;
		}
	}
	for (int i = 1; i <= maze.Nv; i++)
	{
		if (maze.feg[1][i] == 1)
		{
			Edge efo;
			efo.head = i;
			efo.tail = 1;
			e.push_back(efo);
		}
	}

	visit[1] = 1;
	//Prim �㷨����
	for (int i = 1; i <= maze.Nv - 1; i++)
	{
		std::random_shuffle(e.begin(), e.end());		//������Ԫ���������
		Edge arr;
		while (1) {
			arr = e.back();
			if (visit[arr.head] && visit[arr.tail])
			{
				e.pop_back();
			}
			else
			{
				break;
			}
		}
		e.pop_back();
		visit[arr.head] = 1;
		visit[arr.tail] = 1;
		maze.reg[arr.tail][arr.head] = 1;
		maze.reg[arr.head][arr.tail] = 1;	// ���ѡ�߲����

		for (int j = 1; j <= maze.Nv; j++)	// �����ѡ��
		{
			if (maze.feg[arr.head][j] == 1 && !visit[j])
			{
				Edge afo;
				afo.head = j;
				afo.tail = arr.head;
				e.push_back(afo);
			}
		}
	}

	for (int i = 1; i <= maze.Nv; i++)
	{
		for (int j = 1; j <= maze.Nv; j++)
		{
			if (maze.reg[i][j] == 1)
			{
				Connect(flag[1][i], flag[2][i], flag[1][j], flag[2][j]);
			}
		}
	}
	maze.map[2][2] = YOU;
	if (maze.size_n >= 1 && maze.size_m >= 0) {
		maze.map[maze.size_n - 1][maze.size_m] = END;	// �� Prim �����ʾ���Թ���
	}
}