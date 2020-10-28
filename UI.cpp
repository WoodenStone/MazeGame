//UI.cpp:实1现通过一关卡界面、通过全关卡界面、初始菜单界面

#include "Game.h"

//全局变量

extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器

class CAdventure;

void CUI::mainMenu()
{
	CUI* MainUI=NULL;
	CForest* Forest = NULL;
	CDesert* Desert = NULL;
	CCastle* Castle = NULL;
	CPrincess* Princess = NULL;
	CButton* button = new CButton();
	//帮助 tbc
	int xClick, yClick;
	setbkmode(TRANSPARENT);

	for(;is_run();delay_fps(60))
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
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Stars!");
		}
		setcolor(WHITE);
		setfont(60, 0, "微软雅黑");
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Stars!");


		button->putButton_(280, 200, 370,230,"森林");
		button->putButton_(280, 240, 370, 270, "沙漠");
		button->putButton_(280, 280, 370, 310, "城堡");
		button->putButton_(280, 320, 370, 350, "摘星星");

		//flushmouse();
		//进入森林类
		if (click_flag&&button->ifClick(xClick,yClick,280,200,370,230))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Forest = new CForest();
			Forest->all_pass = 2;
			Forest->single_pass = 1;
			Forest->maze.size_n = 15;
			Forest->maze.size_m = 15;
			times = 0;
			Forest->mainGame();

			delete Forest;
			Forest = NULL;
		}
		//沙漠类
		if (click_flag&&button->ifClick(xClick,yClick,280,240,370,270))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Desert = new CDesert();
			Desert->all_pass = rand() % 50 + 25;
			Desert->single_pass = 1;
			Desert->maze.size_n = 15;
			Desert->maze.size_m = 15;
			times = 0;
			Desert->mainGame();
			
			delete Desert;
			Desert = NULL;


		}
		
		//城堡类
		if (click_flag&&button->ifClick(xClick,yClick,280,280,370,310))
		{
			Castle = new CCastle();
			Castle->all_pass = rand() % 50 + 25;
			Castle->single_pass = 1;
			Castle->maze.size_n = 15;
			Castle->maze.size_m = 15;
			times = 0;
			Castle->mainGame();

			delete Castle;
			Castle = NULL;

		}

		if (click_flag && button->ifClick(xClick,yClick,280,320,370,350))
		{
			Princess = new CPrincess();
			Princess->all_pass = rand() % 50 + 25;
			Princess->single_pass = 1;
			Princess->maze.size_n = 15;
			Princess->maze.size_m = 15;
			times = 0;
			Princess->mainGame();

			delete Princess;
			Princess = NULL;

		}
		/*if (button->putButton(280, 420, "帮助"))
		{
			//tbc

		}*/

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

		//api_sleep(5);

	}
	delete button;
	button = NULL;
	delete MainUI;
	MainUI = NULL;
}

//通过一关卡界面
bool CUI::oneLevelClear()
{
	CButton* button = new CButton();

	wchar_t title[50];

	msgBoxPosition msgBox;

	int xClick = 0, yClick = 0;

	swprintf_s(title,L"用时 %lld s\0", times);

	for(;is_run();delay_fps(60))
	{
		if (kbhit())		//键盘消息获取
			ch_msg = getch();

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
		
		button->drawBackground();

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(52, 0, "黑体");
			outtextxy(140 + i, 90 + i, title);
		}
		setcolor(WHITE);
		setfont(52, 0, "黑体");
		outtextxy(140 + 3, 90 + 3, title);

		msgBox.x = 120;
		msgBox.y = 160;
		msgBox.weight = 400;
		msgBox.height = 150;

		//绘制按钮
		button->putButton_(273, 375, 363,405,"下一关");
		button->putButton_(273, 335,363,365, "回到主页");

		//点击回到主页
		if (button->ifClick(xClick,yClick,273,335,363,365))
		{
			wchar_t* text[10];
			text[0] = L"是否回到主页？\n";
			if (button->putMessageBox(msgBox, L"回到主页", text, 1, MY_CHOICE))
			{
				setbkcolor(RED);
				delete button;
				button = NULL;
				return 1;
			}
			else {
				click_flag = false;
				xClick = 0, yClick = 0;
			}
		}
		//点击下一关
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

//通过全关卡画面
void CUI::gameClear()
{
	CButton* button = new CButton();
	int xClick = 0, yClick = 0;
	for(;is_run();delay_fps(60))
	{
		if (kbhit())		//键盘消息获取
			ch_msg = getch();

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

		button->drawBackground();

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(70, 0, "Consolas");
			xyprintf(80 + i, 90 + i, "Congratulations!");
		}
		setcolor(WHITE);
		setfont(70, 0, "Consolas");
		outtextxy(80 + 3, 90 + 3, "Congratulations!");

		button->putButton_(273, 215, 373,245,"回到主页");
		button->putButton_(273, 300,373,330,"退出游戏");

		if (button->ifClick(xClick, yClick, 273, 215, 373, 245))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			break;
		}
			

		if (button->ifClick(xClick,yClick,273,300,373,330))
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