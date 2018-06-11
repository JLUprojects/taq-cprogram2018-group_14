#include <windows.h>
#include "Header.h"
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void PlayBackGroundMusic()
{
	PlaySound("music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

}

void Pos(short x,short y)//set  position of the cursor 
{
	COORD pos = { x,y };
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//hide the cursor
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void SetColor(unsigned short color)  //set the color of the text
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, color);
}

int CompareCoordinate(COORD pt1, COORD pt2)  //compare two coordinates 
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y);
}