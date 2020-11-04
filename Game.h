/*
Game.h 游戏主要头文件，包含各个类的声明
by @WoodenStone @Mango-wen
*/

//防止多次调用
#pragma once

#include "maze.h"

constexpr auto MaxN = 150;
extern mouse_msg m_msg;
extern char ch_msg;
extern long long times, start_time;

//定义对话框位置相关参数
typedef struct {
	int x;
	int y;
	int weight;
	int height;
}msgBoxPosition;

//主要探索模式类
class CAdventure
{
public:
	
	int single_pass, all_pass;		//单关卡、总关卡
	int x, y;	//人物当前坐标
	int flag[3][2600];			//迷宫中坐标与图节点编号关系记录
	typedef struct
	{
		int Nv;  /* 顶点数 */
		int Ne;  /* 边数   */
		int des_x, des_y;		//终点坐标
		int size_n, size_m;		//迷宫大小

		int map[MaxN][MaxN];	//迷宫地图存储
		int fmap[MaxN][MaxN];	/*辅助迷宫地图*/

		int reg[2600][2600];	/* 邻接矩阵 */
		int feg[2600][2600];	/*辅助邻接矩阵*/
	}Map;
	struct QueueNode {
		/** 队列中存储的节点 */
		int x;
		int y;
	};
	Map maze;
	bool visit[2500];	/*记录该点是否走过*/
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

//按钮类
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

//界面类
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

//初始界面类
class CnewGameUI :public CUI
{
public:
	void initialMenu();

};
//探索模式-森林stage
class CForest :public CAdventure, public CUI
{
public:
	CForest() {}
	~CForest() {}
	
	void mainGame();	//模式核心

private:
	void putRoom();	//绘制界面
	void prim();//迷宫算法
};

//探索模式-沙漠stage
class CDesert :public CAdventure, public CUI
{
public:
	CDesert() {}
	~CDesert() {}

	void mainGame();	//模式核心

private:
	void putRoom();	//绘制界面
	void myKLS();	// 暴力 DFS 随机生成迷宫
};

//探索模式-城堡stage
class CCastle : public CAdventure, public CUI
{
public:
	CCastle() {}
	~CCastle() {}

	void mainGame();

private:
	void putRoom();	//绘制界面
	void deepFS();

};

//探索模式-营救公主stage
class CPrincess : public CAdventure, public CUI
{
public:
	CPrincess() {}
	~CPrincess() {}

	void mainGame();

private:
	void putRoom();	//绘制界面
	int  init();	//初始化迷宫数组
	void Create(int x, int y);
};

