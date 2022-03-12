#include<stdio.h>
int  p=5;
int i, j;
int St[3][100];
int Cnt[3] = { 5,0,0 };
void hanoi(int n, int source, int desti, int mid);
void move_disk(int source, int desti);
int main(void) {
	for (i = 0; i < 3; i++)
		for (j = 0; j < 100; j++)
			St[i][j] = 0;
	for (i = 0; i < p; i++)St[0][i] = p - i;
	hanoi(p, 0, 2, 1);
}
void hanoi(int n, int source, int desti, int mid) {
	if (n == 1) {
		move_disk(source, desti);
	}
	else {
		hanoi(n - 1, source, mid, desti);
		move_disk(source, desti);
		hanoi(n - 1, mid, desti, source);
	}
}
void move_disk(int source, int desti) {
	St[desti][Cnt[desti]] = St[source][Cnt[source] - 1];
	printf("Disk %d is moved from pole %d.\n", St[source][Cnt[source] - 1], source, desti);
	St[source][Cnt[source] - 1] = 0;
	Cnt[source]--;
	Cnt[desti]++;
}