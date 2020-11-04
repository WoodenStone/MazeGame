/*
newGameUI.cpp:ʵ�ֳ�ʼ���˵�
by @WoodenStone
*/

#include "Game.h"

extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��

//��ʼ���˵�
void CnewGameUI::initialMenu()
{
	CButton* button = new CButton();
	CUI* graph = NULL;
	int xClick, yClick;
	setbkmode(TRANSPARENT);
	//��ȡ����ͼƬ
	PIMAGE pimg_bg = newimage();
	getimage(pimg_bg, "images\\bg.jpeg", 0, 0);
	for (; is_run(); delay_fps(60))
	{
		if (kbhit())	//������Ϣ��ȡ
		{
			ch_msg = getch();
			if (ch_msg == 27)	//��ESC�˳�
			{
				closegraph();
				exit(0);
			}
		}

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

		
		button->drawBackground();	//���Ʊ���
		setbkcolor(WHITE);
		//��͸���Ȼ��Ʊ���ͼƬ
		putimage_alphablend(NULL, pimg_bg, 0, 0, 128, 0, 0, 640, 480);
		//�������
		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setfont(60, 0, "Comic Sans MS", 0, 0, 500, 0, 0, 0, NULL);
			setcolor(WHITE);
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Stars!");
		}
		setfont(60, 0, "Comic Sans MS", 0, 0, 1000, 0, 0, 0, NULL);
		setcolor(EGERGB(250, 103, 122));
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Stars!");
		//��ť����
		button->putButton_(250, 240, 400, 280, "��ʼ����Ϸ");
		button->putButton_(250, 320, 400, 360, "��Ϸ����");

		//��ʼ����Ϸ
		if (click_flag && button->ifClick(xClick, yClick, 250, 240, 400, 280))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			graph = new CUI();
			graph->mainMenu();
			delete graph;
			graph = NULL;

		}

		//�������
		if (click_flag && button->ifClick(xClick, yClick, 250, 320, 400, 360))
		{
			do {
				gameHelp();
			} while (!getch());
				graph = new CUI();
				graph->mainMenu();
				delete graph;
				graph = NULL;
		}
		//�����������
		LOGFONT f;
		getfont(&f);
		f.lfWidth = 8;
		f.lfWeight = 300;
		wcscpy_s(f.lfFaceName, L"���Ĳ���");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setcolor(EGERGB(250, 103, 122));

		//��ҳ�˵�����
		outtextxy(340, 153, "V2.077");
		outtextxy(249, 440, "��ESC�˳���Ϸ");


	}
	delimage(pimg_bg);
	
	delete button;
	button = NULL;
}
