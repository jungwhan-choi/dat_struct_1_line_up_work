// 재귀함수 사용
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
void swap(int* x, int* y);
void sort(int list[], int n);
int binsearch(struct student list[], char *search_name, int left, int right);
int compare(char first_name, char second_name);
struct student {//학생 정보담을 구조체 선언
	char name[10];
	double score;
};
int main(void) {
	struct student a[17];
	char search_name[10];
	int p=0;
	FILE* fp = fopen("name_gpa (1).txt", "r");//파일의 학생정보 가져오기
	for (int i = 0; i < 17; i++) {
		fscanf(fp, "%s %lf", a[i].name, &a[i].score);//구조체에 저장
	}
	sort(a, 17);//정렬
	for (int i = 0; i < 17; i++) {//사실여부 확인을 위해 정렬된 학생 정보 출력
		printf("%s %.2lf\n", a[i].name, a[i].score);
	}
	while (1) {
		printf("찾을 이름을 넣으시오(종료:$ 입력):");//종료
		scanf("%s", &search_name);
		if (search_name[0] == '$')
			break;
		p=binsearch(a, search_name, 0, 17);
		if (p == 404) {//찾지 못했을 시에p= 404.
			printf("존재하지 않는 학생 정보입니다.\n");
			continue;//재실행
		}
		printf("%s->%d번,%.2lf\n", search_name, p+1, a[p].score);
	}

	fclose(fp);
}
void sort(struct student a[], int n) {//정렬
	int i, j, min, temp;
	
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			
			if (strcmp(a[j].name, a[min].name) != 1) {
				min = j;
			}
		}
		swap(a[i].name, a[min].name);
		swap(&a[i].score, &a[min].score);
	}
	
}
void swap(double *x, double *y) {//바꾸기
	double temp = *x;
	*x = *y;
	*y = temp;
}
int binsearch(struct student list[], char search_name[], int left, int right) {//이진탐색
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;

		switch (strcmp(list[middle].name, search_name)) {
		case -1:
			return binsearch(list, search_name, middle + 1, right);
			break;
		case 0:
			return middle;
			break;
		case 1:
			return binsearch(list, search_name, left, middle - 1);
			break;
		}
	}
	return 404;//이름을 찾지 못함
}
