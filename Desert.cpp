/*
Desert.cpp:
���̿����߼������������Թ��㷨
by @WoodenStone
�����Թ� ����DFS
by @Mango-wen
*/

#include "Game.h"


//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��
int GameLevel_desert = 1;
//���ƽ���
void CDesert::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//��ʱ����ǰ�ؿ����ܹؿ����Ѷȵȼ�

	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass);
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times);
	swprintf_s(gamelevel, L"�Ѷȵȼ���%d\0", GameLevel_desert);
	//������ʽ����
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	/*���������Թ����ƣ������Թ���ͼ��������λ�û��ƣ�����λ��ʱ�̱䶯�����޷�ʵ��
	�����иô��룬����֡ѭ���������̬Ч������������ͼ��֤*/
	//��Χǽ
	/*for (int i = x - 5; i <= x + 5; i+=2)
	{
		for (int j = y - 4; j <= y + 4; j+=2)
		{
			if (maze.map[i][j] == WALL) {
				setfillcolor(WHITE);
				line((j - 1) * 50 + 25, i *50 + 25,(j + 1) * 50 + 25,i *50+ 25);
			}
		}
	}
	//��Χǽ
	for (int i = x - 4; i <= x + 4; i += 2)
	{
		for (int j = y - 5; j <= y + 5; j += 2)
		{
			if (maze.map[i][j] == WALL) {
				setfillcolor(WHITE);
				line(j * 50 + 25, (i-1) * 50 + 25, j * 50 + 25, (i+1) * 50 + 25);
			}
		}
	}*/

	//��ȡͼ����Դ
	PIMAGE pimg_desert_road = newimage();
	getimage(pimg_desert_road, "JPG", MAKEINTRESOURCEA(DESERT_ROAD));
	PIMAGE pimg_desert_wall = newimage();
	getimage(pimg_desert_wall, "JPG", MAKEINTRESOURCEA(DESERT_WALL));
	PIMAGE pimg_desert_player = newimage();
	getimage(pimg_desert_player, "JPG", MAKEINTRESOURCEA(DESERT_PLAYER));
	PIMAGE pimg_desert_end = newimage();
	getimage(pimg_desert_end, "JPG", MAKEINTRESOURCEA(DESERT_END));

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
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_wall, 0, 0, 64, 64);
			}
			else if (maze.map[i][j] == ROAD)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_road, 0, 0, 64, 64);
			}
			else if (maze.map[i][j] == END)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_end, 0, 0, 64, 64);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_player, 0, 0, 64, 64);
				x = i;
				y = j;
			}
		}
	}
	delimage(pimg_desert_player);
	delimage(pimg_desert_road);
	delimage(pimg_desert_wall);
	delimage(pimg_desert_end);
}

//ɳĮstage���ģ�������ɭ�ֻ���һ��
void CDesert::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	//ģ���ʶ
	Stage.num = 2;
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
	bool error = false;
	bool ifInput = false;

	switch (GameLevel_desert) {
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
		GameLevel_desert = 1;
		break;
	}
	int xClick = 0, yClick = 0;
	PIMAGE pimg_desert_bg = newimage();
	getimage(pimg_desert_bg, "images\\desert_bg.jpg", 0, 0);
	for (; is_run(); delay_fps(60))
	{
		//clear();//������ݺ���

		myKLS();//�Թ����ɺ���

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
			setbkcolor(EGERGB(255, 222, 173));
			//������Ϸ��
			putimage(16, 16, 450, 483, pimg_desert_bg, 0, 0, 1023, 719);
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
					delete ad;
					ad = NULL;
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
					else if (sscanf(strbuff, "%d", &GameLevel_desert) == 1)
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
		{
			break;
		}
		//ͨ��ȫ�ؿ�
		if (single_pass==all_pass )
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
	delimage(pimg_desert_bg);
	delete(ad);
	ad = NULL;
	delete button;
	button = NULL;
}

// ð��ģʽ-ɳĮϵ����
// ���� DFS ��������Թ�
void CDesert::myKLS()
{
	//maze.size_m = 25;
	//maze.size_n = 25;
	if (maze.size_m >= 1 && maze.size_n >= 1) {
	for (int i = 1; i <= maze.size_n; i++)	// ��ʼ��
	{
		for (int j = 1; j <= maze.size_m; j++)
		{
			maze.map[i][j] = WALL;
		}
	}
	}

	CreateMaze(maze.size_n - 1, maze.size_m - 1);
	maze.map[2][2] = YOU;
	if (maze.size_m >= 2 && maze.size_n >= 2) {
		maze.map[maze.size_n - 1][maze.size_m] = END;
		maze.map[2][3] = ROAD;
		maze.map[3][2] = ROAD;
		maze.map[maze.size_n - 1][maze.size_m - 1] = ROAD;
		maze.map[maze.size_n - 2][maze.size_m - 1] = ROAD;
		maze.map[maze.size_n - 1][maze.size_m - 2] = ROAD;		// ���� DFS ����
	}
}