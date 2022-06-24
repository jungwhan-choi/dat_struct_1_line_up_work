#define _CRT_SECURE_NO_WARNINGS
#define max_vertex 12

#include <stdio.h>
#include <stdlib.h>

typedef struct listnode* listpointer;
typedef struct listnode {
	int num;
	listpointer link;
}listnode;

double cost[max_vertex][max_vertex];
listpointer graph[max_vertex];
int distance, pred, set_S;

void makenode(listpointer* p, int n) {
	listpointer new;
	new = (listpointer)malloc(sizeof(listnode));
	(*p)->link = new;
	new->num = n;
	new->link = NULL;
}

void cost_maker() {
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;
		char v = NULL;
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

void list_maker() {
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0, e = 0;
		char v = NULL;
		double value = 0;
		fscanf(fp, "%d", &vt);
		listpointer temp = graph[vt];
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf", &value);
			e = fscanf(fp, "%c", &v);
			makenode(&temp, next_vt);
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

void read_and_make_graph() {
	cost_maker();
	list_maker();
}


int shortest_path (int start,int dest){
}
int main() {
	read_and_make_graph();
	for (int i = 0; i < max_vertex; i++) {
		listpointer temp;
		temp = graph[i];
		do {
			printf("%d -> ", temp->num);
			temp = temp->link;

		} while (temp->link != NULL);
		printf("\n");
	}
}