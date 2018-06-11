#include <windows.h>
#include "Header.h"
#include <mmsystem.h>//引入声音头文件
#pragma comment(lib, "winmm.lib")//引入声音头文件库

void PlayBackGroundMusic()
{
	PlaySound("music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Pos(short x, short y)//设置光标位置
{
	COORD pos = { x,y };
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void SetColor(unsigned short color)  //设置颜色
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, color);
}

int CompareCoordinate(COORD pt1, COORD pt2)           //比较坐标函数
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y);
}