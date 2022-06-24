#define _CRT_SECURE_NO_WARNINGS
#define max_vertex 12
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef struct listnode* listpointer;
typedef struct listnode {
	int num;
	listpointer link;
}listnode;

double cost[max_vertex][max_vertex];
listpointer graph[max_vertex];
int distance, pred, set_S;
void read_and_make_graph() {
	cost_maker();
	
}
void cost_maker() {
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0, next_vt = 0;
		fscanf(fp, "%d", &vt);
		printf("\n");
		char v = NULL;
		double value = 0;
		int e = 0;
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf", &value);
			e = fscanf(fp, "%c", &v);
			cost[vt][next_vt] = value;


			printf("(%d,%d):%.1lf\n", vt, next_vt, cost[vt][next_vt]);
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

}
void makenode(listpointer* p,int n) {
	listpointer new;
	new = (listpointer)malloc(sizeof(listnode));
	(*p)->link = new;
	new->num = n;
	new->link = NULL;
}
int shortest_path (int start,int dest){
}
int main() {
	
	for (int i = 0; i < max_vertex; i++) {
		for (int j = 0; j < max_vertex; j++) {
			cost[i][j] = -1;
		}
		
	}
	read_and_make_graph();
	for (int i = 0; i < max_vertex; i++) {
		for (int j = 0; j < max_vertex; j++) {
			printf("%.1lf  ", cost[i][j]);
		}
		printf("\n");

	}
}