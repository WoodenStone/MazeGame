/*
Pincess.cpp: 
星空类 由于历史遗留问题命名为princess
流程控制逻辑函数、绘制迷宫算法
by @WoodenStone
生成迷宫 递归分割
by @Mango-wen
*/

#include "Game.h"

//全局变量
extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器
int GameLevel_star = 1;

//绘制界面
void CPrincess::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50], gamelevel[20];	//计时、当前关卡、总关卡、难度等级

	swprintf_s(cur_pass, L"第 %d 关\0", single_pass);
	swprintf_s(tot_pass, L"共 %d 关\0", all_pass);
	swprintf_s(time, L"使用时间 %lld s\0", times);
	swprintf_s(gamelevel, L"难度等级：%d\0", GameLevel_star);

	//字体样式设置
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "微软雅黑");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 115, time);
	xyprintf(480, 85, gamelevel);

	//设置背景
	PIMAGE pimg_star_bg = newimage();
	getimage(pimg_star_bg, "JPG", MAKEINTRESOURCEA(STAR_BG));
	putimage(16, 17, 449, 482, pimg_star_bg, 0, 0, 1080, 1080);

	//获取图像资源
	PIMAGE pimg_star_player = newimage();
	PIMAGE pimg_star_end = newimage();
	PIMAGE pimg_star_wall = newimage();
	
	getimage_pngfile(pimg_star_player, "images\\star_player.png");
	getimage_pngfile(pimg_star_end, "images\\star_end.png");
	getimage_pngfile(pimg_star_wall, "images\\star_wall.png");
	//使用图片数组存储不同的WALL
	/*PIMAGE pimgs[6];
	char filename[30];
	for (int i = 0; i <= 5; i++)
	{
		sprintf(filename, "images\\star_wall%d.png", i + 1);
		pimgs[i] = newimage();
		getimage_pngfile(pimgs[i], filename);
	}*/

	//绘制迷宫
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

//营救公主stage核心
void CPrincess::mainGame()
{
	CButton* button = new CButton();
	CAdventure* ad = new CAdventure();
	//模块表示
	Stage.num = 4;
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
		clear();//清空数据函数

		maze.des_y=init();//迷宫生成函数
		maze.des_x = maze.size_n - 3;

		maze.map[maze.des_x][maze.des_y] = END;

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
			setbkcolor(EGERGB(51,51,102));
			//绘制游戏区
			setfillcolor(BLACK);
			bar(16, 17, 465, 465);

			//绘制当前游戏界面
			putRoom();

			//放置按钮
			button->putButton_(513, 390, 603, 420, "回到主页");
			button->putButton_(513, 350, 603, 380, "暂停");
			button->putButton_(513, 310, 603, 340, "显示路径");
			if (single_pass == 1)
			{
				button->putButton_(513, 430, 603, 460, "更改难度");
			}
			//按钮设置
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

					inputbox_getline("请输入难度等级", "输入难度等级1~5,1为最低,5为最高\n输入完毕请键入回车", strbuff, buffsize);
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
			break;
		//通过全关卡
		if (single_pass==all_pass)
		{
			gameClear();
			break;
		}
		//下一关
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


//控制迷宫的复杂度，数值越大复杂度越低，最小值为0
//默认为简单难度，可根据需要在degree函数里调整不同难度的复杂度
int Rank = 6;

//CPrincess 函数实现

//初始化迷宫
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
	//最外围设为路径，为防止挖路时挖出边界，为保护迷宫主体外的一圈墙体被挖穿
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
	//创建迷宫，（2,2）为起点
	Create(2, 2);
	//画迷宫的入口和出口，给出玩家初始位置
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
	//由于算法随机性，出口有一定概率不在（n-3,m-2)处，此时需要寻找出口
	for (int i = maze.size_n - 2; i >= 0; i--)
	{
		if (maze.size_m >= 3) {
			if (maze.map[i][maze.size_m - 3] == ROAD)
			{
				maze.map[i][maze.size_m - 2] = ROAD;
				//返回出口所在的纵坐标
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
	//确保四个方向随机，不是固定的上下左右顺序
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
	//向四个方向开挖
	for (int i = 0; i < 4; i++)
	{
		int dx = x;
		int dy = y;
		//控制挖的距离，由rank来调整大小
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range > 0)
		{
			//计算出将要访问到的坐标
			dx += dir[i][0];
			dy += dir[i][1];
			//排除掉回头路
			if (maze.map[dx][dy] == ROAD)
				break;
			//判断是否挖穿路径
			int count = 0, k;
			for (j = dx - 1; j < dx + 2; j++)
			{
				for (k = dy - 1; k < dy + 2; k++)
				{	//确保是九宫格的四个位置
					if (abs(j - dx) + abs(k -dy) == 1 && maze.map[j][k] == ROAD)
						count++;
				}
			}
			//count大于1表明墙体会被挖穿，停止
			if (count > 1)
				break;
			//确保不会挖穿时，前进
			range -= 1;
			maze.map[dx][dy] = ROAD;
		}
		//没有挖穿危险，以此为节点递归
		if (range <= 0) {
			Create(dx, dy);
		}
	}
}