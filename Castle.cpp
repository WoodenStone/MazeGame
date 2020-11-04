/*
Castle.cpp:
流程控制逻辑函数、绘制迷宫算法
by @WoodenStone
生成迷宫 图论DFS
by @Mango-wen
*/


#include "Game.h"


//全局变量
extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器
int GameLevel_castle = 1;

//绘制界面
void CCastle::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//计时、当前关卡、总关卡、难度等级

	swprintf_s(cur_pass, L"第 %d 关\0", single_pass);
	swprintf_s(tot_pass, L"共 %d 关\0", all_pass);
	swprintf_s(time, L"使用时间 %lld s\0", times);
	swprintf_s(gamelevel, L"难度等级：%d\0", GameLevel_castle);

	//字体样式设置
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "微软雅黑");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	//获取图像资源
	PIMAGE pimg_castle_road = newimage();
	getimage(pimg_castle_road, "JPG", MAKEINTRESOURCEA(CASTLE_ROAD));
	PIMAGE pimg_castle_wall = newimage();
	getimage(pimg_castle_wall, "JPG", MAKEINTRESOURCEA(CASTLE_WALL));
	PIMAGE pimg_castle_player = newimage();
	getimage(pimg_castle_player, "JPG", MAKEINTRESOURCEA(CASTLE_PLAYER));
	PIMAGE pimg_castle_end = newimage();
	getimage(pimg_castle_end, "JPG", MAKEINTRESOURCEA(CASTLE_END));

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
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_wall, 0, 0, 128, 128);
			}
			else if (maze.map[i][j] == ROAD)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_road, 0, 0, 300, 300);
			}
			else if (maze.map[i][j] == END)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_end, 0, 0, 100, 100);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_castle_player, 0, 0, 150, 150);
				x = i;
				y = j;
			}
		}
	}
	delimage(pimg_castle_road);
	delimage(pimg_castle_wall);
	delimage(pimg_castle_end);
	delimage(pimg_castle_player);

}

//城堡stage核心
void CCastle::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	bool ifhelped = false;
	//模块标识
	Stage.num = 3;
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
	memset(strbuff, 0, sizeof(strbuff));
	bool error = false;
	bool ifInput = false;

	switch (GameLevel_castle) {
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
		GameLevel_castle = 1;
		break;
	}

	int xClick = 0, yClick = 0;
	PIMAGE pimg_castle_bg = newimage();
	getimage(pimg_castle_bg, "images\\castle_bg.jpg", 0, 0);
	for (; is_run(); delay_fps(60))
	{
		//clear();//清空数据函数
		deepFS();

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
			setbkcolor(EGERGB(102,110,147));

			//绘制游戏区
			putimage(16, 16, 450, 483, pimg_castle_bg, 0, 0, 734, 536);
			//绘制当前游戏界面
			putRoom();

			//按钮设置
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
					return;
				}
				else {
					click_flag = false;
					xClick = 0, yClick = 0;
					start_time = int(time(NULL)) - t;
					times = t;
				}
			}
			//pause
			if (button->ifClick(xClick, yClick, 513, 350, 603, 380))
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"按“确定”结束暂停\n";
				do {
					getmouse();
				} while (!(button->putMessageBox(msg_Pause, L"暂停", text, 1, 0)));
				start_time = int(time(NULL)) - t;
				times = t;
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
					else if (sscanf(strbuff, "%d", &GameLevel_castle) == 1)
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
							outtextxy(100, 60, "输入错误");
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
			break;
		//通过全关卡
		if (single_pass == all_pass)
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
	delimage(pimg_castle_bg);
	delete(ad);
	ad = NULL;
	delete button;
	button = NULL;
}



// 图论 DFS 随机生成迷宫
void CCastle::deepFS()
{
	maze.Nv = 0;						// 节点数清空
	//maze.size_m = 21;
	//maze.size_n = 21;

	for (int i = 1; i <= maze.size_n; i++)	// 初始化
	{
		for (int j = 1; j <= maze.size_m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				maze.map[i][j] = ROAD;
				flag[0][++maze.Nv] = maze.Nv;
				flag[1][maze.Nv] = i;
				flag[2][maze.Nv] = j;
			}
			else
			{
				maze.map[i][j] = WALL;
			}
		}
	}
	for (int i = 1; i <= maze.Nv; i++)
	{
		visit[i] = 0;
		if (i % ((maze.size_n - 1) / 2) != 0)
		{
			maze.reg[i][i + 1] = 1;
			maze.reg[i + 1][i] = 1;
		}
		if (i <= maze.Nv - (maze.size_n - 1) / 2)
		{
			maze.reg[i][i + (maze.size_n - 1) / 2] = 1;
			maze.reg[i + (maze.size_n - 1) / 2][i] = 1;
		}
	}

	dfs_search(maze.Nv);				// 进行图论 DFS 生成

	for (int i = 1; i <= maze.Nv; i++)
	{
		for (int j = 1; j <= maze.Nv; j++)
		{
			if (maze.reg[i][j] == 2 || maze.reg[j][i] == 2)
			{
				Connect(flag[1][i], flag[2][i], flag[1][j], flag[2][j]);
			}
		}
	}
	maze.map[2][2] = YOU;
	if ((maze.size_n - 1) > 0 && maze.size_m > 0) {
		maze.map[maze.size_n - 1][maze.size_m] = END;	// 将图论 DFS 结果显示到迷宫中
	}
}