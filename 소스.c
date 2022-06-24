#include<stdio.h>
#include <stdlib.h>
typedef struct data {
	int score;
	char name[10];
}data;
typedef struct listnode* listpointer;
typedef struct listnode {
	data dat;
	listpointer link;
}listnode;
void print(listpointer* l) {
	printf("%d",(*l)->dat.score);
}
int main(void) {
	listpointer a, b;
	a = (listpointer)malloc(sizeof(listnode));
	a->dat.score = 10;
	print(a);
}