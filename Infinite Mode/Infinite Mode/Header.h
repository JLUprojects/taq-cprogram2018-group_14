#ifndef HEADER_H
#define HEADER_H

#include <windows.h>

#define HEIGHT 30  //the height of the map
#define WIDTH 60  //the width of the map
#define SNAKE_LEN 4  //the initial length of the snake
#define LEFT 75    //the value which correspond to the arrow key
#define UP 72    
#define RIGHT 77    
#define DOWN 80
#define ESC 27 //exit
#define NEWGAME 48 //the ASCII code of "1"and "0"
#define CONTINUE 49
#define BLOOD 5

typedef struct SNAKE //use a linked list to represent a snake
{
	COORD cor;
	struct SNAKE *next;
}snake;

void PlayBackGroundMusic();
void FirstPage();
void FreeSnake(snake*);
void AliveOrNot(COORD, snake*, int*);
void MoveSnake(int, snake**, COORD*, int*, int*);
void CreateFood(COORD*, snake*);
int CompareCoordinate(COORD, COORD);
int GetDirection(int*, int*);
snake* InitializeSnake();
void CreateMap();
void SetColor(unsigned short);
void CreateBlood(int *blood);
void Pos(short, short);
void HideCursor();
void PrintRules();

#endif