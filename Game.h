#pragma once

#include "maze.h"

//�յ�����ṹ��
struct EndCoordinate {
	int to_x;
	int to_y;
};
//��������ṹ��
struct RoleCoordinate {
	int x;
	int y;
};
//�Թ���С
struct MazeSize {
	int XofSize;
	int YofSize;
};
class CAdventure
{
public:
	int level, all_level;		//�ؿ����ܹؿ�
	struct EndCoordinate endxy; //�յ�����
	struct RoleCoordinate rolexy;//��������
	int room[150][150];			//�Թ���ͼ�洢
	struct MazeSize size;		//�Թ���С
};


class CButton
{
public:
	CButton() {}
	~CButton() {}

	void drawBackground();
	bool putButton(int start_x, int start_y, char str_but[]);
};
