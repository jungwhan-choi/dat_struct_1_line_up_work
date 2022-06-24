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

double cost[max_vertex][max_vertex] = { -1, };
listpointer graph[max_vertex];
int distance, pred, set_S;
void read_and_make_graph() {
	
	FILE* fp = fopen("graphdata.txt", "r");
	for (int i = 0; i < max_vertex; i++) {
		int vt = 0,  next_vt = 0;
		fscanf(fp, "%d", &vt);
		printf("\n");
		char v=NULL;
		double value=0;
		do {
			fscanf(fp, "%d", &next_vt);
			fscanf(fp, "%lf%c", &value,&v);
			cost[vt][next_vt] = value;
			if (v == '\n' || v==EOF) {
				break;
			}
			printf("(%d,%d):%.1lf\n", fvt, next_vt, value);
			
		} while (1);
		
	}
}
int shortest_path (int start,int dest){
}
int main() {
	read_and_make_graph();
	
}