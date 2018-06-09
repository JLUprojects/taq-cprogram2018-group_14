#include <windows.h>
#include "Header.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

snake* InitializeSnake()
{
	snake *p = NULL, *head;
	int i;
	for (i = 0; i <SNAKE_LEN; i++) {
		head = (snake*)malloc(sizeof(snake));
		head->next = p;
		head->cor.X = WIDTH / 2;
		head->cor.Y = HEIGHT / 2 + i;
		p = head;
	}

	Pos(p->cor.X, p->cor.Y);
	SetColor(10);
	printf("○");
	p = p->next;
	while (p != NULL) {             
		Pos(p->cor.X, p->cor.Y);
		SetColor(10);
		printf("●");
		p = p->next;
	}
	HideCursor();
	return head;
}

int GetDirection(int *direction, int *speed)
{
	int pause = 0;
	int new_dir = 0;
	if (_kbhit()) {
		new_dir = _getch();
		if (new_dir == 224 || new_dir == 0)new_dir = _getch();
		switch (new_dir) {
		case 32:    
			while (pause != 32)
				pause = _getch(); break;
		case 59:   
			if ((*speed) >= 50)
				(*speed) -= 50; break;
		case 60:
			(*speed) += 50; break;  
		case UP:
		case DOWN:
		case RIGHT:
		case LEFT:
			if (abs(new_dir - *direction) != 2 && abs(new_dir - *direction) != 8) {   //反方向无效， 参照键盘方向键的值 
				*direction = new_dir; break;
			}
		case ESC:
			new_dir = 1;
		}
	}
	return new_dir;
}

void CreateFood(COORD *food, snake *head)
{
	snake *p = NULL;
	int in_snake = 0;                    
	srand((unsigned int)time(NULL));

	do {
		in_snake = 0;
		int x = (rand() % (WIDTH - 5)) + 3;     
		food->X = (x % 2) ? x + 1 : x;    
		food->Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head; p != NULL; p = p->next) {    
			if (CompareCoordinate(p->cor, *food))
				in_snake = 1;
		}
	} while (in_snake);

	Pos(food->X, food->Y);
	SetColor(13);
	printf("★");
}

void MoveSnake(int direction, snake **head, COORD *food, int *score)   
{
	snake *p;
	COORD tail = (*head)->cor;      
	COORD temp;

	switch (direction) {                              
	case UP:
		(*head)->cor.Y--; break;
	case DOWN:
		(*head)->cor.Y++; break;
	case RIGHT:
		(*head)->cor.X += 2; break;
	case LEFT:
		(*head)->cor.X -= 2; break;
	}

	Pos((*head)->cor.X, (*head)->cor.Y);          
	SetColor(10);
	printf("○");
	Pos(tail.X, tail.Y);
	printf("●"); HideCursor();

	for (p = (*head)->next; p != NULL; p = p->next) {    
		temp = p->cor;
		p->cor = tail;          
		tail = temp; 
	}

	if (CompareCoordinate(*food, (*head)->cor)) {

		for (p = (*head)->next; p->next != NULL; p = p->next);       
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail;        
		p->next->next = NULL;

		CreateFood(food, (*head));           
		Pos(food->X, food->Y);
		SetColor(13);
		printf("★");
		(*score)++;
	}
	else {
		Pos(tail.X, tail.Y);
		SetColor(0);
		printf("●");
	}
}

