#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int AliveOrNot(COORD food, snake *head, int *blood)
{
	CreatBlood(blood);
	int eat_self = 0;
	snake *p;
	for (p = head->next->next; p != NULL; p = p->next) {//�ӵ��������ͷ���Ƚ����� 
		if (CompareCoordinate(head->cor, p->cor)) {
			eat_self = 1;
			break;
		}
	}
	//�Ƿ�ײǽ��Ե��Լ�
	if (head->cor.X == 0 || head->cor.X == WIDTH || head->cor.Y == 0 || head->cor.Y == HEIGHT || eat_self)
	{
		//�������õ�����
		snake *hp = head;
		Pos(hp->cor.X, hp->cor.Y);
		printf(" ");
		hp = hp->next;
		while (hp != NULL) {              //��ͷ��β���������
			Pos(hp->cor.X, hp->cor.Y);
			printf(" ");
			hp = hp->next;
		}
		HideCursor();

		int x = (rand() % (WIDTH - 7)) + 3;
		head->cor.X = (x % 2) ? x + 1 : x;
		head->cor.Y = (rand() % (HEIGHT - 3)) + 1;
		//	return 0;
		if (--*blood < 0)
			*blood = 5;
		CreatBlood(blood);
		if (!eat_self) {
			CreatMap();
		}



		return 1;
	}
	//	getchar;
	return 0;
}
void FreeSnake(snake *head)//��Ϸ�������ͷ�����
{
	snake *q, *p = NULL;
	for (p = head; p != NULL; p = q) {
		q = p->next;
		free(p);
	}
}

