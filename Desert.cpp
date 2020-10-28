//Desert.cpp: ɳĮ��ͼ��ʹ�ã��㷨

#include "Game.h"


//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��

//���ƽ���
void CDesert::putRoom()
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

	//���������Թ�
	//����Χǽ
	//��Χǽ
	/*for (int i = x - 3; i <= x + 4; i++)
	{
		for (int j = y - 4; j <= y + 4; j+=2)
		{
			if (maze.map[i][j] == WALL) {
				setfillcolor(BLACK);
				setlinewidth(10);
				line((j-1-y)*50+266,(i-1-x)*50+266+25,(j-1-y)*50+266+50, (i - 1 - x) * 50 + 266 + 25);
			}
		}
	}
	//��Χǽ
	for (int i = x - 4; i <= x + 4; i ++)
	{
		for (int j = y - 3; j <= y + 4; j +=2)
		{
			if (maze.map[i][j] == WALL) {
				setlinewidth(10);
				line((j-1-y)*50+266+25,(i-1-x)*50+266, (j - 1 - y) * 50 + 266 + 25,(i-1-x)*50+266+50);
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
				//setfillcolor(EGERGB(0, 100, 0));
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_wall, 0, 0, 64,64);
			}
			else if (maze.map[i][j] == ROAD)
			{
				//setfillcolor(YELLOW);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_road, 0, 0, 64, 64);
			}
			else if (maze.map[i][j] == END)
			{
				//setfillcolor(BLUE);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_end, 0, 0, 64, 64);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				/*setfillcolor(YELLOW);
				bar((j - y) * 25 + 265, (i - x) * 25 + 265, (j -y-2) * 25 + 266, (i - x-2) * 25 + 266);
				setfillcolor(EGERGB(255,128,64));
				fillellipse((j-y-1)*25+265,(i-x-1)*25+265,25,25);*/
				//putimage((j - y) * 25 + 265, (i - x) * 25 + 265, 50, 50, pimg_forest_player, 0, 0, 59, 59);
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

//ɳĮstage����
void CDesert::mainGame()
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
	//myKLS();
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

			if (kbhit())		//������Ϣ��ȡ
				ch_msg = getch();

			//�����������־����Ϊfalse
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
			setfillcolor(EGERGB(255,222,173));
			bar(16, 17, 465, 465);

			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//��ť����
			button->putButton_(513, 400, 603,430,"�ص���ҳ");
			button->putButton_(513, 350, 603,380,"��ͣ");

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

// ð��ģʽ-ɳĮϵ����
// ���� DFS ��������Թ�
void CDesert::myKLS()
{
	//maze.size_m = 25;
	//maze.size_n = 25;
	setbkcolor(RED);
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