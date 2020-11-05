/*
UI.cpp:实现通过一关卡界面、通过全关卡界面、初始菜单界面、帮助界面
by @WoodenStone
*/

#include "Game.h"

//全局变量

extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器

class CAdventure;


void CUI::mainMenu()
{
	//声明类引用
	CUI* MainUI=NULL;
	CForest* Forest = NULL;
	CDesert* Desert = NULL;
	CCastle* Castle = NULL;
	CPrincess* Princess = NULL;
	CButton* button = new CButton();

	int xClick, yClick;
	//设置绘图模式
	setbkmode(TRANSPARENT);
	//读取背景图片
	PIMAGE pimg_bg = newimage();
	getimage(pimg_bg, "images\\bg.jpeg", 0, 0);

	for(;is_run();delay_fps(60))//检测窗口运行状态
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
			
		//绘制背景
		button->drawBackground();	
		setbkcolor(WHITE);
		putimage_alphablend(NULL, pimg_bg, 0, 0, 128, 0, 0, 640, 480);
		//输出标题文字
		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			
			setfont(60, 0, "Comic Sans MS",0,0,500,0,0,0,NULL);
			setcolor(WHITE);
			outtextxy(30 + i, 60 + i, "MazeGame: Get the Stars!");
		}
		setfont(60, 0, "Comic Sans MS",0,0,1000,0,0,0,NULL);
		setcolor(EGERGB(250,103,122));
		outtextxy(30 + 1, 60 + 1, "MazeGame: Get the Stars!");

		//绘制按钮
		button->putButton_(280, 200, 370, 230, "森林");
		button->putButton_(280, 240, 370, 270, "沙漠");
		button->putButton_(280, 280, 370, 310, "城堡");
		button->putButton_(280, 320, 370, 350, "摘星星");

		//flushmouse();
		//森林stage
		if (click_flag && button->ifClick(xClick, yClick, 280, 200, 370, 230))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Forest = new CForest();
			//设定迷宫参数
			Forest->all_pass = 1;
			Forest->single_pass = 1;
			Forest->maze.size_n = 15;
			Forest->maze.size_m = 15;
			times = 0;
			Forest->mainGame();

			delete Forest;
			Forest = NULL;
		}
		//沙漠类
		if (click_flag && button->ifClick(xClick, yClick, 280, 240, 370, 270))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			Desert = new CDesert();
			//设定迷宫参数
			Desert->all_pass = 3;
			Desert->single_pass = 1;
			Desert->maze.size_n = 15;
			Desert->maze.size_m = 15;
			times = 0;
			Desert->mainGame();

			delete Desert;
			Desert = NULL;


		}

		//城堡类
		if (click_flag && button->ifClick(xClick, yClick, 280, 280, 370, 310))
		{
			Castle = new CCastle();
			//设定迷宫参数
			Castle->all_pass = 3;
			Castle->single_pass = 1;
			Castle->maze.size_n = 25;
			Castle->maze.size_m = 25;
			times = 0;
			Castle->mainGame();

			delete Castle;
			Castle = NULL;

		}
		//星空类
		if (click_flag && button->ifClick(xClick, yClick, 280, 320, 370, 350))
		{
			Princess = new CPrincess();
			//设定迷宫参数
			Princess->all_pass = 3;
			Princess->single_pass = 1;
			Princess->maze.size_n = 35;
			Princess->maze.size_m = 35;
			times = 0;
			Princess->mainGame();

			delete Princess;
			Princess = NULL;

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
	flushkey();
	swprintf_s(title,L"用时 %lld s\0", times);

	for (; is_run(); delay_fps(60))
	{
		if (kbhit())	//键盘消息获取
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
		button->putButton_(273, 375, 363, 405, "下一关");
		button->putButton_(273, 335, 363, 365, "回到主页");

		//点击回到主页
		if (button->ifClick(xClick, yClick, 273, 335, 363, 365))
		{
			wchar_t* text[10];
			text[0] = L"是否回到主页？\n";
			if (button->putMessageBox(msgBox, L"回到主页", text, 1, MY_CHOICE))
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

		button->drawBackground();

		for (int i = 0; i <= NUMOFSTAGE; i++)
		{
			setcolor(EGERGB(100, 100, 100));
			setfont(110, 0, "幼圆");
			xyprintf(80 + i, 90 + i, "恭喜通关!");
		}
		setcolor(WHITE);
		setfont(110, 0, "幼圆");
		outtextxy(80 + 3, 90 + 3, "恭喜通关!");
		button->putButton_(273, 375, 363, 405, "回到主页");
		button->putButton_(273, 330, 363, 365, "退出游戏");

		if (button->ifClick(xClick, yClick, 273, 375, 363, 405))
		{
			click_flag = false;
			xClick = 0, yClick = 0;
			break;
		}

		//退出游戏
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

//游戏帮助
void CUI::gameHelp()
{
		setfillcolor(EGERGB(187 ,255 ,255));
		bar(30, 30, 610, 450);
		//char str[2000]=@"欢迎游玩游戏MazeGame: Get the Stars!\n本游戏是软A作业";
		setcolor(BLACK);
		outtextrect(40, 40, 570, 420, "欢迎游玩游戏MazeGame: Get the Stars!\n"
			"\n"
			"本游戏分为四大关，每个场景中都使用不同的算法生成迷宫，"
			"在游戏中，你可以通过W A S D操纵人物在地图中移动，当人物移动到右下角的出口时，即为通关。\n"
			"\n"
			"在游戏界面中，你可以随时暂停游戏或者回到主界面，当你觉得通关无望，没有耐心时，记得点击*显示路径*来查看通关路径提示哦~"
			"当然，为了游戏性考虑，在一个大关内提示仅可查看一次，请谨慎使用哟！~\n"
			"\n"
			"另外，在每个场景的第一关，你可以调整游戏难度，难度由1到5递增，一旦开始，该大关内便不能再调整难度。"
			"现在，快来开始游戏吧！\n"
			"\n"
			"按任意键进入游戏…");
}