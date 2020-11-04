/*
Game.h ��Ϸ��Ҫͷ�ļ������������������
by @WoodenStone @Mango-wen
*/

//��ֹ��ε���
#pragma once

#include "maze.h"

constexpr auto MaxN = 150;
extern mouse_msg m_msg;
extern char ch_msg;
extern long long times, start_time;

//����Ի���λ����ز���
typedef struct {
	int x;
	int y;
	int weight;
	int height;
}msgBoxPosition;

//��Ҫ̽��ģʽ��
class CAdventure
{
public:
	
	int single_pass, all_pass;		//���ؿ����ܹؿ�
	int x, y;	//���ﵱǰ����
	int flag[3][2600];			//�Թ���������ͼ�ڵ��Ź�ϵ��¼
	typedef struct
	{
		int Nv;  /* ������ */
		int Ne;  /* ����   */
		int des_x, des_y;		//�յ�����
		int size_n, size_m;		//�Թ���С

		int map[MaxN][MaxN];	//�Թ���ͼ�洢
		int fmap[MaxN][MaxN];	/*�����Թ���ͼ*/

		int reg[2600][2600];	/* �ڽӾ��� */
		int feg[2600][2600];	/*�����ڽӾ���*/
	}Map;
	struct QueueNode {
		/** �����д洢�Ľڵ� */
		int x;
		int y;
	};
	Map maze;
	bool visit[2500];	/*��¼�õ��Ƿ��߹�*/
	union STAGE {
		int num;
	}Stage;

	void man_Move();
	void clear();
	void CreateMaze(int x,int y);
	int Check(int x, int y);
	void dfs_search(int step);
	void Connect(int x1, int y1, int x2, int y2);
	void printQueueSteps(int rows, int cols, int num);
	void solveByQueue(int rows, int cols, int num);
	void SolveByStack(int rows, int cols, int num);
	
};

//��ť��
class CButton
{
public:
	CButton() {}
	~CButton() {}


	void drawBackground();
	void putButton_(int start_x, int start_y, int end_x, int end_y, char str_but[]);
	int putMessageBox(msgBoxPosition msgPosition, wchar_t title[], wchar_t* text[], int g_num, int var);
	bool putButton(int start_x, int start_y, char str_but[]);
	bool ifClick(int xClick, int yClick, int xButton_start, int yButton_start, int xButton_finish, int yButton_finish);

};

//������
class CUI
{
public:
	void mainMenu();
	bool oneLevelClear();
	void gameClear();
	void gameHelp();
private:
	CAdventure CAd;
	
};

//��ʼ������
class CnewGameUI :public CUI
{
public:
	void initialMenu();

};
//̽��ģʽ-ɭ��stage
class CForest :public CAdventure, public CUI
{
public:
	CForest() {}
	~CForest() {}
	
	void mainGame();	//ģʽ����

private:
	void putRoom();	//���ƽ���
	void prim();//�Թ��㷨
};

//̽��ģʽ-ɳĮstage
class CDesert :public CAdventure, public CUI
{
public:
	CDesert() {}
	~CDesert() {}

	void mainGame();	//ģʽ����

private:
	void putRoom();	//���ƽ���
	void myKLS();	// ���� DFS ��������Թ�
};

//̽��ģʽ-�Ǳ�stage
class CCastle : public CAdventure, public CUI
{
public:
	CCastle() {}
	~CCastle() {}

	void mainGame();

private:
	void putRoom();	//���ƽ���
	void deepFS();

};

//̽��ģʽ-Ӫ�ȹ���stage
class CPrincess : public CAdventure, public CUI
{
public:
	CPrincess() {}
	~CPrincess() {}

	void mainGame();

private:
	void putRoom();	//���ƽ���
	int  init();	//��ʼ���Թ�����
	void Create(int x, int y);
};

