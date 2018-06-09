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
#define ESC 27 //exit and save
#define NEWGAME 48 
#define CONTINUE 49
#define OBSTACL_COUNT 3//An obstacle will be created every time you get OBSTACL_COUNT more points.
typedef struct SNAKE 
{
	COORD cor;
	struct SNAKE *next;
}snake;

typedef struct OBSTACLE  
{
	COORD cor;
	struct OBSTACLE *next;
}Obstacle;

void PlayBackGroundMusic();
void FirstPage();
void FreeSnake(snake*);
int AliveOrNot( snake*);
void MoveSnake(int, snake **, COORD *, int *);
void CreateFood(COORD*, snake*);
int CompareCoordinate(COORD, COORD);
int GetDirection(int*, int*);
snake* InitializeSnake();
int Choose();
snake* Load(int*, int*, int*, int *);
void Save(int*, int*, int*,int *, snake*);
void CreateMap();
void SetColor(unsigned short);
void Pos(int, int);
void HideCursor();
void PrintRoles(int *);
int GameOver(int, int);
void Add2Obstacle(COORD, Obstacle **);
COORD CreateObstacle(snake *, COORD, Obstacle *);
void IfRunIntoObstacle(snake **, Obstacle **, int *, COORD );
void MoveObstacle(Obstacle **, COORD, snake *);
void FreeObstacle(Obstacle *);
#endif