#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void Save(int *score, int *direction, COORD *food, int *speed, snake *head)
{
	FILE *mem; 
	errno_t err;
	snake *p = NULL;
	if ((err = fopen_s(&mem, "memory_singlemode.txt", "wb")) == 0) { 
		fwrite(score, 4U, 1, mem);
		fwrite(direction, 4U, 1, mem);
		fwrite(food, 4U, 1, mem);
		fwrite(speed, 4U, 1, mem);
		for (p = head; p != NULL; p = p->next)//save coordinate of every node 
			fwrite(&(p->cor), sizeof(p->cor), 1, mem);
		fclose(mem);
	}
	FreeSnake(head);
	exit(0);
}

snake* Load(int *score, int *direction, COORD *food, int *speed) //load the game 
{
	FILE *mem;   
	errno_t err;

	snake *p = NULL, *head = NULL, *q;
	int i;
	if ((err = fopen_s(&mem, "memory_singlemode.txt", "rb")) == 0) {
		fread(score, 4U, 1, mem);
		fread(direction, 4U, 1, mem);
		fread(food, 4U, 1, mem);
		fread(speed, 4U, 1, mem);

		head = (snake*)malloc(sizeof(snake)); //add new node to the end
		head->next = NULL;
		fread(&(head->cor), sizeof(COORD), 1, mem);
		q = head;
		for (i = *score + SNAKE_LEN - 2; i >= 0; i--) {
			p = (snake*)malloc(sizeof(snake));
			p->next = NULL;
			fread(&(p->cor), sizeof(COORD), 1, mem);
			q->next = p;
			q = p;
		}

		fclose(mem);
		p = head;
		Pos(p->cor.X, p->cor.Y);
		SetColor(10);
		printf("¡ð");
		p = p->next;
		while (p != NULL) {          
			Pos(p->cor.X, p->cor.Y);
			SetColor(10);
			printf("¡ñ");
			p = p->next;
		}

		Pos(food->X, food->Y);
		SetColor(13);
		printf("¡ï");
	}
	return head;
}

int Choose()//choose whether to start a new game or not
{
	int choice = 0;
	Pos(WIDTH + 4, 10);
	printf("1¡­¡­continue£»0¡­¡­new game\n");
	while (choice != CONTINUE && choice != NEWGAME)
		choice = _getch();
	switch (choice) {
	case CONTINUE:
		Pos(WIDTH + 4, 11);
		printf("You choose to continue.\n"); break;
	case NEWGAME:
		Pos(WIDTH + 4, 11);
		printf("You choose to start a new game.\n");
	}
	return choice;
}
