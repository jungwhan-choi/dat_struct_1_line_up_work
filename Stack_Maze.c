#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define m  12
#define p  12
#define Max_dir 8
#define Timestep 1000
typedef struct Aoff {
	short int vert;
	short int horiz;
} offsets;
typedef struct St_element {
	short int row;
	short int col;
	short int dir;
} ty_element;
typedef struct listnode* listpointer;
typedef struct listnode {
	ty_element data;
	listpointer link;
}listnode;
offsets move[Max_dir] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
int maze[m + 2][p + 2];
int mark[m + 2][p + 2];
void makenode(listpointer* top, ty_element item) {
	listpointer new_node = (listpointer)malloc(sizeof(listnode));
	new_node->data = item;
	if (*top == NULL) {
		new_node->link = NULL;
	}
	else {
		new_node->link = *top;
	}

	*top = new_node;
	mark[item.row][item.col] = 1;
	mark[item.row][item.col];
}
void backtracking(listpointer* top) {

	*top = (*top)->link;
}
int path(int sy, int sx, int dy, int dx) {
	listpointer top = NULL;
	int i, j, row, col, nextRow, nextCol, dir;		//i,j=반복문 재료, row,col=,nextRow,nextCol=다음으로 향할곳 +or-,dir=방향저장
	int found, backtrack = 0, len = 0;				//found=찾았을시에 1반환,backtrack=백트래킹 횟수,len=노드 길이
	int Exit_Row = dy, Exit_Col = dx;
	ty_element position, next_position;
	if (maze[sy][sx] == 1 || maze[dy][dx] == 1) {
		printf("입력오류:출발점이나 목표점이 막힌 셀입니다.\n");
		return 0;
	}
	position.row = sy;
	position.col = sx;
	position.dir = 0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			mark[i + 1][j + 1] = 0;
		}
	}
	makenode(&top, position);		//top에 시작위치 기입,시작점 mark=1	
	len++;
	while (1) {		//찾기 시작
		int success = 0;
		switch (top->data.dir) {
		case 0:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 1:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 2:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 3:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 4:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 5:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 6:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 7:
			nextRow = move[top->data.dir].vert;
			nextCol = move[top->data.dir].horiz;
			if (maze[top->data.row + nextRow][top->data.col + nextCol] == 1 || mark[top->data.row + nextRow][top->data.col + nextCol] == 1) {
				top->data.dir++;
				continue;
			}
			else
				break;
		case 8:
			backtracking(&top);
			backtrack++;
			len--;
			success = 1;
			break;
		}
		if (success == 0) {
			top->data.dir++;
			next_position.row = top->data.row + nextRow;
			next_position.col = top->data.col + nextCol;
			next_position.dir = 0;
			makenode(&top, next_position);
			len++;
		}
		else {
			continue;
		}

		if (top->data.row == Exit_Row && top->data.col == Exit_Col) {
			listpointer temp2 = NULL;
			listpointer temp3;
			for (int i = 0; i < len; i++) {
				listpointer temp1 = top;
				temp3 = temp2;
				while (1) {
					temp2 = temp1;
					if (temp1->link != temp3)
						temp1 = temp1->link;
					else
						break;
				}
				printf("[%d,%d]\t", temp2->data.row, temp2->data.col);
				if ((i + 1) % 6 == 0)
					printf("\n");
			}


			printf("finished\n길이=%d, 백트래킹 수=%d\n", len, backtrack);
			found = 0;
			return found;

		}
	}
}
int main(void) {
	int done;
	while (1) {
		FILE* fp = fopen("map.txt", "r");
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 28; j++) {
				if (j % 2 == 0) {
					fscanf(fp, "%d", &maze[i][j / 2]);

				}
			}
		}
		int starty, startx, endy, endx;
		while (1) {
			printf("출발점, 목표점은?(4개의 정수; 종료는 Control+D Enter): ");
			int res = scanf("%d%d%d%d", &starty, &startx, &endy, &endx);
			if (res != 4) return 0;

			done = path(starty, startx, endy, endx);

		}
	}
}