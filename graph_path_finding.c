#define _CRT_SECURE_NO_WARNINGS
#define max_vertex 12

#include <stdio.h>
#include <stdlib.h>

typedef struct listnode* listpointer;
typedef struct listnode {
	int num;
	listpointer link;
}listnode;
typedef struct ArrayStack {
	int top;
	int data[max_vertex];
}ArrayStack;
typedef ArrayStack stack;
void MKstack(stack* s) {
	s->top = -1;
}
void push(stack* s,int node) {
	s->top++;
	s->data[s->top] = node;
}
void pop(stack* s) {
	s->top--;
}

double cost[max_vertex][max_vertex];
listpointer graph[max_vertex];
double distance[max_vertex];
stack s;
int pred[max_vertex], set_S[max_vertex], found[max_vertex];

void makenode(listpointer* p, int n) {					//list_maker �Լ��� ���̴� ��� �����Ҵ� �Լ�
	listpointer new;
	new = (listpointer)malloc(sizeof(listnode));
	new->num = n;
	new->link = NULL;
	(*p)->link = new;
}		

void cost_maker() {										//cost[max_vertex][max_vertex] matrix�� �� �Ҵ�
	for (int i = 0; i < max_vertex; i++) {				//cost matrix�� -1�� ��ü �ʱ�ȭ
		for (int j = 0; j < max_vertex; j++) {
			cost[i][j] = -1;
		}
		
	}
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;					//vt:��������, next_vt: ���ϻ��� ���� ����,e: EOFȮ�ο�
		char v = NULL;									//v: ���� �ٹٲ� Ȯ�ο�
		double value = 0;											
		fscanf(fp, "%d", &vt);
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf", &value);
			e = fscanf(fp, "%c", &v);
			cost[vt][next_vt] = value;
			if (v == '\n' || e == EOF) {
				break;
			}
		} while (1);
		if (e == EOF) {
			break;
		}
	}
}

void list_maker() {										//���� ����Ʈ ����
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;
		char v = NULL;
		double value = 0;
		fscanf(fp, "%d", &vt);
		graph[vt] = (listpointer)malloc(sizeof(listnode));		//�� ù ���� �����Ҵ�
		listpointer temp = graph[vt];					
		temp->num = vt;									//�� ó�� ��������� �ѹ� �ο�
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf", &value);
			e = fscanf(fp, "%c", &v);
			makenode(&temp, next_vt);					//makenode �Լ� ���( �ݺ����� Ȱ���� ��������Ʈ ����)
			temp = temp->link;
			if (v == '\n' || e == EOF) {
				break;
			}
		} while (1);
		
		if (e == EOF) {
			break;
		}
	}
}

void read_and_make_graph() {							//cost_maker, list_maker �Լ��� Ȱ���� matrix�� ����list ����
	cost_maker();
	list_maker();
}

void DFS(int n,int d) {
	listpointer w;
	found[n] = 1;
	for (w = graph[n]; w; w = w->link) {
		if (!found[w->num]) {
			pred[w->num] = n;
			DFS(w->num,d);
		}
	}
}

int shortest_path (int start,int dest){

}
int main() {
	int s=0 ,d=0;
	char m = NULL;
	read_and_make_graph();
	MKstack(&s);
	for (int i = 0; i < max_vertex; i++) {
		pred[i] = 0;
		found[i] = 0;
	}
	printf("�ּҰ�θ� ã�� �� ������ �Է��ϼ���>");
	scanf("%c%d%d", m, &s, &d);
}