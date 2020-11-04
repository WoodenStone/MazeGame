/*
newGameUI.cpp:实现初始化菜单
by @WoodenStone
*/

#include "Game.h"

extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器

//初始化菜单
void CnewGameUI::initialMenu()
{
	CButton* button = new CButton();
	CUI* graph = NULL;
	int xClick, yClick;
	setbkmode(TRANSPARENT);
	//获取背景图片
	PIMAGE pimg_bg = newimage();
	getimage(pimg_bg, "images\\bg.jpeg", 0, 0);
	for (; is_run(); delay_fps(60))
	{
		if (kbhit())	//键盘消息获取
		{
			ch_msg = getch();
			if (ch_msg == 27)	//按ESC退出
			{
				closegraph();
				exit(0);
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
		setbkcolor(WHITE);
		//带透明度绘制背景图片
		putimage_alphablend(NULL, pimg_bg, 0, 0, 128, 0, 0, 640, 480);
		//文字输出
		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setfont(60, 0, "Comic Sans MS", 0, 0, 500, 0, 0, 0, NULL);
			setcolor(WHITE);
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Stars!");
		}
		setfont(60, 0, "Comic Sans MS", 0, 0, 1000, 0, 0, 0, NULL);
		setcolor(EGERGB(250, 103, 122));
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Stars!");
		//按钮绘制
		button->putButton_(250, 240, 400, 280, "开始新游戏");
		button->putButton_(250, 320, 400, 360, "游戏帮助");

		//开始新游戏
		if (click_flag && button->ifClick(xClick, yClick, 250, 240, 400, 280))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			graph = new CUI();
			graph->mainMenu();
			delete graph;
			graph = NULL;

		}

		//点击帮助
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
		//字体参数设置
		LOGFONT f;
		getfont(&f);
		f.lfWidth = 8;
		f.lfWeight = 300;
		wcscpy_s(f.lfFaceName, L"华文彩云");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setcolor(EGERGB(250, 103, 122));

		//主页菜单文字
		outtextxy(340, 153, "V2.077");
		outtextxy(249, 440, "按ESC退出游戏");


	}
	delimage(pimg_bg);
	
	delete button;
	button = NULL;
}
