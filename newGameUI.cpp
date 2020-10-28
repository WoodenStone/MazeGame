
#include "Game.h"

extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器

void CnewGameUI::initialMenu()
{
	CButton* button = new CButton();

	int xClick, yClick;
	setbkmode(TRANSPARENT);
	
	for (; is_run(); delay_fps(60))
	{
		if (kbhit())	//键盘消息获取
		{
			ch_msg = getch();
			if (ch_msg == 27)	//按ESC退出
			{
				break;
			}
		}

		bool click_flag = false;
		while (mousemsg())	//鼠标消息获取
		{
			m_msg = getmouse();
			if (m_msg.is_left() && m_msg.is_down())	//存在左键点击事件
			{
				click_flag = true;
				xClick = m_msg.x;
				yClick = m_msg.y;
			}
		}

		button->drawBackground();	//绘制背景

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(60, 0, "微软雅黑");
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Star!");
		}
		setcolor(WHITE);
		setfont(60, 0, "微软雅黑");
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Star!");

		button->putButton_(250, 200, 400, 240, "NEW GAME");
		button->putButton_(250, 260, 400, 300, "LOAD GAME");
		button->putButton_(250, 320, 400, 360, "HELP");

		//开始新游戏
		if (click_flag && button->ifClick(xClick, yClick, 250, 200, 400, 240))
		{
			setbkcolor(WHITE);
		}

		//读取存档
		if (click_flag && button->ifClick(xClick, yClick, 250, 260, 400, 300))
		{
			setbkcolor(RED);
		}

		LOGFONT f;
		getfont(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setcolor(WHITE);

		//主页菜单文字
		outtextxy(340, 153, "V2.077");
		outtextxy(249, 440, "按ESC退出游戏");

		
	}

	delete button;
	button = NULL;
}