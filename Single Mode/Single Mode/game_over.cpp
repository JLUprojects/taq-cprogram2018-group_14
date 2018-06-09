#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int AliveOrNot(snake *head)
{
	int eat_self = 0;
	snake *p;
	for (p = head->next->next; p != NULL; p = p->next) {//compare coordinates of snake head and snake body
		if (CompareCoordinate(head->cor, p->cor)) {
			eat_self = 1;
			break;
		}
	}
	//if run into walls or eat itself
	if (head->cor.X == 0 || head->cor.X == WIDTH || head->cor.Y == 0 || head->cor.Y == HEIGHT || eat_self)
		return 1;
	return 0;
}

void FreeSnake(snake *head)//free the linked list
{
	snake *q, *p = NULL;
	for (p = head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}

int GameOver(int score, int highest)
{
	errno_t err;
	FILE *file;
	system("cls");
	int again;

	Pos(WIDTH / 2, HEIGHT / 2);
	SetColor(15);
	printf("Game over£¡Your score : %d\n", score);

	if (highest < score) {
		Pos(WIDTH / 2, HEIGHT / 2 + 1);
		printf("Congratulations! You have the highest score!");
		if ((err = fopen_s(&file, "HighestScore_singlemode.txt", "wb")) == 0) {
			fwrite(&score, 4U, 1, file);
			fclose(file);
		}
	}

	if ((err = fopen_s(&file, "memory_singlemode.txt", "wb")) == 0)
		fclose(file);   //empty the archive when game is over

	Pos(WIDTH / 2, HEIGHT / 2 + 3);
	printf("0¡­¡­again£»1¡­¡­exit");
	again = _getch();

	return again;
}