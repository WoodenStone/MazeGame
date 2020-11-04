//Button.cpp: ʵ�ְ�ť�ͶԻ���

#include "Game.h"

//ȫ�ֱ���
extern char ch_msg;	//������Ϣ
extern mouse_msg m_msg;	//�����Ϣ

//���Ʊ���

void CButton::drawBackground()
{
	//setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
}

//���ð�ť
void CButton::putButton_(int start_x, int start_y, int end_x, int end_y, char str_but[])
{
	static int x, y;
	//���Ʊ߿�
	setfillcolor(EGERGB(255,121,136));
	bar(start_x, start_y, end_x, end_y);

	//���ð�ť��������ز���
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(20, 0, "��Բ");
	xyprintf(start_x + (end_x - start_x) / 2 - (textwidth(str_but) / 2), start_y + (end_y - start_y) / 2 - (textheight(str_but) / 2), str_but);

}

bool CButton::putButton(int start_x, int start_y, char str_but[])
{
	static int x, y;
	int xClick, yClick;
	bool click_flag = false;
	//���Ʊ߿�
	setfillcolor(EGERGB(100, 100, 100));
	bar(start_x - 25, start_y, start_x + 7 * strlen(str_but) + 30, start_y + 30);

	//��ȡ����
	/*x = msg.x;
	y = msg.y;*/
	for (; is_run(); delay_fps(60))
	{
		click_flag = false;	//���õ����־λ
		while (mousemsg())	//��ȡ�����Ϣ
		{
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down())	//�����������¼�
			{
				click_flag = true;
				xClick = msg.x;
				yClick = msg.y;
			}
		}
		if (click_flag)
		{
			//���λ�ô��ڰ�ť��
			if (xClick > start_x - 25 && (size_t)xClick< start_x + 7 * strlen(str_but) + 30 && yClick>start_y && yClick < start_y + 30)
			{
				return 1;
			}
		}

		//���ð�ť��������ز���
		LOGFONT f;
		getfont(&f);
		f.lfHeight = 23;
		wcscpy_s(f.lfFaceName, L"΢���ź� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		setbkmode(TRANSPARENT);	//���׳�������ģ����� �����
		//setfontbkcolor(WHITE);
		setcolor(WHITE);
		outtextxy(start_x, start_y + 2, str_but);
	}
	return 0;
}
//�ж�������¼�
bool CButton::ifClick(int xClick, int yClick,int xButton_start,int yButton_start,int xButton_finish,int yButton_finish)	//��ť���궨λ
{
	//���λ�ô��ڰ�ť��
	if (xButton_start < xClick && xClick< xButton_finish && yButton_start<yClick && yClick < yButton_finish)		
	{
		return 1;
	}		
	else return 0;
}
//���ƶԻ���
int CButton::putMessageBox(msgBoxPosition msgPosition, wchar_t title[], wchar_t* text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);
	int xClick=0, yClick=0;
	bool click_flag = false;
	
	for (; is_run(); delay_fps(60))
	{
		if (kbhit())		//������Ϣ���
			ch_msg = getch();

		
		while (mousemsg())	//�����Ϣ��ȡ
		{
			m_msg = getmouse();
			if (m_msg.is_left() && m_msg.is_down())	//�����������¼�
			{
				click_flag = true;
				xClick = m_msg.x;
				yClick = m_msg.y;
			}
		}

		setfillcolor(EGERGB(25, 25, 25));
		bar(msgPosition.x, msgPosition.y, msgPosition.x + msgPosition.weight, msgPosition.y + msgPosition.height);

		//�ַ���Ϣ��ȡ
		LOGFONT f;
		getfont(&f);
		f.lfHeight = 30;
		wcscpy_s(f.lfFaceName, L"����");
		f.lfQuality = ANTIALIASED_QUALITY;
		setfont(&f);
		outtextxy(msgPosition.x + 20, msgPosition.y + 10, title);

		//����Ի�������
		for (int i = 0; i < g_num; i++)
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			setfont(&f);
			outtextxy(msgPosition.x + 25, msgPosition.y + 45 + 20 * i, text[i]);
		}

		//���ݴ���ĳ���ѡ��ͬ���ð�ť
		//����ΪMY_OK ������ʾ��
		//����ΪMY_CHOICE ����ѡ���

		if (var == MY_OK)
		{
			//if (putButton(msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 37, "ȷ��"))
				//return 0;
			putButton_(msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10, "ȷ��");
			if (click_flag && ifClick(xClick, yClick, msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10))
				return 1;
		}
		else if (var == MY_CHOICE)
		{
			putButton_(msgPosition.x + msgPosition.weight - 140, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 80, msgPosition.y + msgPosition.height - 10, "��");
			putButton_(msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10, "��");
			if (click_flag&&ifClick(xClick, yClick, msgPosition.x + msgPosition.weight - 140, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 80, msgPosition.y + msgPosition.height - 10))
				return 1;
			if (click_flag&&ifClick(xClick, yClick, msgPosition.x + msgPosition.weight - 70, msgPosition.y + msgPosition.height - 40, msgPosition.x + msgPosition.weight - 10, msgPosition.y + msgPosition.height - 10))
				return 0;
		}

	}
	//return 0;
}