//Castle.cpp: �Ǳ���ͼ��ʹ�ã��㷨

#include "Game.h"


//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��

//���ƽ���
void CCastle::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50];	//��ʱ����ǰ�ؿ����ܹؿ�

	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass);
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times);

	//������ʽ����
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 85, time);

	//��ȡͼ����Դ
	PIMAGE pimg_castle_road = newimage();
	getimage(pimg_castle_road, "JPG", MAKEINTRESOURCEA(CASTLE_ROAD));
	PIMAGE pimg_castle_wall = newimage();
	getimage(pimg_castle_wall, "JPG", MAKEINTRESOURCEA(CASTLE_WALL));
	PIMAGE pimg_castle_player = newimage();
	getimage(pimg_castle_player, "JPG", MAKEINTRESOURCEA(CASTLE_PLAYER));
	PIMAGE pimg_castle_end = newimage();
	getimage(pimg_castle_end, "JPG", MAKEINTRESOURCEA(CASTLE_END));

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
				//setfillcolor(EGERGB(0, 100, 0));
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_wall, 0, 0, 128, 128);
			}
			else if (maze.map[i][j] == ROAD)
			{
				//setfillcolor(BROWN);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_road, 0, 0, 300, 300);
			}
			else if (maze.map[i][j] == END)
			{
				//setfillcolor(BLUE);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_end, 0, 0, 100, 100);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				//setfillcolor(BROWN);
				//bar((j - y) * 25 + 265, (i - x) * 25 + 265, (j - y - 2) * 25 + 266, (i - x - 2) * 25 + 266);
				//setfillcolor(YELLOW);
				//fillellipse((j - y - 1) * 25 + 265, (i - x - 1) * 25 + 265, 25, 25);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_player, 0, 0, 150, 150);
				x = i;
				y = j;
			}
		}
	}
		delimage(pimg_castle_road);
		delimage(pimg_castle_wall);
		delimage(pimg_castle_end);
		delimage(pimg_castle_player);
	
}

//�Ǳ�stage����
void CCastle::mainGame()
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

	int xClick = 0, yClick = 0;

	for (; is_run(); delay_fps(60))
	{
		//clear();//������ݺ���
		deepFS();
		
		x = 2;
		y = 2;//��������
		
		//���ó�ʼʱ��Ϊ0
		start_time = int(time(NULL));

		for (; is_run(); delay_fps(60))
		{
			//�ۼ�ʱ��
			times = int(time(NULL)) - start_time;

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

			man_Move();//�����ƶ�����

			if (x == maze.des_x && y == maze.des_y)
				break;			//�����յ��ж�

			//���Ʊ���
			button->drawBackground();

			//������Ϸ��
			setfillcolor(BLACK);
			bar(16, 17, 465, 465);

			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//��ť����
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
				}
				else {
					click_flag = false;
					xClick = 0, yClick = 0;
					start_time = int(time(NULL)) - t;
					times = t;
				}
			}

			if (button->ifClick(xClick, yClick, 513, 350, 603, 380))
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"����ȷ�����Ӵ���ͣ\n";
				do {
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"��ͣ", text, 1, 0)));
				start_time = int(time(NULL)) - t;
				times = t;
				//IMPORTANT!���ñ�־ֵ���ѻ�ȡ�����λ����Ϣ������ᵼ�½���ͣ������
				click_flag = false;
				xClick = 0, yClick = 0;
			}
		}

		//ͨ��һ�ؿ�
		if (oneLevelClear())
			break;
		//ͨ��ȫ�ؿ�
		if (single_pass==all_pass )
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

// ͼ�� DFS ��������Թ�
void CCastle::deepFS()
{
	maze.Nv = 0;						// �ڵ������
	//maze.size_m = 21;
	//maze.size_n = 21;

	for (int i = 1; i <= maze.size_n; i++)	// ��ʼ��
	{
		for (int j = 1; j <= maze.size_m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
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
	for (int i = 1; i <= maze.Nv; i++)
	{
		visit[i] = 0;
		if (i % ((maze.size_n - 1) / 2) != 0)
		{
			maze.reg[i][i + 1] = 1;
			maze.reg[i + 1][i] = 1;
		}
		if (i <= maze.Nv - (maze.size_n - 1) / 2)
		{
			maze.reg[i][i + (maze.size_n - 1) / 2] = 1;
			maze.reg[i + (maze.size_n - 1) / 2][i] = 1;
		}
	}

	dfs_search(maze.Nv);				// ����ͼ�� DFS ����

	for (int i = 1; i <= maze.Nv; i++)
	{
		for (int j = 1; j <= maze.Nv; j++)
		{
			if (maze.reg[i][j] == 2 || maze.reg[j][i] == 2)
			{
				Connect(flag[1][i], flag[2][i], flag[1][j], flag[2][j]);
			}
		}
	}
	maze.map[2][2] = YOU;
	if ((maze.size_n - 1) > 0 && maze.size_m > 0) {
		maze.map[maze.size_n - 1][maze.size_m] = END;	// ��ͼ�� DFS �����ʾ���Թ���
	}
}