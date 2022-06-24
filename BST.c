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
		printf("������ȣ: %s, ���: %d\n", root->key.itemcode, root->key.stock);
		inorder(root->right);
	}
}
void inorder_searching(treepointer root) {
	if (root) {
		inorder_searching(root->left);
		inorder_searching(root->right);
	}
}
treepointer modifiedSearch(treepointer root, item i) {							//������ �� ��带 ��ȯ, ������ ���� �θ� ��ȯ
	treepointer parent = NULL;
	while (root) {
		if (strcmp(i.itemcode, root->key.itemcode) == 0){		//itemcode �� ���� ��ġ���� ������ �� ��� ��ȯ
			return root;
		}
		parent = root;											//�ƴ� �� parent=����, ����=���� ���
		if (strcmp(i.itemcode, root->key.itemcode) <0)			//srtcmp�� ���� => ��<�� �� itemcode �� �� ��
			root = root->left;
		else
			root = root->right;									//�ݴ�� itemcode > ������
	}
	return parent;
}
treepointer search_BST(treepointer curr, char* k, treepointer * par) {			//��带 ã�� ã�����ϸ� NULL
	*par = NULL;												//�ҷ��� �Լ��� parent ����
	while (curr)
		if (strcmp(k , curr->key.itemcode)==0)					//������ �ٷ� ��ȯ k: ������ ��ǰ�ڵ�
			return curr;
		else if (strcmp(k, curr->key.itemcode) == -1) {			//k�� ������ leftchild �� �̵�
			*par = curr;
			curr = curr->left;
		}
		else {
			*par = curr;										//k�� ũ�� rightchild �� �̵�
			curr = curr->right;
		}
	return NULL;												//ã�� ���ϸ� NULL ��ȯ
}
void insert(treepointer* root, item i) {
	treepointer ptr, temp;
	ptr = (treepointer)malloc(sizeof(treenode));
	strcpy(ptr->key.itemcode, i.itemcode);
	ptr->key.stock = i.stock;
	ptr->left = ptr->right = NULL;								// 61~64 :�ʱ�ȭ
	if (!(*root))
		*root = ptr;
	else {
		temp = modifiedSearch(*root, i);						//modifiedSearch:���� ���� ã���� ��� ��ȯ�ް� , ������ �� �θ� ��ȯ
		if (strcmp(ptr->key.itemcode,temp->key.itemcode)==0) {
			printf("�����ϴ� ��ǰ�ڵ��Դϴ�.\n");				//�����ϴ� ��� ��ȯ���� �� ����
			temp->key.stock = i.stock + temp->key.stock;		//������� + �߰����
			printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.\n", i.itemcode, temp->key.stock);
		}
		else {
			if (strcmp(i.itemcode, temp->key.itemcode) <0)		//temp�� itemcode�� �ٸ� ��� ���� (�� ���� �θ��� ��)
				temp->left = ptr;								//�� ��尡 �߰��� �θ𺸴� �۴�
			else
				temp->right = ptr;								//�� ��尡 �߰��� �θ𺸴� ũ��
		}
			
	}
}

void delete(treepointer *root,char* k) {
	treepointer parent, nptr,succ,curr;
	int num;
	nptr = search_BST(*root, k, &parent);
	if (!nptr) {																//ã�����ϸ� NULL
		printf("���� ������ȣ�Դϴ�.\n");
		return 0;
	}
	printf("[���] ��� ������ �Է��ϼ��� : ");									
	scanf("%d", &num);
	if (nptr->key.stock > num) {												//��� > ��� ��
		nptr->key.stock -= num;													
		return 0;
	}
	else {																		//��� =< ��� 
		if (nptr->key.stock == num) {											
			printf("��� ��� �����Ǿ����ϴ�.\n");							//��� == ���
		}
		else{ 
			printf("��� ��� �����Ǿ� %d���� ����մϴ�\n", nptr->key.stock); //��� < ���
		}
		if (nptr->left && nptr->right) {										//leftchil rightchild ��� ����
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
		if (!parent)														//root���� itemcode�� ã�� �� ��尡 �Ѱ� ������ �ڽ��� ����.
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
		printf("\t1 : ���Ȯ��\n");
		printf("\t2 :   �԰�\n");
		printf("\t3 :   ���\n");
		printf("\t4 :   �˻�\n");
		printf("\t5 :   ����\n\n");
		printf("*============================*\n");
		c = getch();
		int d= 1;
		while (d) {
			if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5')
				d = 0;
			else {
				printf("�߸� �Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ���.\n");
				c = getch();
			}
		}
		
		switch (c) {
			case '1':
				if (!root) {
					printf("������ �����Դϴ�.\n");
				}
				else {
					inorder(root);
				}
				break;
			case '2':
				printf("[�԰�] ������ȣ�� �Է��ϼ��� : ");
				scanf("%s", &a);
				printf("[�԰�] �԰� ������ �Է��ϼ��� : ");
				scanf("%d", &b);
				strcpy(i.itemcode, a);
				i.stock = b;
				insert(&root, i);
				break;
			case '3':
				printf("[���] ������ȣ�� �Է��ϼ��� : ");
				scanf("%s", &a);
				delete(&root, &a);
				break;
			case '4':
				if (!root) {
					printf("��� �������� �ʽ��ϴ�. ���� ���� �԰�����ּ���.\n");
					break;
				}
				printf("[��� ���� �˻�] ������ȣ�� �Է��ϼ��� : ");
				scanf("%s", &a);
				if(search(root, &a))
					printf("��ǰ�ڵ� %s �� ���� %d�� �Դϴ�.\n", search(root, &a)->key.itemcode, search(root, &a)->key.stock);
				else {
					printf("��ǰ�� ã�� �� �����ϴ�.\n");
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