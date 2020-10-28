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
	/*int single_pass=single_pass, all_pass=all_pass;		//�ؿ����ܹؿ�
	int maze.des_x = 480, maze.des_y = 640;			//�յ�����
	int x = 1, y = 1;					//��������
	int n, m;						//�Թ���С
	int room[150][150];				//�Թ���ͼ�洢
	Map maze;		*/	//�Թ���С

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
//ð��ģʽ-ɭ��stage
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

//ð��ģʽ-ɳĮstage
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

//ð��ģʽ-�Ǳ�stage
class CCastle : public CAdventure, public CUI
{
public:
	CCastle() {}
	~CCastle() {}

	void mainGame();

private:
	void putRoom();	//���ƽ���
	void deepFS();
>>>>>>> Stashed changes
};
