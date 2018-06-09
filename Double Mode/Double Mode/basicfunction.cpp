#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Header.h"

snake* InitializeSnake(int n, int dir, int color)
{
	snake *p = NULL, *head;
	int i;
	for (i = 0; i <SNAKE_LEN; i++) {
		head = (snake*)malloc(sizeof(snake));
		head->next = p;
		head->cor.X = WIDTH / 2 + n;
		head->cor.Y = HEIGHT / 2 + i * dir;
		p = head;
	}
	Pos(p->cor.X, p->cor.Y);
	SetColor(color);
	printf("¡ð");
	p = p->next;
	while (p != NULL) {          
		Pos(p->cor.X, p->cor.Y);
		printf("¡ñ");
		p = p->next;
	}
	HideCursor();
	return head;
}


COORD CreatFood(int color, int n, snake *head1, snake *head2, COORD food1, COORD food2)
{
	COORD food;
	snake *p = NULL;
	int recreat, nothing;                 
	srand((unsigned int)time(NULL) + n);//two function call in the main function to creat foods for both snakes
	                                                            //are so close that their time are the same
	                                                            //so change the argument of srand
	do {
		recreat = 0;

		int x = (rand() % (WIDTH - 5)) + 3;       //make sure that food is in the map
		food.X = (x % 2) ? x + 1 : x;      //x-coordinate is even number
		food.Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head1; p != NULL; p = p->next) {    //if food coincides with snake1
			if (CompareCoordinate(p->cor, food))
			{
				recreat = 1; goto creatfood;
			}
		}
		for (p = head2; p != NULL; p = p->next) {     //if food coincides with snake2
			if (CompareCoordinate(p->cor, food))
			{
				recreat = 1; goto creatfood;
			}
		}
		if (CompareCoordinate(food1, food))
		{
			recreat = 1; goto creatfood;
		}

		if (CompareCoordinate(food2, food))
		{
			recreat = 1; goto creatfood;
		}
	creatfood:
		nothing = 0;//no meaning,it seems that there must have something after goto identification
	} while (recreat);

	Pos(food.X, food.Y);
	SetColor(color);
	printf("¡ï");
	return food;
}

void GetDirection(int *dir1, int *dir2)
{
	int dir_t = 0;
	if (_kbhit()) {
		dir_t = _getch();
		if (dir_t == 224)   //
			dir_t = _getch();
	}
	//only arrow keys and awsd are valid
	if ((dir_t == 72 || dir_t == 75 || dir_t == 77 || dir_t == 80) && abs(dir_t - *dir1) != 2 && abs(dir_t - *dir1) != 8) {
		*dir1 = dir_t;
	}
	else if ((dir_t == 100 || dir_t == 97 || dir_t == 115 || dir_t == 119) && abs(dir_t - *dir2) != 3 && abs(dir_t - *dir2) != 4) {
		*dir2 = dir_t;
	}
}

int MoveSnake1(int dir1, snake **head1, COORD food1, COORD food2, int *score1)
{
	snake *p, *q;
	COORD tail1 = (*head1)->cor, temp; 

									
	switch (dir1) {
	case UP:
		(*head1)->cor.Y--; break;
	case DOWN:
		(*head1)->cor.Y++; break;
	case RIGHT:
		(*head1)->cor.X += 2; break;
	case LEFT:
		(*head1)->cor.X -= 2; break;
	}

	Pos((*head1)->cor.X, (*head1)->cor.Y);           
	SetColor(10);
	printf("¡ð");
	Pos(tail1.X, tail1.Y);
	printf("¡ñ"); HideCursor();

	for (p = (*head1)->next; p != NULL; p = p->next) {    
		temp = p->cor;
		p->cor = tail1;           
		tail1 = temp;
	}

	if (CompareCoordinate(food1, (*head1)->cor)) {    //snake 1 eats its own food   
		(*score1)++;
		for (p = (*head1)->next; p->next != NULL; p = p->next);     
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail1;        
		p->next->next = NULL;
		return 1;          //creat food1
	}
	else if (CompareCoordinate(food2, (*head1)->cor)) { //snake1 eats food2
		(*score1)--;
		Pos(tail1.X, tail1.Y);//cover the previous tail
		SetColor(0);
		printf("¡ñ");
		for (p = (*head1)->next, q = NULL; p->next != NULL; q = p, p = p->next);    //find the end of the list     
		Pos(p->cor.X, p->cor.Y);//cover the present tail
		printf("¡ñ");
		q->next = NULL;
		free(p);
		return 2;        //creat food 2
	}
	else {
		Pos(tail1.X, tail1.Y);
		SetColor(0);
		printf("¡ñ");
		return 0;
	}
}

int MoveSnake2(int dir2, snake **head2, COORD food1, COORD food2, int *score2)
{
	snake *p, *q;
	COORD tail2 = (*head2)->cor, temp;

	switch (dir2) {
	case W:
		(*head2)->cor.Y--; break;
	case S:
		(*head2)->cor.Y++; break;
	case D:
		(*head2)->cor.X += 2; break;
	case A:
		(*head2)->cor.X -= 2; break;
	}
	Pos((*head2)->cor.X, (*head2)->cor.Y);            
	SetColor(11);
	printf("¡ð");
	Pos(tail2.X, tail2.Y);
	printf("¡ñ"); HideCursor();

	for (p = (*head2)->next; p != NULL; p = p->next) {   
		temp = p->cor;
		p->cor = tail2;               
		tail2 = temp;
	}



	if (CompareCoordinate(food2, (*head2)->cor)) {
		(*score2)++;
		for (p = (*head2)->next; p->next != NULL; p = p->next);        
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail2;       
		p->next->next = NULL;
		return 2;       
	}
	else if (CompareCoordinate(food1, (*head2)->cor)) { 
		(*score2)--;
		Pos(tail2.X, tail2.Y);
		SetColor(0);
		printf("¡ñ");
		for (p = (*head2)->next, q = NULL; p->next != NULL; q = p, p = p->next);       
		Pos(p->cor.X, p->cor.Y);
		printf("¡ñ");
		q->next = NULL;
		free(p);
		return 1;          
	}
	else {
		Pos(tail2.X, tail2.Y);
		SetColor(0);
		printf("¡ñ");
		return 0;
	}
}
