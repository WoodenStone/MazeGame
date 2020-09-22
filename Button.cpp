//Button.cpp: ʵ�ְ�ť�ͶԻ���

#include "Game.h"

//ȫ�ֱ���

extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;


//���Ʊ���
void CButton::drawBackground()
{
	setbkcolor(EGERGB(50, 50, 50));
	cleardevice();
}

//���ð�ť
bool CButton::putButton(int start_x, int start_y, char str_but[])
{
	static int x, y;

	//���Ʊ߿�
	setfillcolor(EGERGB(100, 100, 100));
	bar(start_x - 25, start_y, start_x + 19 * strlen(str_but) + 25, start_y + 30);

	//��ȡ����
	x = m_msg.x;
	y = m_msg.y;
	
	//��ȡ����
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
	
	//����������ز���
	LOGFONTA f;		//LOGFONTAΪMBCS�汾 LOGFONTWΪUTF16�汾 to be confirmed
	getfont(&f);
	f.lfHeight = 25;
	strcpy(f.lfFaceName, "΢���ź�");
	f.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f);
	setcolor(WHITE);
	outtextxy(x, y + 30, str_but);

	return 0;
}