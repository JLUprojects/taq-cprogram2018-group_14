#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Header.h"
#include <graphics.h>

int main()
{
	snake *head;                
	COORD food;  
	int speed;   
	int score; 
	int direction;  
	int pause; 	
	int blood; 
	system("mode con cols=122 lines=31  ");//set the size of the console window
	PlayBackGroundMusic();
	FirstPage();

	pause = 0;
	while (pause != 32)
		pause = _getch();

	system("cls");
	speed = 200;
	score = 0;
	direction = DOWN;
	blood = BLOOD;
	CreateMap();
	PrintRules();
	head = InitializeSnake();
	CreateFood(&food, head);            
	pause = 0;
	while (pause != 32)//Press space to start the  game
		pause = _getch();

	for (;;) {
		if (GetDirection(&direction, &speed)== 1)
			break;
		MoveSnake(direction, &head,&food, &score, &speed);
		Pos(WIDTH + 4, HEIGHT / 2 + 5);
		SetColor(15);
		printf("Score: %d\n", score);
		Pos(WIDTH + 4, HEIGHT / 2 + 7);
		SetColor(12);
		printf("Blood: %d\n", blood);
		CreateBlood(&blood);
		Sleep(speed);
		AliveOrNot(food, head, &blood);
	}
	FreeSnake(head);
	return 0;
}

