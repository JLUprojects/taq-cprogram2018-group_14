#include <windows.h>
#include "Header.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>



snake* InitializeSnake()//creat a linked list at the center of the map
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
	printf("¡ð");
	p = p->next;
	while (p != NULL) {              //print the snake
		Pos(p->cor.X, p->cor.Y);
		SetColor(10);
		printf("¡ñ");
		p = p->next;
	}
	HideCursor();
	return head;
}

int GetDirection(int *direction, int *speed)//capture key presses from the user
{
	int pause = 0;
	int new_dir = 0;
	if (_kbhit()) {
		new_dir = _getch();
		if (new_dir == 224 || new_dir == 0)new_dir = _getch();//use _getch twice to capture function keys
		switch (new_dir) {
		case 32:     //presse space key to pause
			while (pause != 32)
				pause = _getch(); break;
		case 59:
			if ((*speed) > 50) {
				(*speed) -= 50;
			}
			break;
		case 60:
			(*speed) += 50;
			break;
		case UP:
		case DOWN:
		case RIGHT:
		case LEFT:
			if (abs(new_dir - *direction) != 2 && abs(new_dir - *direction) != 8) {   //opposite direction is invalid 
				*direction = new_dir; break;
			}
		case ESC:
			new_dir = 1; break;
		default:
			new_dir = 0; break;
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
		int x = (rand() % (WIDTH - 5)) + 3;      //make sure that food is in the map
		food->X = (x % 2) ? x + 1 : x;      //x-coordinate is even number
		food->Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head; p != NULL; p = p->next) {     //if food coincides with snake
			if (CompareCoordinate(p->cor, *food))
				in_snake = 1; break;
		}
	} while (in_snake);

	Pos(food->X, food->Y);
	SetColor(13);
	printf("¡ï");
}

void MoveSnake(int direction, snake **head, COORD *food, int *score,int *speed) //move snake 
{
	snake *p;
	COORD tail = (*head)->cor;      //save the previous coordinate of snake head
	COORD temp;

	switch (direction) {                               //change the coordinate of snake head 
	case UP:
		(*head)->cor.Y--; break;
	case DOWN:
		(*head)->cor.Y++; break;
	case RIGHT:
		(*head)->cor.X += 2; break;
	case LEFT:
		(*head)->cor.X -= 2; break;
	}

	Pos((*head)->cor.X, (*head)->cor.Y);            //print new head 
	SetColor(10);
	printf("¡ð");
	Pos(tail.X, tail.Y);
	printf("¡ñ"); HideCursor();

	for (p = (*head)->next; p != NULL; p = p->next) {    //update the coordinates of snake body 
		temp = p->cor;
		p->cor = tail;
		tail = temp;  //when the loop is over,tail is the coordinate of the previous snake tail 
	}

	if (CompareCoordinate(*food, (*head)->cor)) {

		for (p = (*head)->next; p->next != NULL; p = p->next);        //find the end of the linked list 
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail;         //add a new node whose coordinate is the previous snake tail 
		p->next->next = NULL;
		
		if (rand() % 2) {
			if ((*speed) > 50) {
				(*speed) -= 50;
			}
		}
		else {
			(*speed) += 50;
		}
		CreateFood(food, (*head));            //creat a new food
		(*score)++;
	}
	else {
		Pos(tail.X, tail.Y);//cover the previous snake tail 
		SetColor(0);
		printf("¡ñ");
	}
}

