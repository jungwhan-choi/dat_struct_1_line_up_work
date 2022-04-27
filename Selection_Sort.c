#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
	int a[10] = { 5,9,16,4,78,34,89,15,90,35 };
	sort(a, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d\n", a[i]);
	}
}