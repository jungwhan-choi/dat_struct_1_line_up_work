#include<stdio.h>
#define p 5																
int i, j;
int St[3][100];													//1��,2��,3�� �� ����
int Cnt[3] = { p,0,0 };											//1��,2��,3�� ���� ���� ���� ��ũ ��
void hanoi(int n, int source, int desti, int mid);				//��Ϳ� �ϳ��� �۾�
void move_disk(int source, int desti);							//��ũ�� source������ desti���� �ű�� �۾�
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
		hanoi(n - 1, source, mid, desti);						//desti->mid, mid->desti
		move_disk(source, desti);								//disk move
		hanoi(n - 1, mid, desti, source);						//source->desti, desti->mid, mid-> source
	}
}
void move_disk(int source, int desti) {
	St[desti][Cnt[desti]] = St[source][Cnt[source] - 1];
	printf("Disk %d is moved from pole %d.\n", St[source][Cnt[source] - 1], source, desti);
	St[source][Cnt[source] - 1] = 0;
	Cnt[source]--;
	Cnt[desti]++;
}