#pragma once

#include "maze.h"

//终点坐标结构体
struct EndCoordinate {
	int to_x;
	int to_y;
};
//人物坐标结构体
struct RoleCoordinate {
	int x;
	int y;
};
//迷宫大小
struct MazeSize {
	int XofSize;
	int YofSize;
};
class CAdventure
{
public:
	int level, all_level;		//关卡和总关卡
	struct EndCoordinate endxy; //终点坐标
	struct RoleCoordinate rolexy;//人物坐标
	int room[150][150];			//迷宫地图存储
	struct MazeSize size;		//迷宫大小
};


class CButton
{
public:
	CButton() {}
	~CButton() {}

	void drawBackground();
<<<<<<< Updated upstream
	bool putButton(int start_x, int start_y, char str_but[]);
=======
	int putMessageBox(msgBoxPosition msgPosition, wchar_t title[], wchar_t* text[], int g_num, int var);
	void putButton_(int start_x, int start_y, int end_x, int end_y, char str_but[]);
	bool putButton(int start_x, int start_y, char str_but[]);
	bool ifClick(int xClick, int yClick, int xButton_start, int yButton_start, int xButton_finish, int yButton_finish);

};

class CUI
{

public:
	/*int single_pass=single_pass, all_pass=all_pass;		//关卡和总关卡
	int maze.des_x = 480, maze.des_y = 640;			//终点坐标
	int x = 1, y = 1;					//人物坐标
	int n, m;						//迷宫大小
	int room[150][150];				//迷宫地图存储
	Map maze;		*/	//迷宫大小

	//CUI() {}
	//~CUI() {}
	void mainMenu();
	bool oneLevelClear();
	void gameClear();
private:
	CAdventure CAd;
	
};

class CnewGameUI {
public:
	void initialMenu();

};
//冒险模式-森林stage
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

//冒险模式-沙漠stage
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

//冒险模式-城堡stage
class CCastle : public CAdventure, public CUI
{
public:
	CCastle() {}
	~CCastle() {}

	void mainGame();

private:
	void putRoom();	//绘制界面
	void deepFS();
>>>>>>> Stashed changes
};
