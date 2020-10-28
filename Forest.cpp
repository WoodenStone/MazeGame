//Forest.cpp: ɭ�ֵ�ͼ��ʹ�ã��㷨

#include "Game.h"
using namespace std;

//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��



//���ƽ���
void CForest::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50];	//��ʱ����ǰ�ؿ����ܹؿ�
	
	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass );
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times );

	//������ʽ����
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480,25,cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 85, time);

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

	int xClick=0, yClick=0;

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

			if (kbhit())		//������Ϣ��ȡ
				ch_msg = getch();

			bool click_flag = false;
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

			//������Ϸ��
			setfillcolor(EGERGB(100, 100, 100));
			bar(16, 17, 465, 465);

			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//���ư�ť
			button->putButton_(513, 400, 603, 430, "�ص���ҳ");
			button->putButton_(513, 350, 603, 380, "��ͣ");

			//����ص���ҳ
			if (button->ifClick(xClick, yClick, 513, 400, 603, 430))
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"ȷ���ص���ҳ��\n";

				if (button->putMessageBox(msg_back, L"�ص���ҳ", text, 1, MY_CHOICE))
				{
					delete button;
					button = NULL;
					return;
				}else{
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
				//button->putButton_(513, 350, 603,380,"��ͣ");
				do{
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"��ͣ", text, 1, 0)));
				
				start_time = int(time(NULL)) - t1;
				times = t1;
				//IMPORTANT!���ñ�־ֵ���ѻ�ȡ�����λ����Ϣ������ᵼ�½���ͣ������
				click_flag = false;
				xClick = 0, yClick = 0;
			}
			//api_sleep(5);
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
			//��һ��
			single_pass++;
			maze.size_m += 2;
			maze.size_n += 2;
			if (maze.size_n > 99 || maze.size_m > 99)
			{
				maze.size_n = 99;
				maze.size_m = 99;
			}
		
	}
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
	if (maze.size_n >= 1) {
		maze.map[maze.size_n - 1][maze.size_m] = END;	// �� Prim �����ʾ���Թ���
	}
}