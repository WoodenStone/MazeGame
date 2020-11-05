/*
Desert.cpp:
流程控制逻辑函数、绘制迷宫算法
by @WoodenStone
生成迷宫 暴力DFS
by @Mango-wen
*/

#include "Game.h"


//全局变量
extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器
int GameLevel_desert = 1;
//绘制界面
void CDesert::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//计时、当前关卡、总关卡、难度等级

	swprintf_s(cur_pass, L"第 %d 关\0", single_pass);
	swprintf_s(tot_pass, L"共 %d 关\0", all_pass);
	swprintf_s(time, L"使用时间 %lld s\0", times);
	swprintf_s(gamelevel, L"难度等级：%d\0", GameLevel_desert);
	//字体样式设置
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "微软雅黑");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	/*废弃线性迷宫绘制，由于迷宫贴图根据人物位置绘制，人物位置时刻变动，故无法实现
	若运行该代码，由于帧循环会产生动态效果，可自行贴图验证*/
	//横围墙
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
	//竖围墙
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

	//获取图像资源
	PIMAGE pimg_desert_road = newimage();
	getimage(pimg_desert_road, "JPG", MAKEINTRESOURCEA(DESERT_ROAD));
	PIMAGE pimg_desert_wall = newimage();
	getimage(pimg_desert_wall, "JPG", MAKEINTRESOURCEA(DESERT_WALL));
	PIMAGE pimg_desert_player = newimage();
	getimage(pimg_desert_player, "JPG", MAKEINTRESOURCEA(DESERT_PLAYER));
	PIMAGE pimg_desert_end = newimage();
	getimage(pimg_desert_end, "JPG", MAKEINTRESOURCEA(DESERT_END));

	//绘制迷宫
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

//沙漠stage核心，流程与森林基本一致
void CDesert::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	//模块标识
	Stage.num = 2;
	bool ifhelped = false;
	//设定按钮位置参数
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

	//输入框变量
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
		//clear();//清空数据函数

		myKLS();//迷宫生成函数

		x = 2;
		y = 2;//重置坐标

		//设置初始时间为0
		start_time = int(time(NULL));

		for (; is_run(); delay_fps(60))
		{
			//累加时间
			times = int(time(NULL)) - start_time;

			ch_msg = (char)'#';	//清空键盘消息

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

			man_Move();//人物移动函数

			if (x == maze.des_x && y == maze.des_y)
				break;			//到达终点判断

			//绘制背景
			button->drawBackground();
			setbkcolor(EGERGB(255, 222, 173));
			//绘制游戏区
			putimage(16, 16, 450, 483, pimg_desert_bg, 0, 0, 1023, 719);
			//绘制当前游戏界面
			putRoom();

			//按钮绘制
			button->putButton_(513, 390, 603, 420, "回到主页");
			button->putButton_(513, 350, 603, 380, "暂停");
			button->putButton_(513, 310, 603, 340, "显示路径");
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "更改难度");
			}
			//点击回到主页
			if (button->ifClick(xClick, yClick, 513, 390, 603, 420))
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"确定回到主页？\n";
	
				if (button->putMessageBox(msg_back, L"回到主页", text, 1, MY_CHOICE))
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
			//点击暂停
			if (button->ifClick(xClick, yClick, 513, 350, 603, 380))
			{
				long long t1 = times;
				wchar_t* text[10];
				text[0] = L"按“确定”结束暂停\n";

				do {
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"暂停", text, 1, 0)));

				start_time = int(time(NULL)) - t1;
				times = t1;
				//IMPORTANT!重置标志值和已获取的鼠标位置信息，否则会导致界面停留不动
				click_flag = false;
				xClick = 0, yClick = 0;
			}
			//显示路径
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
						outtextxy(60, 60, "机会仅有一次，请少侠继续努力~\(≧▽≦)/~");
					} while (!(getch()));
				}
				start_time = int(time(NULL)) - t;
				times = t;
				click_flag = false;
				xClick = 0, yClick = 0;
			}
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "更改难度");
				if (button->ifClick(xClick, yClick, 513, 430, 603, 460))
				{
					click_flag = false;
					xClick = 0, yClick = 0;
					inputbox_getline("请输入难度等级", "输入难度等级1~5,1为最低,5为最高\n输入完毕请键入回车", strbuff, buffsize);
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
							xyprintf(100, 60, "输入错误");
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

		//通过一关卡
		if (oneLevelClear())
		{
			break;
		}
		//通过全关卡
		if (single_pass==all_pass )
		{
			gameClear();
			break;
		}
		//下一关
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

// 冒险模式-沙漠系列类
// 暴力 DFS 随机生成迷宫
void CDesert::myKLS()
{
	//maze.size_m = 25;
	//maze.size_n = 25;
	if (maze.size_m >= 1 && maze.size_n >= 1) {
	for (int i = 1; i <= maze.size_n; i++)	// 初始化
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
		maze.map[maze.size_n - 1][maze.size_m - 2] = ROAD;		// 进行 DFS 生成
	}
}