#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CODE_LEN 7
typedef int itemstock;
typedef struct item{
	char itemcode[MAX_CODE_LEN];
	itemstock stock;
}item;
typedef struct treenode* treepointer;
typedef struct treenode {
	item key;
	treepointer left;
	treepointer right;
}treenode;
void inorder(treepointer root) {
	if (root) {
		inorder(root->left);
		printf("관리번호: %s, 재고: %d\n", root->key.itemcode, root->key.stock);
		inorder(root->right);
	}
}
void inorder_searching(treepointer root) {
	if (root) {
		inorder_searching(root->left);
		inorder_searching(root->right);
	}
}
treepointer modifiedSearch(treepointer root, item i) {							//있으면 그 노드를 반환, 없으면 넣을 부모 반환
	treepointer parent = NULL;
	while (root) {
		if (strcmp(i.itemcode, root->key.itemcode) == 0){		//itemcode 의 값과 서치값과 같으면 그 노드 반환
			return root;
		}
		parent = root;											//아닐 시 parent=현재, 현재=다음 노드
		if (strcmp(i.itemcode, root->key.itemcode) <0)			//srtcmp가 음수 => 왼<오 즉 itemcode 가 더 앞
			root = root->left;
		else
			root = root->right;									//반대로 itemcode > 현재노드
	}
	return parent;
}
treepointer search_BST(treepointer curr, char* k, treepointer * par) {			//노드를 찾고 찾지못하면 NULL
	*par = NULL;												//불러온 함수의 parent 변수
	while (curr)
		if (strcmp(k , curr->key.itemcode)==0)					//같으면 바로 반환 k: 삭제할 상품코드
			return curr;
		else if (strcmp(k, curr->key.itemcode) == -1) {			//k가 작으면 leftchild 로 이동
			*par = curr;
			curr = curr->left;
		}
		else {
			*par = curr;										//k가 크면 rightchild 로 이동
			curr = curr->right;
		}
	return NULL;												//찾지 못하면 NULL 반환
}
void insert(treepointer* root, item i) {
	treepointer ptr, temp;
	ptr = (treepointer)malloc(sizeof(treenode));
	strcpy(ptr->key.itemcode, i.itemcode);
	ptr->key.stock = i.stock;
	ptr->left = ptr->right = NULL;								// 61~64 :초기화
	if (!(*root))
		*root = ptr;
	else {
		temp = modifiedSearch(*root, i);						//modifiedSearch:같은 값을 찾으면 노드 반환받고 , 없으면 들어갈 부모 반환
		if (strcmp(ptr->key.itemcode,temp->key.itemcode)==0) {
			printf("존재하는 상품코드입니다.\n");				//존재하는 노드 반환받을 시 수행
			temp->key.stock = i.stock + temp->key.stock;		//기존재고 + 추가재고
			printf("상품코드 %s의 재고는 %d개 입니다.\n", i.itemcode, temp->key.stock);
		}
		else {
			if (strcmp(i.itemcode, temp->key.itemcode) <0)		//temp가 itemcode와 다를 경우 실행 (새 노드와 부모노드 비교)
				temp->left = ptr;								//새 노드가 추가될 부모보다 작다
			else
				temp->right = ptr;								//새 노드가 추가될 부모보다 크다
		}
			
	}
}

void delete(treepointer *root,char* k) {
	treepointer parent, nptr,succ,curr;
	int num;
	nptr = search_BST(*root, k, &parent);
	if (!nptr) {																//찾지못하면 NULL
		printf("없는 관리번호입니다.\n");
		return 0;
	}
	printf("[출고] 출고 수량을 입력하세요 : ");									
	scanf("%d", &num);
	if (nptr->key.stock > num) {												//재고 > 출고량 비교
		nptr->key.stock -= num;													
		return 0;
	}
	else {																		//재고 =< 출고량 
		if (nptr->key.stock == num) {											
			printf("재고가 모두 소진되었습니다.\n");							//재고 == 출고량
		}
		else{ 
			printf("재고가 모두 소진되어 %d개만 출고합니다\n", nptr->key.stock); //재고 < 출고량
		}
		if (nptr->left && nptr->right) {										//leftchil rightchild 모두 존재
			succ = nptr->right;
			parent = nptr;
			while (succ->left) {
				parent = succ;
				succ = succ->left;
			}
			strcpy(nptr->key.itemcode, succ->key.itemcode);
			nptr->key.stock = succ->key.stock;
			nptr = succ;
		}
		curr = nptr->left;
		if (!curr)
			curr = nptr->right;
		if (!parent)														//root에서 itemcode를 찾고 그 노드가 한개 이하의 자식을 가짐.
			*root = curr;
		else if (parent->left == nptr)
			parent->left = curr;
		else
			parent->right = curr;
		free(nptr);
	}
}
treepointer search(treepointer root, char* i) {
	treepointer par,succ;
	succ=search_BST(root, i, &par);
	
	return succ;
}
int main() {
	treenode* root = NULL;
	
	char a[7];
	int b = 0;
	item i;
	while (1) {
		char c=NULL;
		
		printf("*====S E L E C T  M E N U====*\n");
		printf("\t1 : 재고확인\n");
		printf("\t2 :   입고\n");
		printf("\t3 :   출고\n");
		printf("\t4 :   검색\n");
		printf("\t5 :   종료\n\n");
		printf("*============================*\n");
		c = getch();
		int d= 1;
		while (d) {
			if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5')
				d = 0;
			else {
				printf("잘못 입력하였습니다. 다시 입력해 주세요.\n");
				c = getch();
			}
		}
		
		switch (c) {
			case '1':
				if (!root) {
					printf("재고소진 상태입니다.\n");
				}
				else {
					inorder(root);
				}
				break;
			case '2':
				printf("[입고] 관리번호를 입력하세요 : ");
				scanf("%s", &a);
				printf("[입고] 입고 수량을 입력하세요 : ");
				scanf("%d", &b);
				strcpy(i.itemcode, a);
				i.stock = b;
				insert(&root, i);
				break;
			case '3':
				printf("[출고] 관리번호를 입력하세요 : ");
				scanf("%s", &a);
				delete(&root, &a);
				break;
			case '4':
				if (!root) {
					printf("재고가 존재하지 않습니다. 제고를 먼저 입고시켜주세요.\n");
					break;
				}
				printf("[재고 수량 검색] 관리번호를 입력하세요 : ");
				scanf("%s", &a);
				if(search(root, &a))
					printf("상품코드 %s 의 재고는 %d개 입니다.\n", search(root, &a)->key.itemcode, search(root, &a)->key.stock);
				else {
					printf("상품을 찾을 수 없습니다.\n");
				}
				break;
			case '5':
				break;
		}
		if (c == '5')
			break;
	}
	return ;
}