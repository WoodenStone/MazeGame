/*
Castle.cpp:
���̿����߼������������Թ��㷨
by @WoodenStone
�����Թ� ͼ��DFS
by @Mango-wen
*/


#include "Game.h"


//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��
int GameLevel_castle = 1;

//���ƽ���
void CCastle::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//��ʱ����ǰ�ؿ����ܹؿ����Ѷȵȼ�

	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass);
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times);
	swprintf_s(gamelevel, L"�Ѷȵȼ���%d\0", GameLevel_castle);

	//������ʽ����
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

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
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_wall, 0, 0, 128, 128);
			}
			else if (maze.map[i][j] == ROAD)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_road, 0, 0, 300, 300);
			}
			else if (maze.map[i][j] == END)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_end, 0, 0, 100, 100);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
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
	CAdventure* ad = new CAdventure();
	bool ifhelped = false;
	//ģ���ʶ
	Stage.num = 3;
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

	switch (GameLevel_castle) {
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
		GameLevel_castle = 1;
		break;
	}

	int xClick = 0, yClick = 0;
	PIMAGE pimg_castle_bg = newimage();
	getimage(pimg_castle_bg, "images\\castle_bg.jpg", 0, 0);
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

			if (kbhit())	//������Ϣ��ȡ
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
			setbkcolor(EGERGB(102,110,147));

			//������Ϸ��
			putimage(16, 16, 450, 483, pimg_castle_bg, 0, 0, 734, 536);
			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//��ť����
			button->putButton_(513, 390, 603, 420, "�ص���ҳ");
			button->putButton_(513, 350, 603, 380, "��ͣ");
			button->putButton_(513, 310, 603, 340, "��ʾ·��");
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "�����Ѷ�");
			}
			//����ص���ҳ
			if (button->ifClick(xClick, yClick, 513, 390, 603, 420))
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
			//pause
			if (button->ifClick(xClick, yClick, 513, 350, 603, 380))
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"����ȷ����������ͣ\n";
				do {
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"��ͣ", text, 1, 0)));
				start_time = int(time(NULL)) - t;
				times = t;
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
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "�����Ѷ�");
				if (button->ifClick(xClick, yClick, 513, 430, 603, 460))
				{
					click_flag = false;
					xClick = 0, yClick = 0;
					inputbox_getline("�������Ѷȵȼ�", "�����Ѷȵȼ�1~5,1Ϊ���,5Ϊ���\n������������س�", strbuff, buffsize);
					if (strbuff[0] == '\0')
					{
						error = false;
					}
					else if (strlen(strbuff) > 5) {
						ifInput = error = true;
					}
					else if (sscanf(strbuff, "%d", &GameLevel_castle) == 1)
					{
						error = false;
						ifInput = true;
					}
					else {
						ifInput = error = true;
					}

					if (ifInput)
					{
						if (error)
						{
							outtextxy(100, 60, "�������");
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
		//��һ��
		single_pass++;
		maze.size_m += 6;
		maze.size_n += 6;
		if (maze.size_n > 99 || maze.size_m > 99)
		{
			maze.size_n = 99;
			maze.size_m = 99;
		}
	}
	delimage(pimg_castle_bg);
	delete(ad);
	ad = NULL;
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