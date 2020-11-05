/*
Pincess.cpp: 
�ǿ��� ������ʷ������������Ϊprincess
���̿����߼������������Թ��㷨
by @WoodenStone
�����Թ� �ݹ�ָ�
by @Mango-wen
*/

#include "Game.h"

//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��
int GameLevel_star = 1;

//���ƽ���
void CPrincess::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//��ʱ����ǰ�ؿ����ܹؿ����Ѷȵȼ�

	swprintf_s(cur_pass, L"�� %d ��\0", single_pass);
	swprintf_s(tot_pass, L"�� %d ��\0", all_pass);
	swprintf_s(time, L"ʹ��ʱ�� %lld s\0", times);
	swprintf_s(gamelevel, L"�Ѷȵȼ���%d\0", GameLevel_star);

	//������ʽ����
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "΢���ź�");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	//���ñ���
	PIMAGE pimg_star_bg = newimage();
	getimage(pimg_star_bg, "JPG", MAKEINTRESOURCEA(STAR_BG));
	putimage(16, 17, 449, 482, pimg_star_bg, 0, 0, 1080, 1080);

	//��ȡͼ����Դ
	PIMAGE pimg_star_player = newimage();
	PIMAGE pimg_star_end = newimage();
	PIMAGE pimg_star_wall = newimage();
	
	getimage_pngfile(pimg_star_player, "images\\star_player.png");
	getimage_pngfile(pimg_star_end, "images\\star_end.png");
	getimage_pngfile(pimg_star_wall, "images\\star_wall.png");
	//ʹ��ͼƬ����洢��ͬ��WALL
	/*PIMAGE pimgs[6];
	char filename[30];
	for (int i = 0; i <= 5; i++)
	{
		sprintf(filename, "images\\star_wall%d.png", i + 1);
		pimgs[i] = newimage();
		getimage_pngfile(pimgs[i], filename);
	}*/

	//�����Թ�
	for (int i = x - 6; i <= x + 6; i++)
	{
		for (int j = y - 6; j <= y + 6; j++)
		{
			if (i < 1 || j < 1) {
				continue;
			}
			if (maze.map[i][j] == WALL)
			{
				putimage_withalpha(NULL, pimg_star_wall, (j - 1 - y) * 30 + 266, (i - 1 - x) * 30 + 266, 0, 0, 30, 30);

			}

			else if (maze.map[i][j] == END)
			{

				putimage_withalpha(NULL, pimg_star_end, (j - 1 - y) * 30 + 266, (i - 1 - x) * 30 + 266, 0, 0, 30, 30);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				putimage_withalpha(NULL, pimg_star_player, (j - 1 - y) * 30 + 266, (i - 1 - x) * 30 + 266, 0, 0, 30, 30);
				x = i;
				y = j;
			}
		}
	}

	delimage(pimg_star_bg);
	delimage(pimg_star_end);
	delimage(pimg_star_player);
	delimage(pimg_star_wall);
}

//Ӫ�ȹ���stage����
void CPrincess::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	//ģ���ʾ
	Stage.num = 4;
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

	switch (GameLevel_star) {
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
		GameLevel_star = 1;
		break;
	}

	int xClick = 0, yClick = 0;
	for (; is_run(); delay_fps(60))
	{
		clear();//������ݺ���

		maze.des_y=init();//�Թ����ɺ���
		maze.des_x = maze.size_n - 3;

		maze.map[maze.des_x][maze.des_y] = END;

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
			setbkcolor(EGERGB(51,51,102));
			//������Ϸ��
			setfillcolor(BLACK);
			bar(16, 17, 465, 465);

			//���Ƶ�ǰ��Ϸ����
			putRoom();

			//���ð�ť
			button->putButton_(513, 390, 603, 420, "�ص���ҳ");
			button->putButton_(513, 350, 603, 380, "��ͣ");
			button->putButton_(513, 310, 603, 340, "��ʾ·��");
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "�����Ѷ�");
			}
			//��ť����
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
				//setbkcolor(RED);
				flushkey();
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

					inputbox_getline("�������Ѷȵȼ�", "�����Ѷȵȼ�1~5,1Ϊ���,5Ϊ���\n������������س�", strbuff, buffsize);
					if (strbuff[0] == '\0')
					{
						error = false;
					}
					else if (strlen(strbuff) > 5) {
						ifInput = error = true;
					}
					else if (sscanf(strbuff, "%d", &GameLevel_star) == 1)
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
			break;
		//ͨ��ȫ�ؿ�
		if (single_pass==all_pass)
		{
			gameClear();
			break;
		}
		//��һ��
		single_pass++;
		maze.size_m += 9;
		maze.size_n += 9;
		if (maze.size_n > 99 || maze.size_m > 99)
		{
			maze.size_n = 99;
			maze.size_m = 99;
		}
	}
	delete(ad);
	ad = NULL;
	delete button;
	button = NULL;
}


