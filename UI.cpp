/*
UI.cpp:ʵ��ͨ��һ�ؿ����桢ͨ��ȫ�ؿ����桢��ʼ�˵����桢��������
by @WoodenStone
*/

#include "Game.h"

//ȫ�ֱ���

extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��

class CAdventure;


void CUI::mainMenu()
{
	//����������
	CUI* MainUI=NULL;
	CForest* Forest = NULL;
	CDesert* Desert = NULL;
	CCastle* Castle = NULL;
	CPrincess* Princess = NULL;
	CButton* button = new CButton();

	int xClick, yClick;
	//���û�ͼģʽ
	setbkmode(TRANSPARENT);
	//��ȡ����ͼƬ
	PIMAGE pimg_bg = newimage();
	getimage(pimg_bg, "images\\bg.jpeg", 0, 0);

	for(;is_run();delay_fps(60))//��ⴰ������״̬
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
			
		//���Ʊ���
		button->drawBackground();	
		setbkcolor(WHITE);
		putimage_alphablend(NULL, pimg_bg, 0, 0, 128, 0, 0, 640, 480);
		//�����������
		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			
			setfont(60, 0, "Comic Sans MS",0,0,500,0,0,0,NULL);
			setcolor(WHITE);
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Stars!");
		}
		setfont(60, 0, "Comic Sans MS",0,0,1000,0,0,0,NULL);
		setcolor(EGERGB(250,103,122));
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Stars!");

		//���ư�ť
		button->putButton_(280, 200, 370, 230, "ɭ��");
		button->putButton_(280, 240, 370, 270, "ɳĮ");
		button->putButton_(280, 280, 370, 310, "�Ǳ�");
		button->putButton_(280, 320, 370, 350, "ժ����");

		//flushmouse();
		//ɭ��stage
		if (click_flag && button->ifClick(xClick, yClick, 280, 200, 370, 230))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Forest = new CForest();
			//�趨�Թ�����
			Forest->all_pass = 1;
			Forest->single_pass = 1;
			Forest->maze.size_n = 15;
			Forest->maze.size_m = 15;
			times = 0;
			Forest->mainGame();

			delete Forest;
			Forest = NULL;
		}
		//ɳĮ��
		if (click_flag && button->ifClick(xClick, yClick, 280, 240, 370, 270))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Desert = new CDesert();
			//�趨�Թ�����
			Desert->all_pass = 3;
			Desert->single_pass = 1;
			Desert->maze.size_n = 15;
			Desert->maze.size_m = 15;
			times = 0;
			Desert->mainGame();

			delete Desert;
			Desert = NULL;


		}

		//�Ǳ���
		if (click_flag && button->ifClick(xClick, yClick, 280, 280, 370, 310))
		{
			Castle = new CCastle();
			//�趨�Թ�����
			Castle->all_pass = 3;
			Castle->single_pass = 1;
			Castle->maze.size_n = 25;
			Castle->maze.size_m = 25;
			times = 0;
			Castle->mainGame();

			delete Castle;
			Castle = NULL;

		}
		//�ǿ���
		if (click_flag && button->ifClick(xClick, yClick, 280, 320, 370, 350))
		{
			Princess = new CPrincess();
			//�趨�Թ�����
			Princess->all_pass = 3;
			Princess->single_pass = 1;
			Princess->maze.size_n = 35;
			Princess->maze.size_m = 35;
			times = 0;
			Princess->mainGame();

			delete Princess;
			Princess = NULL;

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
	delete MainUI;
	MainUI = NULL;
}

//ͨ��һ�ؿ�����
bool CUI::oneLevelClear()
{
	CButton* button = new CButton();

	wchar_t title[50];

	msgBoxPosition msgBox;

	int xClick = 0, yClick = 0;
	flushkey();
	swprintf_s(title,L"��ʱ %lld s\0", times);

	for (; is_run(); delay_fps(60))
	{
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

		button->drawBackground();

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(52, 0, "����");
			outtextxy(140 + i, 90 + i, title);
		}
		setcolor(WHITE);
		setfont(52, 0, "����");
		outtextxy(140 + 3, 90 + 3, title);

		msgBox.x = 120;
		msgBox.y = 160;
		msgBox.weight = 400;
		msgBox.height = 150;

		//���ư�ť
		button->putButton_(273, 375, 363, 405, "��һ��");
		button->putButton_(273, 335, 363, 365, "�ص���ҳ");

		//����ص���ҳ
		if (button->ifClick(xClick, yClick, 273, 335, 363, 365))
		{
			wchar_t* text[10];
			text[0] = L"�Ƿ�ص���ҳ��\n";
			if (button->putMessageBox(msgBox, L"�ص���ҳ", text, 1, MY_CHOICE))
			{
				//setbkcolor(RED);
				delete button;
				button = NULL;
				return 1;
			}
			else {
				click_flag = false;
				xClick = 0, yClick = 0;
			}
		}
		//�����һ��
		if (button->ifClick(xClick, yClick, 273, 375, 363, 405))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			break;
		}
	}

	times = 0;
	delete button;
	button = NULL;
	return 0;
}

//ͨ��ȫ�ؿ�����
void CUI::gameClear()
{
	CButton* button = new CButton();
	int xClick = 0, yClick = 0;
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

		button->drawBackground();

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(110, 0, "��Բ");
			xyprintf(80 + i, 90 + i, "��ϲͨ��!");
		}
		setcolor(WHITE);
		setfont(110, 0, "��Բ");
		outtextxy(80 + 3, 90 + 3, "��ϲͨ��!");
		button->putButton_(273, 375, 363, 405, "�ص���ҳ");
		button->putButton_(273, 330, 363, 365, "�˳���Ϸ");

		if (button->ifClick(xClick, yClick, 273, 375, 363, 405))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			break;
		}

		//�˳���Ϸ
		if (button->ifClick(xClick, yClick, 273, 330, 363, 365))
		{
			delete button;
			button = NULL;
			closegraph();
			exit(0);
		}

	}

	delete button;
	button = NULL;
}

//��Ϸ����
void CUI::gameHelp()
{
		setfillcolor(EGERGB(187 ,255 ,255));
		bar(30, 30, 610, 450);
		//char str[2000]=@"��ӭ������ϷMazeGame: Get the Stars!\n����Ϸ����A��ҵ";
		setcolor(BLACK);
		outtextrect(40, 40, 570, 420, "��ӭ������ϷMazeGame: Get the Stars!\n"
			"\n"
			"����Ϸ��Ϊ�Ĵ�أ�ÿ�������ж�ʹ�ò�ͬ���㷨�����Թ���"
			"����Ϸ�У������ͨ��W A S D���������ڵ�ͼ���ƶ����������ƶ������½ǵĳ���ʱ����Ϊͨ�ء�\n"
			"\n"
			"����Ϸ�����У��������ʱ��ͣ��Ϸ���߻ص������棬�������ͨ��������û������ʱ���ǵõ��*��ʾ·��*���鿴ͨ��·����ʾŶ~"
			"��Ȼ��Ϊ����Ϸ�Կ��ǣ���һ���������ʾ���ɲ鿴һ�Σ������ʹ��Ӵ��~\n"
			"\n"
			"���⣬��ÿ�������ĵ�һ�أ�����Ե�����Ϸ�Ѷȣ��Ѷ���1��5������һ����ʼ���ô���ڱ㲻���ٵ����Ѷȡ�"
			"���ڣ�������ʼ��Ϸ�ɣ�\n"
			"\n"
			"�������������Ϸ��");
}