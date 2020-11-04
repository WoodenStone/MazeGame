// Maze.h : ��ʼ��ͷ�ļ�

// Start
#pragma once			// ��ֹ��ͷ�ļ�����ε���

// Head
#include <stdlib.h>
#include <time.h> //ʱ����Ϊ�����������
#include <graphics.h> //����ͼ�ο�ͷ�ļ�
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <vector>		// ʹ�� STL vector
#include <algorithm>	// ʹ�� random_shuffle ����
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

