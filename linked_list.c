#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//학생정보와 학번 저장용 공간
typedef struct listdata {
    char name[30];
    int id;
}listdata;

//노드 생성
typedef struct listnode* listpointer;
typedef struct listnode {
    listdata data;   //listdata 구조체 활용해 char 과 int 따로 저장
    listpointer link;   //다음 노드를 가리킬 포인터
}listnode;

//헤드 생성
typedef struct linkedlist {
    listpointer head;   //처음으로 올 노드를 가리킴(처음은 NULL 값)
    int length;
}linkedlist;

void insertlast(linkedlist* first, listdata item);
listpointer make_node(listdata item, listpointer link);
void printlist(linkedlist* first);
listpointer search(linkedlist* first, int x);
int insert(linkedlist* first, listpointer pre, listdata item);
int delete(linkedlist* first, int x);
void cut_string(char* line, int* i, char* seg);
int digits_only(char* str);
void reverse(linkedlist* first);

int main() {
    
    linkedlist first; //헤드 생성
  
    first.head = NULL;
    first.length = 0;

    listdata item;   //학생정보 저장공간
    listpointer nptr;   //찾을 학생정보가 담긴 노드

    char  line[100], command[10], num1[11], num2[11], iname[15];    //각각, 명령어 줄, 명령어, 찾을 학생학번, 넣을 핵생 학번, 넣을 삭생 이름
    char* ch_ptr;
    int nread, i, std_num1, std_num2, check;
    
    FILE* fp = fopen("students.txt", "r");
    
    while (1) {
        check = fscanf(fp, "%s %d", item.name, &item.id);
        if (check != 2)
            break;   //파일의 학생 정보를 읽어와 item에 일단 저장
        insertlast(&first, item);   //item의 정보를 first 노드열의 마지막 노드 뒤에 붙이기
    }
    printlist(&first);
    while (1) {
        printf("\n명령문(print, search, insert, delete, reverse, getlength, exit.)>>");
        ch_ptr = gets(line);
        if (!ch_ptr)
            break;
        i = 0;
        cut_string(line, &i, command);
        if (strcmp(command, "print") == 0) {
            printlist(&first);
        }
        else if (strcmp(command, "search") == 0) {
            cut_string(line, &i, num1);
            if (!digits_only(num1)) {
                printf("잘못된 명령어(학번 오류)\n");
                continue;
            }
            std_num1 = atoi(num1);
            nptr = search(&first, std_num1);
            if (nptr) {
                printf("찾기성공, 이름:%s, 학번:%d\n", nptr->data.name, nptr->data.id);
            }
            else {
                printf("검색에 실패하였습니다\n");
            }
        }
        else if (strcmp(command, "insert") == 0) {
            cut_string(line, &i, num1);
            if (!digits_only(num1)) {
                printf("잘못된 명령어(첫번째 학번 오류)\n");
                continue;
            }
            std_num1 = atoi(num1);
            nptr = search(&first, std_num1);
            cut_string(line, &i, num2);
            if (!digits_only(num2)) {
                printf("잘못된 명령어(두번째 학번 오류)\n");
                continue;
            }
            std_num2 = atoi(num2);
            cut_string(line, &i, iname);
            if (strlen(iname) == 0) {
                printf("잘못된 명령어(학생 이름이 없습니다)\n");
                continue;
            }
            strcpy(item.name, iname);                                     
            item.id = std_num2;
            insert(&first, nptr, item);
            printlist(&first);
        }
        else if (strcmp(command, "delete") == 0) {
            cut_string(line, &i, num1);
            if (!digits_only(num1)) {
                printf("잘못된 명령어(학번 오류)\n");
                continue;
            }
            std_num1 = atoi(num1);
            check = delete(&first, std_num1);
            if (check) {
                printlist(&first);
            }
        }
        else if (strcmp(command, "reverse")==0) {
            reverse(&first);
            printlist(&first);
        }
        else if(strcmp(command,"getlength")==0){
            printf("길이:%d\n", first.length);
        }
        else if(strcmp(command,"exit")==0){
            break;
        }
        else { printf("알 수 없는 명령어 입니다.\n");
        }
    }

    fclose(fp);
}


