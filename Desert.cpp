//Desert.cpp: 沙漠地图，使用？算法

#include "Game.h"


//全局变量
extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;	//鼠标消息
extern long long times, start_time; //计时器

//绘制界面
void CDesert::putRoom()
{
	wchar_t time[25], cur_pass[50], tot_pass[50];	//计时、当前关卡、总关卡

	swprintf_s(cur_pass, L"第 %d 关\0", single_pass);
	swprintf_s(tot_pass, L"共 %d 关\0", all_pass);
	swprintf_s(time, L"使用时间 %lld s\0", times);

	//字体样式设置
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "微软雅黑");
	xyprintf(480, 25, cur_pass);
	xyprintf(480, 55, tot_pass);
	xyprintf(480, 85, time);

	//绘制线形迷宫
	//绘制围墙
	//横围墙
	/*for (int i = x - 3; i <= x + 4; i++)
	{
		for (int j = y - 4; j <= y + 4; j+=2)
		{
			if (maze.map[i][j] == WALL) {
				setfillcolor(BLACK);
				setlinewidth(10);
				line((j-1-y)*50+266,(i-1-x)*50+266+25,(j-1-y)*50+266+50, (i - 1 - x) * 50 + 266 + 25);
			}
		}
	}
	//竖围墙
	for (int i = x - 4; i <= x + 4; i ++)
	{
		for (int j = y - 3; j <= y + 4; j +=2)
		{
			if (maze.map[i][j] == WALL) {
				setlinewidth(10);
				line((j-1-y)*50+266+25,(i-1-x)*50+266, (j - 1 - y) * 50 + 266 + 25,(i-1-x)*50+266+50);
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
				//setfillcolor(EGERGB(0, 100, 0));
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_wall, 0, 0, 64,64);
			}
			else if (maze.map[i][j] == ROAD)
			{
				//setfillcolor(YELLOW);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_road, 0, 0, 64, 64);
			}
			else if (maze.map[i][j] == END)
			{
				//setfillcolor(BLUE);
				//bar((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				putimage((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, 50, 50, pimg_desert_end, 0, 0, 64, 64);
				maze.des_x = i;
				maze.des_y = j;
			}
			else if (maze.map[i][j] == YOU)
			{
				/*setfillcolor(YELLOW);
				bar((j - y) * 25 + 265, (i - x) * 25 + 265, (j -y-2) * 25 + 266, (i - x-2) * 25 + 266);
				setfillcolor(EGERGB(255,128,64));
				fillellipse((j-y-1)*25+265,(i-x-1)*25+265,25,25);*/
				//putimage((j - y) * 25 + 265, (i - x) * 25 + 265, 50, 50, pimg_forest_player, 0, 0, 59, 59);
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

//沙漠stage核心
void CDesert::mainGame()
{
	CButton* button = new CButton();

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

	int xClick = 0, yClick = 0;
	//myKLS();
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

			if (kbhit())		//键盘消息获取
				ch_msg = getch();

			//设置鼠标点击标志变量为false
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

			//绘制游戏区
			setfillcolor(EGERGB(255,222,173));
			bar(16, 17, 465, 465);

			//绘制当前游戏界面
			putRoom();

			//按钮绘制
			button->putButton_(513, 400, 603,430,"回到主页");
			button->putButton_(513, 350, 603,380,"暂停");

			//点击回到主页
			if (button->ifClick(xClick, yClick, 513, 400, 603, 430))
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

		}

		//通过一关卡
		if (oneLevelClear())
			break;
		//通过全关卡
		if (single_pass==all_pass )
		{
			gameClear();
			break;
		}
		//下一关
		single_pass++;
		maze.size_m += 2;
		maze.size_n += 2;
		if (maze.size_n > 99 || maze.size_m > 99)
		{
			maze.size_n = 99;
			maze.size_m = 99;
		}
	}
	delete button;
	button = NULL;
}

// 冒险模式-沙漠系列类
// 暴力 DFS 随机生成迷宫
void CDesert::myKLS()
{
	//maze.size_m = 25;
	//maze.size_n = 25;
	setbkcolor(RED);
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