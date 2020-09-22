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
bool CButton::putButton(int start_x, int start_y, char str_but[])
{
	static int x, y;

	//绘制边框
	setfillcolor(EGERGB(100, 100, 100));
	bar(start_x - 25, start_y, start_x + 19 * strlen(str_but) + 25, start_y + 30);

	//获取坐标
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