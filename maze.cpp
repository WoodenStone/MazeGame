//maze.cpp:�������ļ�

#include "Game.h"

//����������
int main()
{
	//�������
	srand((unsigned int)time(NULL));
	//��ʼ����ͼ����
	setinitmode(INIT_RENDERMANUAL, 100, 100);
	initgraph(640, 480);
	setcaption("MazeGame: Get the Stars!");
	flushkey();
	//��ʼ��Ϸ
	/*CUI* graph = new CUI();
	graph->mainMenu();*/

	CnewGameUI* graph = new CnewGameUI();
	graph->initialMenu();

	delete graph;
	graph = NULL;
	//������Ϸ
	closegraph();
	return 0;
}