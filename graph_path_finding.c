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
int pop(stack* s) {
	int p = 0;
	p = s->data[s->top];
	s->top--;
	return p;
}

double cost[max_vertex][max_vertex];
listpointer graph[max_vertex];
double distance[max_vertex];
stack s;
int pred[max_vertex], set_S[max_vertex], found[max_vertex];

int stack_search(int v) {								//스택에 원소 삽입 시 겹치는 원소 없는지 확인
	if (s.top == -1) {
		return 1;
	}
	for (int i = 0; i < s.top; i++) {
		if (s.data[i] == v) {
			return 0;
		}
	}
	return 1;
}

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

int get_unvisited_neighbor(int v) {						//노드의 이웃 중 가장 방문이 되지않은 가장 가까운 노드번호 반환
	listpointer w;
	w = graph[v];
	do {
		if (!found[(w->link)->num]) {
			return (w->link)->num;
		}
		else {
			w = w->link;
		}
	} while (w->link != NULL);
	return -1;
}

void DFS(int start,int dest) {							//DFS경로서칭
	int v = start;
	int w=0;
	pred[v] = -1;
	do {
		found[v] = 1;
		Label_NB:
		w = get_unvisited_neighbor(v);
		if (w >= 0) {
			if (stack_search(v)) {
				push(&s, v);
			}
			if (w == dest) {
				push(&s, w);
				break;
			}
			pred[w] = v;
			v = w;
			continue;
		}
		else {
			if (s.top == -1) {
				break;
			}
			else {
				if (stack_search(v)) {
					push(&s, v);
				}
				v = pred[v];
				goto Label_NB;
			}
		}
	} while (1);
	return 0;
}

int choose_shortest() {
	double a = 100;
	int b = 0;
	for (int i = 0; i < max_vertex; i++) {
		if (distance[i] != -1 && set_S[i] != 1) {
			if (distance[i] < a) {
				a = distance[i];
				b = i;
			}
		}
	}
	return b;
}
double Dijikstra (int start,int dest){						//다익스트라 경로서칭
	int i = 0, u = 0, w = 0;
	for (; i < max_vertex; i++) {
		set_S[i]= 0; 
		distance[i] = cost[start][i];
		
		if (cost[start][i] != -1) {
			pred[i] = start;
		}
		else {
			pred[i] = -1;
		}
	}
	
	printf("\n\n");
	push(&s, start);
	set_S[start] = 1;
	distance[start] = -1;
	int step = 1;
	printf("\n\n");
	for (i = 0; i < max_vertex - 2; i++) {
		u = choose_shortest();
		if (s.data[s.top] != dest) {
			push(&s, u);
		}
		
		set_S[u] = 1;
		for (w=0; w < max_vertex; w++) {
			if (!set_S[w]) {
				if (distance[w] == -1&&cost[u][w]!=-1) {
					distance[w] = distance[u] + cost[u][w];
					pred[w] = u;
				}
				else if (distance[w]!=-1&&cost[u][w]!=-1&&distance[u] + cost[u][w] < distance[w]){
					distance[w] = distance[u] + cost[u][w];
					pred[w] = u;
				}
			}
		}
	}
	return distance[dest];
}
int main() {
	int start=0 ,dest=0;
	char m = NULL;
	read_and_make_graph();
	MKstack(&s);
	for (int i = 0; i < max_vertex; i++) {
		pred[i] = 0;
		found[i] = 0;
	}
	do {
		s.top = -1;
		for (int i = 0; i < max_vertex; i++) {
			pred[i] = 0;
			set_S[i] = 0;
			found[i]=0;
			distance[i] = 0;
		}
		printf("최소경로를 찾을 두 정점을 입력하세요>");
		scanf(" %c %d %d", &m, &start, &dest);
		if (m == 'f') {
			DFS(start, dest);
			for (int i = 0; i < s.top; i++) {
				printf("%d->", s.data[i]);
			}
			printf("%d\n", s.data[s.top]);
		}
		else if (m == 'j') {
			double lowest_cost=Dijikstra(start, dest);
			for (int i = 0; i < s.top;i++) {
				printf("%d->", s.data[i]);
			}
			printf("%d\t총 비용:%.1lf\n\n", dest,lowest_cost);
		}
		else if (m == 'e') {
			break;
		}
	} while (1);
	return 0;
}