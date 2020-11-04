// Maze.h : 初始化头文件

// Start
#pragma once			// 防止该头文件被多次调用

// Head
#include <stdlib.h>
#include <time.h> //时间作为随机生成种子
#include <graphics.h> //引入图形库头文件
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <vector>		// 使用 STL vector
#include <algorithm>	// 使用 random_shuffle 函数
#include "resource.h"


// Block

enum BLOCK { WALL = 1, 
	YOU, 
	END, 
	ROAD };

//Button
#define MY_OK 0
#define MY_CHOICE 1

//Const Number
#define INF 2147483647
#define NUMOFSTAGE 4

