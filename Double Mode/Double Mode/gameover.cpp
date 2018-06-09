#include "Header.h"
#include <stdio.h>
#include <conio.h>

int AliveOrNot(snake *head1, snake *head2)
{
	snake *p;
	for (p = head1->next->next; p != NULL; p = p->next) {   //if eats itself
		if (CompareCoordinate(head1->cor, p->cor))
			return 1;
	}
	for (p = head2->next; p != NULL; p = p->next) {
		if (CompareCoordinate(head1->cor, p->cor))
			return 1;
	}
    //if run into wall
	if (head1->cor.X == 0 || head1->cor.X == WIDTH || head1->cor.Y == 0 || head1->cor.Y == HEIGHT)return 1;
	
	for (p = head2->next->next; p != NULL; p = p->next) {
		if (CompareCoordinate(head2->cor, p->cor))
			return 2;
	}
	for (p = head1->next; p != NULL; p = p->next) { //if knocks the other
		if (CompareCoordinate(head2->cor, p->cor))
			return 2;
	}

	
	
	if (head2->cor.X == 0 || head2->cor.X == WIDTH || head2->cor.Y == 0 || head2->cor.Y == HEIGHT)return 2;

	if (CompareCoordinate(head1->cor, head2->cor))return 3; //two snakes bump together head to head
	return 0;
}

void FreeSnake(snake *head1, snake *head2)
{                                          
	snake *p = NULL, *q;
	for (p = head1; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
	for (p = head2; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}

int GameOver(int end, int score1, int score2)
{
	int again;
	system("cls");
	Pos(WIDTH / 2, HEIGHT / 2 - 1);
	SetColor(15);
	printf("Game Over£¡");

	switch (end) {
	case 0:
		Pos(WIDTH / 2, HEIGHT / 2 + 1);
		printf("Score of green snake£º%d", score1);
		Pos(WIDTH / 2, HEIGHT / 2 + 2);
		printf("Score of bule snake£º%d", score2);
		break;
	case 1:
		Pos(WIDTH / 2, HEIGHT / 2 + 1);
		printf("Green snake break the roles, score minus 5£º%d-5=%d", score1, score1 - 5);
		Pos(WIDTH / 2, HEIGHT / 2 + 2);
		printf("Score of bule snake£º%d", score2);
		score1 -= 5;
		break;
	case 2:
		Pos(WIDTH / 2, HEIGHT / 2 + 1);
		printf("Score of green snake£º%d", score1);
		Pos(WIDTH / 2, HEIGHT / 2 + 2);
		printf("Blue snake break the roles, score minus 5£º%d-5=%d", score2, score2 - 5);
		score2 -= 5;
		break;
	case 3:
		Pos(WIDTH / 2, HEIGHT / 2 + 1);
		printf("You bumped together head to head!");
		Pos(WIDTH / 2, HEIGHT / 2 + 2);
		printf("Score of green snake£º%d", score1);
		Pos(WIDTH / 2, HEIGHT / 2 + 3);
		printf("Score of blue snake£º%d", score2);
		break;
	}
	Pos(WIDTH / 2, HEIGHT / 2 + 4);
	if (score1 > score2)
		printf("Green snake is winner£¡");
	else if (score1 < score2)
		printf("Blue snake is winner£¡");
	else
		printf("Draw!");

	Pos(WIDTH / 2, HEIGHT / 2 + 6);
	printf("0¡­¡­again£»1¡­¡­exit");
	again = _getch();
	return again;
}
