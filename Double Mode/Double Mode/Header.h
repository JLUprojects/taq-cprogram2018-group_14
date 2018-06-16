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
#define A 97   
#define W 119    
#define S 115    
#define D 100
#define TIMELIMIT  1 
#define NEWGAME 48 

typedef struct SNAKE 
{
	COORD cor;
	struct SNAKE *next;
}snake;

void PlayBackGroundMusic();
void Pos(short, short);
void SetColor(unsigned short);
void HideCursor();
snake* InitializeSnake(int, int, int);
void CreateMap();
int CompareCoordinate(COORD, COORD);
COORD CreateFood(int, int, snake *, snake *, COORD, COORD);
void GetDirection(int *, int *);
int MoveSnake1(int , snake **, COORD , COORD , int *);
int MoveSnake2(int , snake **, COORD , COORD , int *);
int AliveOrNot(snake *, snake *);
void FreeSnake(snake *, snake *);
int GameOver(int, int, int);
void PrintRules();
void FirstPage();

#endif