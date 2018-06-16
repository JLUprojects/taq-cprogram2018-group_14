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
	int highest = 0;  
	int pause; 	
	int choice;//choose whether to start a new game after saveing last time
	errno_t err;
	FILE *file;
	system("mode con cols=130 lines=40  ");//set the size of the console window
	
	initgraph(980, 500);
	IMAGE img;
	loadimage(&img, "cover.jpg");
	putimage(10, 10, &img);
	_getch();
	closegraph();
	
	//PlayBackGroundMusic();  
	//you can put any music that you like in the Debug folder and excute this line of code
	// It must be a wav file and named "music", function defination is in Windows_API.cpp
	FirstPage();

	pause = 0;
	while (pause != 32)
		pause = _getch();

	newgame:
	system("cls");
	speed = 200;
	score = 0;
	direction = DOWN;
	CreateMap();
	PrintRules(&highest);
	choice = NEWGAME;
	if ((err = fopen_s(&file, "memory_singlemode.txt", "rb")) == 0) {
		char ch = fgetc(file); fclose(file);
		if (ch != EOF) //if the file is not empty
			choice = Choose();//choose whether to continue the unfinished game
	}

	if (choice == CONTINUE)
		head = Load(&score, &direction, &food, &speed);
	else {
		head = InitializeSnake();
		CreateFood(&food, head);            
	}

	pause = 0;
	while (pause != 32)//Press space to start the  game
		pause = _getch();

	for (;;) {
		if (GetDirection(&direction, &speed)== 1)
			Save(&score, &direction, &food, &speed, head);
		MoveSnake(direction, &head, &food, &score); 
		Pos(WIDTH + 4, HEIGHT / 2 + 5);
		SetColor(15);
		printf("Score: %d\n", score);
		Sleep(speed);

		if (AliveOrNot(head))
			break;
	}

	FreeSnake(head);
	if (GameOver(score,highest)== NEWGAME)
		goto newgame;

	return 0;
}

