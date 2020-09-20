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
	bool putButton(int start_x, int start_y, char str_but[]);
};
