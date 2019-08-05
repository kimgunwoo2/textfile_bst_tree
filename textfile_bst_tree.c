#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct {
	char name[100];
	char number[100];
}element;
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
}TreeNode;
int compare(element e1, element e2) {
	int n;
	n = strcmp(e1.name, e2.name);
	if (n == 0)
		n = strcmp(e1.number, e2.number);
	return n;
}

void display(TreeNode *p) {
	if (p != NULL) {
		
		display(p->left);
		printf("이름 : %s , 전화번호 : %s\n", p->key.name, p->key.number);
		display(p->right);
		
	}
}
TreeNode *search(TreeNode *root, element key) {
	TreeNode *p = root;
	while (p != NULL) {
		switch (compare(key, p->key)) {
		case -1:
			p = p->left;
			break;
		case 0:
			return p;
		case 1:
			p = p->right;
			break;
		}
	}
	return p;
}
void insert_node(TreeNode **root, element key) {
	TreeNode *p, *t;
	TreeNode *n;

	t = *root;
	p = NULL;
	while (t != NULL) {
		if (compare(key, t->key) == 0) return;
		p = t;
		if (compare(key, t->key) < 0) t = t->left;
		else t = t->right;
	}
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL)return;
	n->key = key;
	n->left = n->right = NULL;
	if (p != NULL)
		if (compare(key, p->key) < 0)
			p->left = n;
		else p->right = n;
	else *root = n;
}
void delete_node(TreeNode **root, element key) {

	TreeNode *p, *child, *succ, *succ_p, *t;
	p = NULL;
	t = *root;
	while (t != NULL&&compare(t->key, key) != 0) {
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;
	}
	if (t == NULL) {
		printf("key is not in the tree");
		return;
	}
	if ((t->left == NULL) && (t->right) == NULL) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else *root = NULL;
	}
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else p->right = child;
		}
		else *root = child;
	}
	else {
		succ_p = t;
		succ = t->right;
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		t->key = succ->key;
		t = succ;
	}
	free(t);
}
void Help() {
	printf("\n");
	printf("*************************\n");
	printf("*****BST 전화번호부******\n");
	printf("*************************\n");
	printf("i: 입력 \n");
	printf("d: 삭제\n");
	printf("s: 탐색\n");
	printf("p: 출력\n");
	printf("f: 저장\n");
	printf("q: 종료\n");
	printf("*************************\n");

}
void readfile(TreeNode **root,FILE* fp) {
	element person;
	
	if (fp == NULL) {
		printf("실패");
	}
	else {
		while (feof(fp) == 0) {
			fscanf(fp, "%s\t%s\n", person.name,person.number);
			printf("이름 : %s, 전화번호 : %s\n", person.name, person.number);
			insert_node(root, person);
		}
	}
	
	return;
}
void savefile(TreeNode *root,FILE *fp) {
	element person;
	if (fp == NULL) {
		printf("실패");
	}
	else {
		if (root != NULL) {
			savefile(root->left,fp);
			fprintf(fp,"%s\t%s\n", root->key.name, root->key.number);
			savefile(root->right,fp);
		}
	}
	
	return;
}
void main()
{
	
	TreeNode *temp;
	TreeNode *root = NULL;
	element e; int c;
	FILE *fp;
	char mode='a';
	fp = fopen("a.txt", "rt");
	readfile(&root,fp);
	fclose(fp);
	while(mode!='q') {
		Help();
		printf("어떤 것을 하시겠습니까? >> ");
		scanf_s("%c", &mode);
		getchar();
		switch (mode) {
		case 'i':
			printf("이름 : ");
			gets_s(e.name,sizeof(e.name));
			printf("전화번호 : ");
			gets_s(e.number,sizeof(e.number));
			insert_node(&root, e);
			break;
		case 'd':
			printf("이름 : ");
			gets_s(e.name, sizeof(e.name));
			delete_node(&root, e);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("찾고자 하는 이름을 적으세요 : ");
			gets_s(e.name, sizeof(e.name));
			temp = search(root, e);
			if (temp != NULL)
				printf("전화번호 : %s\n", temp->key.number);
			break;
		case 'f':	
			fp = fopen("a.txt", "w");
			printf("파일에 저장하였습니다. ");
			savefile(root,fp);
			fclose(fp);
		}


	}

}