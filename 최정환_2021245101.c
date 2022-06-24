#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct str_record {	// 한 데이터아이템, 즉 한 레코드의 타입 선언.
	char name[30]; // 이름.  이것을 키로 한다.
	int stno; // 학번
} ty_record;

typedef struct str_treenode* ty_treenode_ptr;
typedef struct str_treenode {	// 트리 노드의 타입선언.
	ty_record data;
	ty_treenode_ptr left, right;
} ty_treenode;

// key 를 가진 노드를 찾는다. 발견되면 NULL을 반환하고, 
// 아니면, 탐색 중에 마지막으로 도달한 노드의 포인터를 반환.
ty_treenode_ptr   modifiedSearch(ty_treenode_ptr root, char* key)
{
	ty_treenode_ptr nodeptr = root;
	ty_treenode_ptr parent = NULL;
	while (nodeptr) {
		if (strcmp(key, nodeptr->data.name) == 0)
			return  NULL;
		parent = nodeptr;
		if (strcmp(key, nodeptr->data.name) < 0)
			nodeptr = nodeptr->left;
		else
			nodeptr = nodeptr->right;
	}
	return parent;
} // modifiedSearch

void insert(ty_treenode_ptr* node, ty_record item)
{
	ty_treenode_ptr newnode, temp;
	newnode = (ty_treenode_ptr)malloc(sizeof(ty_treenode));
	newnode->data = item;
	newnode->left = newnode->right = NULL;
	if (!(*node))  // 루트가 널이면 즉 노드가 한 개도 없는 경우.
		*node = newnode;
	else {
		temp = modifiedSearch(*node, item.name); // 새 노드를 붙일  노드 탐색
		if (!temp)
			printf("동일 키의 노드 이미 존재로 삽입 실패: 키=%s\n", item.name);
		else {  // temp 가 가리키는 노드에 자식으로 새 노드를 붙인다.
			if (strcmp(item.name, temp->data.name) < 0)
				temp->left = newnode;
			else
				temp->right = newnode;
		}
	}
} // insert

ty_treenode_ptr get_maxnode1(ty_treenode_ptr root) {
	ty_treenode_ptr temp;
	if (!root) {
		printf("트리가 비었습니다.\n");
		return NULL;
	}
	while (1) {
		if (root->right == NULL) {
			break;
		}
		root = root->right;
	}
	return root;
}
/* 함수 get_maxnode */



int main()
{
	char sname[30];
	int stnumber, readnum;
	ty_treenode_ptr ROOT = NULL;  // 이진탐색트리의 루트노드를 가리키는 헤더변수.
	ty_treenode_ptr max_nodeptr;
	ty_record newrecord;

	FILE* fp;
	fp = fopen("data.txt", "r");		// 파일을 연다.
	if (!fp) {
		printf("파일 열기 에러: data.txt.\n");
		return 0;
	}

	// 데이터 파일에서 모든 레코드들을 읽어서 BST 에 넣는다. 
	// 헤더변수 ROOT 가 루트노드를 가리키게 한다.
	while (1) {
		readnum = fscanf(fp, "%s%d", sname, &stnumber);
		if (readnum != 2) {
			break; // 화일 끝에 도달.
		}
		strcpy(newrecord.name, sname);  newrecord.stno = stnumber;
		insert(&ROOT, newrecord);
	}


	/* 함수 get_maxnode 는 ROOT 가 가리키는 이진탐색트리에서 최대키 (맨 마지막 키)를 가진
	   노드를 찾아 이에 대한 포인터를 반환한다.
	   함수가 반환한 결과는 변수 max_node_ptr 로 받는다.
	*/

	max_nodeptr = get_maxnode1(ROOT);

	/* 최대 키를 가진 노드의 내용을 출력한다.  */
	if (!max_nodeptr) {
		printf("노드가 비었습니다.");
	}
	else {
		printf("최대 키 노드 내용:이름= %s, 학번=%d\n", max_nodeptr->data.name, max_nodeptr->data.stno);
	}
	


	fclose(fp);
	printf("프로그램이 종료됩니다.\n");
	return 1;
} // main
