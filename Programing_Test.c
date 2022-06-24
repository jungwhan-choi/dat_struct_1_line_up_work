#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int element;
// 연결 스택과 연결 큐의 노드
typedef struct ListNode* listpointer;
typedef struct ListNode {
	element data;
	listpointer link;
} listnode;
typedef struct LinkedStack { // Stack의 top을 표현할 구조체
	listpointer top;
	int length;
} Stack;
typedef struct LinkedQueue { // Queue의 front, rear를 표현할 구조체
	listpointer front, * rear;
} Queue;
// 공백스택 생성
Stack* createStack() {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S->top = NULL;
	S->length = 0;
	return S;
}
// 공백큐 생성
Queue* createQueue() {
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}
// 스택의 모든 요소 출력
void displayStack(Stack* S) {
	listnode* p = S->top;
	printf("STACK [ ");
	while (p) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf(" ]\n");
}

void push(Stack s, element item) {
	listpointer temp = (listpointer)malloc(sizeof(listnode));
	temp->data = item;
	temp->link = NULL;
	if (!s.top) {
		s.top = temp;
	}
	else {
		temp->link = s.top;
		s.top = temp;
	}
	
}
int main(void) {
	int a[8];
	FILE* fp = fopen("stack_status.txt", "r");
	Stack* S = createStack();
	for (int i = 0; i < 8; i++) {
		fscanf(fp, "%d", a[i]);
		push(*S, a[i]);
	}
	displayStack(S);
	
}