//�����Թ��ĸ��Ӷȣ���ֵԽ���Ӷ�Խ�ͣ���СֵΪ0
//Ĭ��Ϊ���Ѷȣ��ɸ�����Ҫ��degree�����������ͬ�Ѷȵĸ��Ӷ�
int Rank = 6;

//CPrincess ����ʵ��

//��ʼ���Թ�
int CPrincess::init()
{
	int i,j;
	//maze.size_m = 25;
	//maze.size_n = 25;
	for (i = 0; i <= maze.size_n; i++)
	{
		for (j = 0; j <= maze.size_m; j++)
		{
			maze.map[i][j] = WALL;
		}
	}
	//����Χ��Ϊ·����Ϊ��ֹ��·ʱ�ڳ��߽磬Ϊ�����Թ��������һȦǽ�屻�ڴ�
	for (i = 0; i < maze.size_n; i++)
	{
		maze.map[i][0] = ROAD;
		if (maze.size_m >= 0) {
			maze.map[i][maze.size_m] = ROAD;
		}
	}
	for (i = 0; i < maze.size_m; i++)
	{
		maze.map[0][i] = ROAD;
		if (maze.size_n >= 0) {
			maze.map[maze.size_n][i] = ROAD;
		}
	}
	//�����Թ�����2,2��Ϊ���
	Create(2, 2);
	//���Թ�����ںͳ��ڣ�������ҳ�ʼλ��
	maze.map[2][2] = YOU;
	for (i = 0; i < maze.size_n; i++)
	{
		if (maze.size_m >= 0) {
			maze.map[i][maze.size_m] = WALL;
		}
	}
	for (i = 0; i < maze.size_m; i++)
	{
		if (maze.size_n >= 0) {
			maze.map[maze.size_n][i] = WALL;
		}
	}
	//�����㷨����ԣ�������һ�����ʲ��ڣ�n-3,m-2)������ʱ��ҪѰ�ҳ���
	for (int i = maze.size_n - 2; i >= 0; i--)
	{
		if (maze.size_m >= 3) {
			if (maze.map[i][maze.size_m - 3] == ROAD)
			{
				maze.map[i][maze.size_m - 2] = ROAD;
				//���س������ڵ�������
				return i;
			}
		}
	}
}

void CPrincess::Create(int x, int y)
{
	maze.map[x][y] = ROAD;
	int dir[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	int i, j;
	//ȷ���ĸ�������������ǹ̶�����������˳��
	for (i = 0; i < 4; i++)
	{
		int r = rand() % 4;
		int temp = dir[0][0];
		dir[0][0] = dir[r][0];
		dir[r][0] = temp;
		temp = dir[0][1];
		dir[0][1] = dir[r][1];
		dir[r][1] = temp;
	}
	//���ĸ�������
	for (int i = 0; i < 4; i++)
	{
		int dx = x;
		int dy = y;
		//�����ڵľ��룬��rank��������С
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range > 0)
		{
			//�������Ҫ���ʵ�������
			dx += dir[i][0];
			dy += dir[i][1];
			//�ų�����ͷ·
			if (maze.map[dx][dy] == ROAD)
				break;
			//�ж��Ƿ��ڴ�·��
			int count = 0, k;
			for (j = dx - 1; j < dx + 2; j++)
			{
				for (k = dy - 1; k < dy + 2; k++)
				{	//ȷ���ǾŹ�����ĸ�λ��
					if (abs(j - dx) + abs(k -dy) == 1 && maze.map[j][k] == ROAD)
						count++;
				}
			}
			//count����1����ǽ��ᱻ�ڴ���ֹͣ
			if (count > 1)
				break;
			//ȷ�������ڴ�ʱ��ǰ��
			range -= 1;
			maze.map[dx][dy] = ROAD;
		}
		//û���ڴ�Σ�գ��Դ�Ϊ�ڵ�ݹ�
		if (range <= 0) {
			Create(dx, dy);
		}
	}
}