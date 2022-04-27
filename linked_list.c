#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//�л������� �й� ����� ����
typedef struct listdata {
    char name[30];
    int id;
}listdata;

//��� ����
typedef struct listnode* listpointer;
typedef struct listnode {
    listdata data;   //listdata ����ü Ȱ���� char �� int ���� ����
    listpointer link;   //���� ��带 ����ų ������
}listnode;

//��� ����
typedef struct linkedlist {
    listpointer head;   //ó������ �� ��带 ����Ŵ(ó���� NULL ��)
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
    
    linkedlist first; //��� ����
  
    first.head = NULL;
    first.length = 0;

    listdata item;   //�л����� �������
    listpointer nptr;   //ã�� �л������� ��� ���

    char  line[100], command[10], num1[11], num2[11], iname[15];    //����, ��ɾ� ��, ��ɾ�, ã�� �л��й�, ���� �ٻ� �й�, ���� ��� �̸�
    char* ch_ptr;
    int nread, i, std_num1, std_num2, check;
    
    FILE* fp = fopen("students.txt", "r");
    
    while (1) {
        check = fscanf(fp, "%s %d", item.name, &item.id);
        if (check != 2)
            break;   //������ �л� ������ �о�� item�� �ϴ� ����
        insertlast(&first, item);   //item�� ������ first ��忭�� ������ ��� �ڿ� ���̱�
    }
    printlist(&first);
    while (1) {
        printf("\n��ɹ�(print, search, insert, delete, reverse, getlength, exit.)>>");
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
                printf("�߸��� ��ɾ�(�й� ����)\n");
                continue;
            }
            std_num1 = atoi(num1);
            nptr = search(&first, std_num1);
            if (nptr) {
                printf("ã�⼺��, �̸�:%s, �й�:%d\n", nptr->data.name, nptr->data.id);
            }
            else {
                printf("�˻��� �����Ͽ����ϴ�\n");
            }
        }
        else if (strcmp(command, "insert") == 0) {
            cut_string(line, &i, num1);
            if (!digits_only(num1)) {
                printf("�߸��� ��ɾ�(ù��° �й� ����)\n");
                continue;
            }
            std_num1 = atoi(num1);
            nptr = search(&first, std_num1);
            cut_string(line, &i, num2);
            if (!digits_only(num2)) {
                printf("�߸��� ��ɾ�(�ι�° �й� ����)\n");
                continue;
            }
            std_num2 = atoi(num2);
            cut_string(line, &i, iname);
            if (strlen(iname) == 0) {
                printf("�߸��� ��ɾ�(�л� �̸��� �����ϴ�)\n");
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
                printf("�߸��� ��ɾ�(�й� ����)\n");
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
            printf("����:%d\n", first.length);
        }
        else if(strcmp(command,"exit")==0){
            break;
        }
        else { printf("�� �� ���� ��ɾ� �Դϴ�.\n");
        }
    }

    fclose(fp);
}


void insertlast(linkedlist* first, listdata item) {  
    listpointer temp;   //temp��� �ӽ� ��� ������ ����(�߰��� ���)
    listpointer last;   //��尡 NULL�� �ƴ� �� 
    temp = (listpointer)malloc(sizeof(listnode));   //temp�� ��� ���� �߰�
    temp->link = NULL;
    
    temp->data = item;  
    if (!first->head) {    //��尡 NULL�̸� �ٷεڿ� ����  
        (*first).head = temp;     //��尡 �� ��带 ����Ŵ
        (*first).length = 1;
    }
    else {      //��尡 NULL�� �ƴϸ� link �� NULL �� ��带 Ž��
        last = (*first).head;
        while ( last->link) {   //���� ��尡 NULL�� �ƴϸ� 
            last = last->link;
        }
        last->link = temp;     //NULL�� ��� �ڿ� ��� ����
        (*first).length++;
    }
}
void printlist(linkedlist *first) {
    listpointer curr;   //���������� ������ ���
    curr = (*first).head;   //��� ����
    while (curr) {
        printf("�̸�:%s , �й�:%d\n", curr->data.name, curr->data.id);
        curr = curr->link;  //��ũ�� ���� ��� ����
        
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
        if (pre) {      //pre�� NULL�� �ƴ� ��
            temp->link = pre->link;
            pre->link = temp;
        }
        else if (!(*first).head) {      //pre�� ���� ��, �� �� ù ����� ���
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
        printf("�������� �ʴ� �й��Դϴ�");
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
        if (!isdigit(str[k]))//���ڰ� �ƴѰ� ������ 0 ��ȯ
            return 0;
    return 1;
}
listpointer make_node(listdata item, listpointer link) {       //������
    listpointer new_node = (listpointer)malloc(sizeof(listnode));
    new_node->data = item;
    new_node->link = link;
    return new_node;
}