#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "Header.h"

int main() {
	int end, running_time, timelimit = TIMELIMIT;
	int dir1, dir2;
	COORD food1, food2;
	int score1, score2;
	snake *head1, *head2;
	time_t start_time;
	int pause, again;
	int create_food;
	system("mode con cols=128 lines=31  ");
	FirstPage();
	//PlayBackGroundMusic();  
	//you can put any music that you like in the Debug folder and excute this line of code
	// It must be a wav file and named "music", function defination is in Windows_API.cpp
	pause = 0;
	while (pause != 32)
		pause = _getch();

newgame: 
	system("cls");
	dir1 = DOWN; dir2 = W;
	score1 = 0; score2 = 0;
	food1 = { 0,0 }; food2 = { 0,0 };

	PrintRules();
	CreateMap();
	head1 = InitializeSnake(4, 1, 10);
	head2 = InitializeSnake(-4, -1, 11);

	pause = 0;
	while (pause != 32)
		pause = _getch();

	start_time = time(NULL);
	food1 = CreateFood(13, 10, head1, head2, food1, food2);       //creat foods for both snake
	food2 = CreateFood(14, 20, head1, head2, food1, food2);

	for (;;) {
		GetDirection(&dir1, &dir2);

		create_food = MoveSnake1(dir1, &head1, food1, food2, &score1);
		switch (create_food) {
		case 1:
			food1 = CreateFood(13, 10, head1, head2, food1, food2); break;
		case 2:
			food2 = CreateFood(14, 20, head1, head2, food1, food2); break;
		case 0:break;
		}

		create_food = MoveSnake2(dir2, &head2, food1, food2, &score2);
		switch (create_food) {
		case 1:
			food1 = CreateFood(13, 10, head1, head2, food1, food2); break;
		case 2:
			food2 = CreateFood(14, 20, head1, head2, food1, food2); break;
		case 0:break;
		}
		Sleep(250);

		Pos(WIDTH + 4, HEIGHT / 2);
		SetColor(15);
		printf("Score of green snake£º%d", score1);
		Pos(WIDTH + 4, HEIGHT / 2 + 1);
		printf("Score of bule snake£º%d", score2);
		running_time = (int)difftime(time(NULL), start_time);
		Pos(WIDTH + 4, HEIGHT / 2 + 3);
		printf("You still have %d minutes %d seconds.", timelimit - (running_time / 60) - 1, 60 - (running_time % 60));

		end = AliveOrNot(head1, head2);
		if (end || (running_time / 60)>TIMELIMIT)
			break;

	}

	FreeSnake(head1, head2);
	again = GameOver(end, score1, score2);
	if (again = NEWGAME)
		goto newgame;

	return 0;
}

