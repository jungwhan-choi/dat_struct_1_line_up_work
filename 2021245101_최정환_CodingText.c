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
	listpointer front,  rear;
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
void displayQueue(Queue* Q) {
	listnode* p = Q->front;
	printf("Queue [ ");
	while (p) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf(" ]\n");
}
void deleteQ(Queue* Q) {
	listpointer temp = NULL;
	listpointer next = NULL;
	next = Q->front;
	while (next->link) {
		temp = next;
		next = next->link;
	}
	if (Q->front == Q->rear) {
		Q->front = NULL;
		Q->rear == NULL;
		
	}
	else {
		Q->rear = temp;
		temp->link = NULL;
		
	}
	
}
void reverse(Stack* S,int k) {
	Queue* Q = createQueue();
	listpointer temp=NULL;
	listpointer temp2 = NULL;
	for (int i = k; i >0; i--) {
		listpointer next = S->top;
		int j = i;
		while (j>=1) {
			temp = next;
			next = next->link;
			j--;
		}
		qpush(Q, temp->data);
		
	}
	displayQueue(Q);
	temp = S->top;
	for (int i = 0; i <k; i++) {
		temp->data = Q->rear->data;
		temp = temp->link;
		deleteQ(Q);
	}
	
}
void spush(Stack* s, element item) {
	listpointer temp = (listpointer)malloc(sizeof(listnode));
	temp->data = item;
	temp->link = NULL;
	if (s->top==NULL) {
		s->top = temp;
	}
	else {
		temp->link = s->top;
		s->top = temp;
	}

}
int qpush(Queue* s, element item) {										//왜 int?????
	listpointer temp = (listpointer)malloc(sizeof(listnode));
	temp->data = item;
	temp->link = NULL;
	if (s->front == NULL) {
		s->rear = temp;
		s->front = temp;
	}
	else {
		temp->link = s->front;
		s->front = temp; 
	}
}
int main(void) {
	int n;
	int element;
	int k;
	FILE* fp = fopen("stack_status.txt", "r");
	if (!fp) {
		printf("failed");
	}
	fscanf(fp, "%d", &n);
	Stack* S = createStack();
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d", &element);
		spush(S, element);
	}
	displayStack(S);
	while (1) {
		printf("k 입력:");
		scanf("%d", &k);
		if (k > n) {
			printf("잘못 입력함\n");
			continue;
		}
		reverse(S, k);
		displayStack(S);
	}
	

}