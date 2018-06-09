#include "Header.h"
#include <Windows.h>
#include <stdio.h>

void CreatMap()
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
}


void PrintRules()
{
	int timelimit = TIMELIMIT;
	Pos(WIDTH + 4, 1);
	printf("Rules£º");
	Pos(WIDTH + 4, 2);
	printf("1.Press the arrow keys to control the movement of green snake,");
	Pos(WIDTH + 4, 3);
	printf("  eat red food");
	Pos(WIDTH + 4, 4);
	printf("2.Press the a/w/s/d keys to control the movement of blue snake,");
	Pos(WIDTH + 4, 5);
	printf("  eat yellow food");
	Pos(WIDTH + 4, 6);
	printf("3.Eat your opponent's food ,score minus 1");
	Pos(WIDTH + 4, 7);
	printf("4.If you run into the wall/eat yourself/bump your opponent");
	Pos(WIDTH + 4,8);
	printf("   the game will be ended and your score will minus 5");
	Pos(WIDTH + 4, 9);
	printf("5.The one who gets a higher score in %d minutes is winner", timelimit);
	Pos(WIDTH + 4, 11);
	printf("Press space key to start the game!");
}

void FirstPage()
{
	int timelimit = TIMELIMIT;
	printf("Welcome to Snake +¡ª¡ªDouble Mode!\n\n");
	printf("Please change your input method to English mode first!\n\n");
	printf("Rules£º\n");
	printf("1.Press the arrow keys to control the movement of green snake,eat red food\n");
	printf("2.Press the a/w/s/d keys to control the movement of blue snake,eat yellow food\n");
	printf("3.Eat your opponent's food ,score minus 1\n");
	printf("4.If you run into the wall/eat yourself/bump your opponent\n");
	printf("   the game will be ended and your score will minus 5\n");
	printf("5.The one who gets a higher score in %d minutes is winner\n\n", timelimit);
	printf("Press space key to continue");
	HideCursor();
}
