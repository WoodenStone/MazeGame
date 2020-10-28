
#include "Game.h"

extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ
extern long long times, start_time; //��ʱ��

void CnewGameUI::initialMenu()
{
	CButton* button = new CButton();

	int xClick, yClick;
	setbkmode(TRANSPARENT);
	
	for (; is_run(); delay_fps(60))
	{
		if (kbhit())	//������Ϣ��ȡ
		{
			ch_msg = getch();
			if (ch_msg == 27)	//��ESC�˳�
			{
				break;
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

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(60, 0, "΢���ź�");
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Star!");
		}
		setcolor(WHITE);
		setfont(60, 0, "΢���ź�");
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Star!");

		button->putButton_(250, 200, 400, 240, "NEW GAME");
		button->putButton_(250, 260, 400, 300, "LOAD GAME");
		button->putButton_(250, 320, 400, 360, "HELP");

		//��ʼ����Ϸ
		if (click_flag && button->ifClick(xClick, yClick, 250, 200, 400, 240))
		{
			setbkcolor(WHITE);
		}

		//��ȡ�浵
		if (click_flag && button->ifClick(xClick, yClick, 250, 260, 400, 300))
		{
			setbkcolor(RED);
		}

		LOGFONT f;
		getfont(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"΢���ź� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setcolor(WHITE);

		//��ҳ�˵�����
		outtextxy(340, 153, "V2.077");
		outtextxy(249, 440, "��ESC�˳���Ϸ");

		
	}

	delete button;
	button = NULL;
}