void insertlast(linkedlist* first, listdata item) {  
    listpointer temp;   //temp라는 임시 헤드 포인터 생성(추가할 노드)
    listpointer last;   //헤드가 NULL이 아닐 때 
    temp = (listpointer)malloc(sizeof(listnode));   //temp에 노드 공간 추가
    temp->link = NULL;
    
    temp->data = item;  
    if (!first->head) {    //헤드가 NULL이면 바로뒤에 생성  
        (*first).head = temp;     //헤드가 새 노드를 가리킴
        (*first).length = 1;
    }
    else {      //헤드가 NULL이 아니면 link 가 NULL 인 노드를 탐색
        last = (*first).head;
        while ( last->link) {   //다음 노드가 NULL이 아니면 
            last = last->link;
        }
        last->link = temp;     //NULL인 노드 뒤에 노드 생성
        (*first).length++;
    }
}
void printlist(linkedlist *first) {
    listpointer curr;   //순차적으로 삽입할 노드
    curr = (*first).head;   //헤드 삽입
    while (curr) {
        printf("이름:%s , 학번:%d\n", curr->data.name, curr->data.id);
        curr = curr->link;  //링크로 다음 노드 삽입
        
    }
}
listpointer search(linkedlist* first, int x) {
    listpointer curr;
    curr = (*first).head;
    while (curr) {
        if (curr->data.id == x)
            return curr;
        else {
            curr = curr->link;
        }
    }
    return NULL;
}
int insert(linkedlist* first, listpointer pre, listdata item) {
    listpointer temp = make_node(item, NULL);
    if ((*first).head) {
        if (pre) {      //pre가 NULL이 아닐 시
            temp->link = pre->link;
            pre->link = temp;
        }
        else if (!(*first).head) {      //pre가 널일 시, 즉 맨 첫 노드일 경우
            temp->link = (*first).head;
            (*first).head = temp;
        }
    }
    else {
        (*first).head=temp;
        temp->link = NULL;
    }
    (*first).length++;
    return 1;
}
int delete(linkedlist* first, int x) {
    listpointer temp=(*first).head;
    listpointer curr;
    listpointer prev;
    
    curr = search(first, x);
    if (!curr) {
        printf("존재하지 않는 학번입니다");
    }
    if (temp->data.id == x) {
        prev = curr->link;
        
        (*first).head = prev;
        return 1;
    }
    while (temp) {
        if (temp->link == curr) {
            prev = temp;
            prev->link = curr->link;
            return 1;
        }
        else {
            temp = temp->link;
        }
    }
    return 0;
    
}
void reverse(linkedlist* first) {
    listpointer curr;
    listpointer temp;
    listpointer next;
    curr = (*first).head;
    if (!curr || curr->link == NULL)
        return;
    temp = curr;
    curr = curr->link;
    temp->link = NULL;
    while (curr) {
        next = curr->link;
        curr->link = (*first).head;
        (*first).head = curr;
        curr = next;
    }

}
void cut_string(char* line, int* i, char* seg) {
    int j = 0;
    while (line[*i] == ' ' || line[*i] == ',') {
        (*i)++;
    }
    while (line[*i] != ' ' && line[*i] != ',' && line[*i] != '\0') {
        seg[j] = line[*i];
        (*i)++;
        j++;
    } 
    seg[j] = '\0';
}
int digits_only(char* str) {
    int k;
    if (str[0] == '\0')
        return 0;
    for (k = 0; str[k] != '\0'; k++)
        if (!isdigit(str[k]))//숫자가 아닌게 나오면 0 반환
            return 0;
    return 1;
}
listpointer make_node(listdata item, listpointer link) {       //노드생성
    listpointer new_node = (listpointer)malloc(sizeof(listnode));
    new_node->data = item;
    new_node->link = link;
    return new_node;
}