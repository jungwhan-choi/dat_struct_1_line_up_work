#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
void swap(int* list_i, int* list_min) {
	int temp;
	temp = *list_i;
	*list_i = *list_min;
	*list_min = temp;
}
void sort(int list[], int n) {
	int i, j, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (list[min] > list[j])
				min = j;
		}
		swap(&list[i], &list[min]);
	}
}
int main(void) {
	int a[10];
	srand(time(NULL));					//random seed
	for (int i = 0; i < 10; i++) {
		
		a[i] = rand() % 1000;
	}
	sort(a, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d\n", a[i]);
	}
	char a1[10]="¾È³ç", b1[10]="°¨±â";
	printf("%d", strcmp(a1, b1));
}