#include "Header.h"
#include <Windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void PlayBackGroundMusic()
{
	PlaySound("music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Pos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void SetColor(unsigned short color)
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


int CompareCoordinate(COORD pt1, COORD pt2)
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y);
}