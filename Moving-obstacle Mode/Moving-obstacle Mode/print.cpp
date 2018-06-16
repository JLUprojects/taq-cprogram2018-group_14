#include <windows.h>
#include "Header.h"
#include <stdio.h>

void CreateMap()
{
	SetColor(15);
	int i;
	for (i = 0; i <= WIDTH; i += 2) {        
		Pos(i, 0); printf("¡ö");
		Pos(i, HEIGHT); printf("¡ö");
	}
	for (i = 0; i <= HEIGHT; i++) {        
		Pos(0, i); printf("¡ö");
		Pos(WIDTH, i); printf("¡ö");
	}
	HideCursor();
}


void FirstPage()
{
	int x = OBSTACL_COUNT;
	printf("Welcome to Snake +!¡ª¡ªMoving Obstacle Mode\n\n");
	printf("Rules£º\n");
	printf("1.Press the arrow keys to control the movement of the snake.\n");
	printf("2.Press space key to pause and continue.\n");
	printf("3.Press F1 to speed up and F2 to slow down.\n");
	printf("4.Press ESC to exit and save.\n");
	printf("5.An obstacle will be created every time you get %d more points.\n",x);
	printf("Press space key to enter the game.");
	HideCursor();
}

void PrintRoles(int *highest)
{
	int x = OBSTACL_COUNT;
	Pos(WIDTH + 4, 1);
	printf("Rules£º");
	Pos(WIDTH + 4, 2);
	printf("1.Press the arrow keys to control the movement of the snake.");
	Pos(WIDTH + 4, 3);
	printf("2.Press space key to pause and continue.");
	Pos(WIDTH + 4, 4);
	printf("3.Press F1 to speed up and F2 to slow down.");
	Pos(WIDTH + 4, 5);
	printf("4.Press ESC to exit and save.");
	Pos(WIDTH + 4, 6);
	printf("5.An obstacle will be created every time you get %d more points.",x);
	Pos(WIDTH + 4, 7);
	printf("Press space key to start!");
	errno_t err;
	FILE *file;
	if ((err = fopen_s(&file, "HighestScore obstacle.txt", "rb")) == 0) {
		fread(highest, 4U, 1, file);
		fclose(file);
	}
	Pos(WIDTH + 4, 8);
	printf("Highest Score£º%d", *highest);
}

