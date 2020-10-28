<<<<<<< Updated upstream
=======
//maze.cpp:程序主文件

#include "Game.h"

//程序主函数
int main()
{
	//随机种子
	srand((unsigned int)time(NULL));
	//初始化绘图环境
	setinitmode(INIT_RENDERMANUAL|INIT_NOFORCEEXIT, 100, 100);
	initgraph(640, 480);
	setcaption("MazeGame: Get the Stars!");
	//开始游戏
	CUI* graph = new CUI();
	graph->mainMenu();


	/*CnewGameUI* graph = new CnewGameUI();
	graph->initialMenu();*/
	delete graph;
	graph = NULL;
	//结束游戏
	closegraph();
	return 0;
}
>>>>>>> Stashed changes
