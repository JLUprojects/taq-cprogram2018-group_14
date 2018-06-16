#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void AliveOrNot(COORD food, snake *head, int *blood)
{
	CreateBlood(blood);
	int eat_self = 0;
	snake *p;
	for (p = head->next->next; p != NULL; p = p->next) {
		if (CompareCoordinate(head->cor, p->cor)) {
			eat_self = 1;
			break;
		}
	}
	//If break the rules
	if (head->cor.X == 0 || head->cor.X == WIDTH || head->cor.Y == 0 || head->cor.Y == HEIGHT || eat_self)
	{
		//cover the snake body
		snake *hp = head;
		while (hp != NULL) {              
			Pos(hp->cor.X, hp->cor.Y);
			printf(" ");
			hp = hp->next;
		}
		HideCursor();

		int x = (rand() % (WIDTH - 7)) + 3;
		head->cor.X = (x % 2) ? x + 1 : x;
		head->cor.Y = (rand() % (HEIGHT - 3)) + 1;
		
		if (--*blood < 0)
			*blood = 5;
		CreateBlood(blood);
		if (!eat_self) {
			CreateMap();
		}
	}
}

void FreeSnake(snake *head)//free the linked list
{
	snake *q, *p = NULL;
	for (p = head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}

