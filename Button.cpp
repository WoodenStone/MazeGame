//Button.cpp: 实现按钮和对话框

#include "Game.h"

//全局变量

extern char ch_msg;	//键盘消息
extern mouse_msg m_msg;


//绘制背景
void CButton::drawBackground()
{
	setbkcolor(EGERGB(50, 50, 50));
	cleardevice();
}

//放置按钮
<<<<<<< Updated upstream
=======
void CButton::putButton_(int start_x, int start_y, int end_x,int end_y, char str_but[])
{
	static int x, y;
	int xClick, yClick;
	bool click_flag = false;
	//绘制边框
	setfillcolor(EGERGB(100, 100, 100));
	bar(start_x, start_y, end_x, end_y);

		//设置按钮内字体相关参数
		setcolor(WHITE);
		setbkmode(TRANSPARENT);
		setfont(23, 0, "微软雅黑");
		xyprintf(start_x + (end_x-start_x)/2 - (textwidth(str_but) / 2), start_y + (end_y-start_y)/2 - (textheight(str_but) / 2), str_but);

}

>>>>>>> Stashed changes
bool CButton::putButton(int start_x, int start_y, char str_but[])
{
	static int x, y;

	//绘制边框
	setfillcolor(EGERGB(100, 100, 100));
	bar(start_x - 25, start_y, start_x + 19 * strlen(str_but) + 25, start_y + 30);

	//获取坐标
<<<<<<< Updated upstream
	x = m_msg.x;
	y = m_msg.y;
	
	//获取焦点
	if (x > start_x - 25 && (size_t)x< start_x + 19 * strlen(str_but) + 25 && y>start_y && y < start_y + 30)
	{
		setfillcolor(EGERGB(150, 150, 150));
		bar(x - 25, y, x + 19 * strlen(str_but) + 25, y + 30);

		if (m_msg.is_up())
		{
			m_msg.is_move();
			return 1;
		}	//?????
=======
	/*x = msg.x;
	y = msg.y;*/
	for (; is_run(); delay_fps(60))
	{
		click_flag = false;	//设置点击标志位
		while (mousemsg())	//获取鼠标信息
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())	//存在左键点击事件
			{
				click_flag = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (click_flag)
		{
			//点击位置处于按钮内
			if (xClick > start_x - 25 && (size_t)xClick< start_x + 7 * strlen(str_but) + 30 && yClick>start_y && yClick < start_y + 30)
			{
				return 1;
			}
		}

		//设置按钮内字体相关参数
		LOGFONT f;
		getfont(&f);
		f.lfHeight = 23;
		wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setbkmode(TRANSPARENT);	//容易出现字体模糊情况 待解决
		//setfontbkcolor(WHITE);
		setcolor(WHITE);
		outtextxy(start_x, start_y + 2, str_but);
	}
	return 0;
}
//判断鼠标点击事件
bool CButton::ifClick(int xClick, int yClick,int xButton_start,int yButton_start,int xButton_finish,int yButton_finish)	//按钮坐标定位
{
	//点击位置处于按钮内
	if (xButton_start < xClick && xClick< xButton_finish && yButton_start<yClick && yClick < yButton_finish)		
	{
		return 1;
	}		
	else return 0;
}

//绘制对话框
int CButton::putMessageBox(msgBoxPosition msgPosition, wchar_t title[], wchar_t * text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);
	int xClick, yClick;
	while(1)
	{
		if (kbhit())		//键盘消息清空
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

		setfillcolor(EGERGB(25, 25, 25));
		bar(msgPosition.x, msgPosition.y, msgPosition.x + msgPosition.weight, msgPosition.y + msgPosition.height);

		//字符消息获取
		LOGFONT f;
		getfont(&f);
		f.lfHeight = 30;
		wcscpy_s(f.lfFaceName, L"黑体");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		outtextxy(msgPosition.x + 20, msgPosition.y + 10, title);

		//输出对话框文字
		for (int i = 0; i < g_num; i++)
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			setfont(&f);
			outtextxy(msgPosition.x + 25, msgPosition.y+45+20*i, text[i]);
		}

		//根据传入的常量选择不同放置按钮
		//传入为MY_OK 代表提示框
		//传入为MY_CHOICE 代表选择框

		if (var == MY_OK)
		{
			//if (putButton(msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 37, "确定"))
				//return 0;
			putButton_(msgPosition.x+msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x+msgPosition.weight - 10, msgPosition.y+msgPosition.height - 10, "确定");
			if (click_flag && ifClick(xClick, yClick, msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10))
				return 1;
		}
		else if (var == MY_CHOICE)
		{
			putButton_(msgPosition.x + msgPosition.weight - 140, msgPosition.y + msgPosition.height - 40,msgPosition.x+msgPosition.weight-80, msgPosition.y + msgPosition.height - 10, "是");
			putButton_(msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10, "否");
			if (click_flag&&ifClick(xClick,yClick,msgPosition.x + msgPosition.weight - 140, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 80, msgPosition.y + msgPosition.height - 10))
				return 1;
			if (click_flag && ifClick(xClick, yClick, msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10))
				return 0;
		}
>>>>>>> Stashed changes
	}
	
	//设置字体相关参数
	LOGFONTA f;		//LOGFONTA为MBCS版本 LOGFONTW为UTF16版本 to be confirmed
	getfont(&f);
	f.lfHeight = 25;
	strcpy(f.lfFaceName, "微软雅黑");
	f.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f);
	setcolor(WHITE);
	outtextxy(x, y + 30, str_but);

	return 0;
}