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

int stack_search(int v) {								//���ÿ� ���� ���� �� ��ġ�� ���� ������ Ȯ��
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

int get_unvisited_neighbor(int v) {						//����� �̿� �� ���� �湮�� �������� ���� ����� ����ȣ ��ȯ
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

void DFS(int start,int dest) {							//DFS��μ�Ī
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
double Dijikstra (int start,int dest){						//���ͽ�Ʈ�� ��μ�Ī
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
		printf("�ּҰ�θ� ã�� �� ������ �Է��ϼ���>");
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
			printf("%d\t�� ���:%.1lf\n\n", dest,lowest_cost);
		}
		else if (m == 'e') {
			break;
		}
	} while (1);
	return 0;
}