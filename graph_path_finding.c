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

void makenode(listpointer* p, int n) {					//list_maker 함수에 쓰이는 노드 공간할당 함수
	listpointer new;
	new = (listpointer)malloc(sizeof(listnode));
	new->num = n;
	new->link = NULL;
	(*p)->link = new;
}		

void cost_maker() {										//cost[max_vertex][max_vertex] matrix에 값 할당
	for (int i = 0; i < max_vertex; i++) {				//cost matrix를 -1로 전체 초기화
		for (int j = 0; j < max_vertex; j++) {
			cost[i][j] = -1;
		}
		
	}
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;					//vt:시작정점, next_vt: 파일상의 다음 정점,e: EOF확인용
		char v = NULL;									//v: 파일 줄바꿈 확인용
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

void list_maker() {										//인점 리스트 생성
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;
		char v = NULL;
		double value = 0;
		fscanf(fp, "%d", &vt);
		graph[vt] = (listpointer)malloc(sizeof(listnode));		//맨 첫 정점 공간할당
		listpointer temp = graph[vt];					
		temp->num = vt;									//맨 처음 정점노드의 넘버 부여
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf", &value);
			e = fscanf(fp, "%c", &v);
			makenode(&temp, next_vt);					//makenode 함수 사용( 반복문을 활용한 인접리스트 생성)
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

void read_and_make_graph() {							//cost_maker, list_maker 함수를 활용해 matrix와 인전list 생성
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
	printf("최소경로를 찾을 두 정점을 입력하세요>");
	scanf("%c%d%d", m, &s, &d);
}