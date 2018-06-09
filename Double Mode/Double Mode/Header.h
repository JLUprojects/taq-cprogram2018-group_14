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
void Pos(int x, int y);
void SetColor(unsigned short color);
void HideCursor();
snake* InitializeSnake(int n, int dir, int color);
void CreatMap();
int CompareCoordinate(COORD pt1, COORD pt2);
COORD CreatFood(int color, int n, snake *head1, snake *head2, COORD food1, COORD food2);
void GetDirection(int *dir1, int *dir2);
int MoveSnake1(int dir1, snake **head1, COORD food1, COORD food2, int *score1);
int MoveSnake2(int dir2, snake **head2, COORD food1, COORD food2, int *score2);
int AliveOrNot(snake *head1, snake *head2);
void FreeSnake(snake *head1, snake *head2);
int GameOver(int end, int score1, int score2);
void PrintRules();
void FirstPage();

#endif