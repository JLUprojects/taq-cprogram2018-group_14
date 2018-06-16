#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "Header.h"

COORD CreateObstacle(snake *head,COORD food,Obstacle *obstacle)
{
	COORD coord;
	snake *p = NULL;
	Obstacle *r = NULL;
	int in_snake, in_obstacle, in_food;
	srand((unsigned int)time(NULL)+5);

	do {
		in_snake = 0;
		in_obstacle = 0;
		in_food=0;
		int x = (rand() % (WIDTH - 5)) + 3;      
		coord.X = (x % 2) ? x + 1 : x;     
		coord.Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head; p != NULL; p = p->next) {     //if the new obstacle coincides with snake
			if (CompareCoordinate(p->cor, coord))
				in_snake = 1;
		}
		for (r = obstacle; r != NULL; r = r->next) {     //if the new obstacle coincides with other obstacles
			if (CompareCoordinate(r->cor, coord))
				in_obstacle = 1;
		}
		if (CompareCoordinate(food, coord)) //if the new obstacle coincides with food
			in_food = 1;
	} while (in_snake|| in_obstacle||in_food);

	Pos(coord.X, coord.Y);
	SetColor(15);
	printf("¡ö");

	return coord;
}
 
void Add2Obstacle(COORD coord, Obstacle **obstacle)
{
	Obstacle *r = (Obstacle *)malloc(sizeof(Obstacle));
	r->cor.X = coord.X;
	r->cor.Y = coord.Y;
	r->next = NULL;
	
	if (*obstacle == NULL)
		*obstacle =r;
	else {
		 r->next=*obstacle;
		*obstacle = r;
	}
}

void MoveObstacle(Obstacle **obstacle, COORD food, snake *head)
{
	Obstacle *r;
	int direction ;
	int recreat;
	COORD previous;
	srand((unsigned int)time(NULL));
	for (r = *obstacle; r != NULL; r = r->next) {
		previous = r->cor;
		do {
			direction = rand() % 4 + 1;
			switch (direction) {                              //change the coordinate of the obstacle
			case 1:                                               // according to the direction which has been created randomly
				r->cor.Y--; break;
			case 2:
				r->cor.Y++; break;
			case 3:
				r->cor.X += 2; break;
			case 4:
				r->cor.X -= 2; break;
			}
			recreat = 0;                                               //obstacle can't cover food or bump the wall,if so,creat direction again
			if (CompareCoordinate(food, r->cor) || r->cor.X == 0 || r->cor.X == WIDTH || r->cor.Y == 0 || r->cor.Y == HEIGHT) {
				recreat = 1;
				r->cor = previous;
			}
		} while (recreat); 

		Pos(r->cor.X, r->cor.Y);            //print new obstacle
		SetColor(15);
		printf("¡ö");
		Pos(previous.X, previous.Y);  //cover the previous obstacle
		SetColor(0);
		printf("¡ö"); HideCursor();
	}
}

void IfRunIntoObstacle(snake **head, Obstacle **obstacle, int *score,COORD food)
{
	snake *p,*q,*pre;
	Obstacle *r,*l;
	for (r = *obstacle,l=NULL; r != NULL; l=r, r = r->next) {   //compare each obstacle with each node of the snake
		for (q = *head; q != NULL; q = q->next) {
			if (CompareCoordinate(r->cor, q->cor)) {  //if you meet an obstacle,score minus 1 and delete the last node in the snake list
				(*score)--;
				for (p = (*head)->next, pre = NULL; p->next != NULL; pre = p, p = p->next);      
				Pos(p->cor.X, p->cor.Y);
				SetColor(0);
				printf("¡ñ");
				pre->next = NULL;
				free(p);   
				r->cor = CreateObstacle(*head, food, *obstacle);
			}
		}
	}
}

