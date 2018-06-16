#include <windows.h>
#include "Header.h"
#include <stdio.h>

void CreateMap()
{
	SetColor(15);
	int i;
	for (i = 0; i <= WIDTH; i += 2) {          //print the wall,one square needs 2 unit of x-coordinate  
		Pos(i, 0); printf("¡ö");
		Pos(i, HEIGHT); printf("¡ö");
	}
	for (i = 0; i <= HEIGHT; i++) {            
		Pos(0, i); printf("¡ö");
		Pos(WIDTH, i); printf("¡ö");
	}
	HideCursor();
}

void CreateBlood(int *blood)
{
	SetColor(12);
	int i;
	if (*blood <= 0) {
		*blood = BLOOD;
	}
	for (i = 0; i < *blood * 2; i += 2)
	{        
		Pos(WIDTH + 10 + i, HEIGHT / 2 + 8); printf("¡ô");
	}
	SetColor(15);
	for (; i < 10; i += 2)
	{        
		Pos(WIDTH + 10 + i, HEIGHT / 2 + 8); printf("¡ó");
	}

}

void FirstPage()
{
	printf("Welcome to Snake +!¡ª¡ªInfinite Mode\n\n");
	printf("Rules£º\n");
	printf("1.Press arrow keys to control the movement of the snake.\n");
	printf("2.Press space key to pause or continue.\n");
	printf("3.Press F1 to speed up and F2 to slow down.\n");
	printf("4.Press ESC to exit.\n");
	printf("5.Speed will change randomly after you ate a food.\n");
	printf("Press space key to enter the game.");
	HideCursor();
}

void PrintRules()
{
	Pos(WIDTH + 4, 1);
	printf("Rules£º");
	Pos(WIDTH + 4, 2);
	printf("1.Press arrow keys to control the movement of the snake.");
	Pos(WIDTH + 4, 3);
	printf("2.Press space key to pause or continue.");
	Pos(WIDTH + 4, 4);
	printf("3.Press F1 to speed up and F2 to slow down.");
	Pos(WIDTH + 4, 5);
	printf("4.Press ESC to exit.");
	Pos(WIDTH + 4, 6);
	printf("5.Speed will change randomly after you ate a food.\n");
	Pos(WIDTH + 4, 7);
	printf("Press space key to start!");
}
