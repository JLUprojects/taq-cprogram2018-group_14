#include <windows.h>
#include "Header.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

snake* InitializeSnake()//初始化蛇身 
{
	snake *p = NULL, *head;
	int i;
	for (i = 0; i < SNAKE_LEN; i++) {
		head = (snake*)malloc(sizeof(snake));
		head->next = p;
		head->cor.X = WIDTH / 2;
		head->cor.Y = HEIGHT / 2 + i;
		p = head;
	}

	Pos(p->cor.X, p->cor.Y);
	SetColor(10);
	printf("○");
	p = p->next;
	while (p != NULL) {              //从头到尾，输出蛇身
		Pos(p->cor.X, p->cor.Y);
		SetColor(10);
		printf("●");
		p = p->next;
	}
	HideCursor();
	return head;
}

/*改变速度函数  */
void ChangeSpeed(int *speed, int *isUpSpeed)
	{
		if (*isUpSpeed) {
			if ((*speed) > 50) {
				(*speed) -= 50;
			}
		}
		else {
			(*speed) += 50;
		}
	}

int GetDirection(int *direction, int *speed, int *isUpSpeed)//获取键盘输入
{
	int pause = 0;
	int new_dir = 0;
	if (_kbhit()) {
		new_dir = _getch();
		if (new_dir == 224 || new_dir == 0)new_dir = _getch();//_getch获取扩展字符要调用两次
		switch (new_dir) {
		case 32:     //按空格键暂停，再按空格键继续	
			while (pause != 32)
				pause = _getch(); break;
		case 59:    
			*isUpSpeed = 1;
			ChangeSpeed(speed, isUpSpeed);
			break;
		case 60:
			*isUpSpeed = 0;
			ChangeSpeed(speed, isUpSpeed);
			break;  

		case UP:
		case DOWN:
		case RIGHT:
		case LEFT:
			if (abs(new_dir - *direction) != 2 && abs(new_dir - *direction) != 8) {   //反方向无效， 参照键盘方向键的值 
				*direction = new_dir;
			} break;
		case ESC:
			new_dir = 1;
		}
	}
	return new_dir;
}
int CompareCoordinate(COORD pt1, COORD pt2)           //比较坐标函数
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y);
}

void CreatFood(COORD *food, snake *head)
{
	snake *p = NULL;
	int in_snake = 0;                    //判断食物是否落在了蛇身上， 默认为否 0 
	srand((unsigned int)time(NULL));

	do {
		in_snake = 0;
		int x = (rand() % (WIDTH - 5)) + 3;      //确保食物在框里
		food->X = (x % 2) ? x + 1 : x;      //而且横坐标是偶数
		food->Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head; p != NULL; p = p->next) {     //判断食物是否落在了蛇
			if (CompareCoordinate(p->cor, *food))
				in_snake = 1;
		}
	} while (in_snake);
}

void MoveSnake(int direction, snake **head, COORD *food, int *score, int *isUpSpeed, int *speed)   //蛇移动，同时判断是否吃到了食物并加分
{
	snake *p;
	COORD tail = (*head)->cor;      //保存原来的蛇头 */
	COORD temp;

	switch (direction) {                               //根据方向改变蛇头的坐标
	case UP:
		(*head)->cor.Y--; break;
	case DOWN:
		(*head)->cor.Y++; break;
	case RIGHT:
		(*head)->cor.X += 2; break;
	case LEFT:
		(*head)->cor.X -= 2; break;
	}

	Pos((*head)->cor.X, (*head)->cor.Y);            //打印新的蛇头 
	SetColor(10);
	printf("○");
	Pos(tail.X, tail.Y);
	printf("●"); HideCursor();

	for (p = (*head)->next; p != NULL; p = p->next) {    //更新蛇身坐标 
		temp = p->cor;
		p->cor = tail;          //tail是前一个节点的坐标    
		tail = temp;  //循环结束是tail是尾部的坐标
	}

	if (CompareCoordinate(*food, (*head)->cor)) {

		for (p = (*head)->next; p->next != NULL; p = p->next);        //找到尾部,空语句
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail;         //添加节点，坐标是更新前的尾部的坐标
		p->next->next = NULL;

		*isUpSpeed = (rand() % 2) ? 1 : 0; // 吃完食物后随机加速或减速
		ChangeSpeed(speed, isUpSpeed);

		CreatFood(food, (*head));            //生成新的食物
		Pos(food->X, food->Y);
		SetColor(13);
		printf("★");
		(*score)++;
	}
	else {
		//head在前已更改， 后面的节点改成前一节点的坐标 
		Pos(tail.X, tail.Y);//覆盖尾部
		SetColor(0);
		printf("●");
	}
}


