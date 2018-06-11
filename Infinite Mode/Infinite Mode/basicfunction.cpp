#include <windows.h>
#include "Header.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

snake* InitializeSnake()//��ʼ������ 
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
	printf("��");
	p = p->next;
	while (p != NULL) {              //��ͷ��β���������
		Pos(p->cor.X, p->cor.Y);
		SetColor(10);
		printf("��");
		p = p->next;
	}
	HideCursor();
	return head;
}

/*�ı��ٶȺ���  */
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

int GetDirection(int *direction, int *speed, int *isUpSpeed)//��ȡ��������
{
	int pause = 0;
	int new_dir = 0;
	if (_kbhit()) {
		new_dir = _getch();
		if (new_dir == 224 || new_dir == 0)new_dir = _getch();//_getch��ȡ��չ�ַ�Ҫ��������
		switch (new_dir) {
		case 32:     //���ո����ͣ���ٰ��ո������	
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
			if (abs(new_dir - *direction) != 2 && abs(new_dir - *direction) != 8) {   //��������Ч�� ���ռ��̷������ֵ 
				*direction = new_dir;
			} break;
		case ESC:
			new_dir = 1;
		}
	}
	return new_dir;
}
int CompareCoordinate(COORD pt1, COORD pt2)           //�Ƚ����꺯��
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y);
}

void CreatFood(COORD *food, snake *head)
{
	snake *p = NULL;
	int in_snake = 0;                    //�ж�ʳ���Ƿ������������ϣ� Ĭ��Ϊ�� 0 
	srand((unsigned int)time(NULL));

	do {
		in_snake = 0;
		int x = (rand() % (WIDTH - 5)) + 3;      //ȷ��ʳ���ڿ���
		food->X = (x % 2) ? x + 1 : x;      //���Һ�������ż��
		food->Y = (rand() % (HEIGHT - 1)) + 1;
		for (p = head; p != NULL; p = p->next) {     //�ж�ʳ���Ƿ���������
			if (CompareCoordinate(p->cor, *food))
				in_snake = 1;
		}
	} while (in_snake);
}

void MoveSnake(int direction, snake **head, COORD *food, int *score, int *isUpSpeed, int *speed)   //���ƶ���ͬʱ�ж��Ƿ�Ե���ʳ�ﲢ�ӷ�
{
	snake *p;
	COORD tail = (*head)->cor;      //����ԭ������ͷ */
	COORD temp;

	switch (direction) {                               //���ݷ���ı���ͷ������
	case UP:
		(*head)->cor.Y--; break;
	case DOWN:
		(*head)->cor.Y++; break;
	case RIGHT:
		(*head)->cor.X += 2; break;
	case LEFT:
		(*head)->cor.X -= 2; break;
	}

	Pos((*head)->cor.X, (*head)->cor.Y);            //��ӡ�µ���ͷ 
	SetColor(10);
	printf("��");
	Pos(tail.X, tail.Y);
	printf("��"); HideCursor();

	for (p = (*head)->next; p != NULL; p = p->next) {    //������������ 
		temp = p->cor;
		p->cor = tail;          //tail��ǰһ���ڵ������    
		tail = temp;  //ѭ��������tail��β��������
	}

	if (CompareCoordinate(*food, (*head)->cor)) {

		for (p = (*head)->next; p->next != NULL; p = p->next);        //�ҵ�β��,�����
		p->next = (snake *)malloc(sizeof(snake));
		p->next->cor = tail;         //��ӽڵ㣬�����Ǹ���ǰ��β��������
		p->next->next = NULL;

		*isUpSpeed = (rand() % 2) ? 1 : 0; // ����ʳ���������ٻ����
		ChangeSpeed(speed, isUpSpeed);

		CreatFood(food, (*head));            //�����µ�ʳ��
		Pos(food->X, food->Y);
		SetColor(13);
		printf("��");
		(*score)++;
	}
	else {
		//head��ǰ�Ѹ��ģ� ����Ľڵ�ĳ�ǰһ�ڵ������ 
		Pos(tail.X, tail.Y);//����β��
		SetColor(0);
		printf("��");
	}
}


