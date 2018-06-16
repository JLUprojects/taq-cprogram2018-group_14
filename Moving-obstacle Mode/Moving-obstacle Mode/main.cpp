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
	Obstacle *obstacle;
	int speed;    
	int score;  
	int direction;  
	int highest = 0;  
	int pause; 
	int choice;
	int obstacle_number;
	int counter;
	errno_t err;
	FILE *file;

	IMAGE img;
	initgraph(970, 500);
	loadimage(&img, "cover.jpg");
	putimage(10, 10, &img);
	_getch();
	closegraph();

	system("mode con cols=128  lines=31  ");
	//PlayBackGroundMusic();  
	//you can put any music that you like in the Debug folder and excute this line of code
	// It must be a wav file and named "music", function defination is in Windows_API.cpp
	FirstPage();
	pause = 0;
	while (pause != 32)
		pause = _getch();
	

	newgame:
	system("cls");
	obstacle = NULL;
	obstacle_number = 0;
	speed = 200;
	score = 0;
	choice = NEWGAME;
	direction = DOWN;
	counter = 0;
	CreateMap();
	PrintRoles(&highest);

	if ((err = fopen_s(&file, "memory obstacle.txt", "rb")) == 0) {
		char ch = fgetc(file); fclose(file);
		if (ch != EOF) 
			choice = Choose();
	}

	if (choice == CONTINUE) {
		head = Load(&score, &direction, &speed, &obstacle_number);
		CreateFood(&food, head);
		int i; Obstacle *r;
		for (i = 0; i <obstacle_number; i++) //creat the linked list for obstacles 
			Add2Obstacle(CreateObstacle(head, food, obstacle), &obstacle);
		for (r = obstacle; r!=NULL; r = r->next) {
			Pos(r->cor.X, r->cor.Y);
			SetColor(15);
			printf("¡ö");
		}
	}
	else {
		head = InitializeSnake();
		CreateFood(&food, head);           
	}

	pause = 0;
	while (pause != 32)
		pause = _getch();

	for (;;) {
		
		if(GetDirection(&direction, &speed)==1)
			Save(&score, &direction, &speed, &obstacle_number,head);
		MoveSnake(direction, &head, &food, &score); 
			
		counter++;  //the speed of the obstacle is a quarter of the snake
		if(obstacle!=NULL&&counter%4==0)
			MoveObstacle(&obstacle, food, head);
		
		IfRunIntoObstacle(&head, &obstacle, &score,food);
		
		//if the player gets OBSTACL_COUNT more score ,creat a new obstacle
		if (score%OBSTACL_COUNT == 0&&score/ OBSTACL_COUNT != obstacle_number) {   
			obstacle_number++;
			Add2Obstacle(CreateObstacle(head, food, obstacle), &obstacle);
	
		if (AliveOrNot(head))
				break;
		}
		
		Pos(WIDTH + 4, HEIGHT / 2 + 5);
		SetColor(15);
		printf("Score: %d\n", score);
		Sleep(speed);

		if (AliveOrNot(head))
			break;
	}

	FreeSnake(head);
	FreeObstacle(obstacle);
	if (GameOver(score, highest) == NEWGAME)goto newgame;

	return 0;
}

