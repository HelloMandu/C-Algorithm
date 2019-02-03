#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#pragma warning(disable :4996)

typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

typedef struct Tree {
	TreeNode *root;
}Tree;

TreeNode *CreateNode(int key) {
	TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void InsertNode(Tree *tree, int key) {
	TreeNode *child = tree->root;
	TreeNode *parent = NULL;
	while (child != NULL) {
		if (key == child->key)
			return;
		parent = child;
		if (key > child->key)
			child = child->left;
		else
			child = child->right;
	}

	TreeNode *newnode = CreateNode(key);

	if (tree->root == NULL)
		tree->root = newnode;
	else if (key > parent->key)
		parent->left = newnode;
	else
		parent->right = newnode;
}
void DeleteNode(Tree *tree, int key) { //root ������ Ž���Ͽ� key ���� ���� ��带 ã�� �����ϴ� ���� 
	TreeNode *parent, *child, *p, *succ, *succ_left, *succ_right, *succ_left_parent, *succ_right_parent, *succ_parent;
	parent = NULL;
	p = tree->root;
	while ((p != NULL) && (p->key != key)) {  //������ ����� ��ġ Ž�� 
		parent = p;
		if (key > p->key)
			p = p->left;
		else
			p = p->right;
	}

	if (p == NULL) return; //������ ��尡 ���� ��� 

	// ������ ��尡 �ܸ������ ��� 
	if ((p->left == NULL) && (p->right == NULL)) {

		if (parent != NULL) {

			if (parent->left == p)
				parent->left = NULL;

			else
				parent->right = NULL;
		}
		else tree->root = NULL;
	}
	// ������ ��尡 �� ���� �ڽĳ�带 ���� ��� 
	else if ((p->left == NULL) || (p->right == NULL)) {

		if (p->left != NULL)
			child = p->left;

		else
			child = p->right;

		if (parent != NULL) {

			if (parent->left == p)
				parent->left = child;

			else
				parent->right = child;
		}
		else tree->root = child;
	}
	// ������ ��尡 �� ���� �ڽĳ�带 ���� ��� 
	else {
		succ_left_parent = p;
		succ_right_parent = p;
		succ_left = p->left;
		succ_right = p->right;

		while (succ_left->right != NULL) { // ����  Ž��
			succ_left_parent = succ_left;
			succ_left = succ_left->right;
		}
		while (succ_right->left != NULL) { // ������ Ž��
			succ_right_parent = succ_right;
			succ_right = succ_right->left;
		}
		if (abs(p->key - succ_left->key) != abs(p->key - succ_right->key)) { // �ٲܰ� ���ϱ�
			if (abs(p->key - succ_left->key) < abs(p->key - succ_right->key)) {
				succ_parent = succ_left_parent;
				succ = succ_left;
			}
			else {
				succ_parent = succ_right_parent;
				succ = succ_right;
			}
		}
		else {
			succ_parent = succ_left_parent;
			succ = succ_left;
		}
		// �İ��� Ž��
		if (succ == succ_left) { //���� �ٽ� Ȯ��
			if (succ_parent->left == succ)
				succ_parent->left = succ->left;

			else
				succ_parent->right = succ->left;
		}
		else {
			if (succ_parent->left == succ)
				succ_parent->left = succ->right;

			else
				succ_parent->right = succ->right;
		}
		p->key = succ->key;
		p = succ;
	}
	free(p);
}
void preorder(TreeNode *root, FILE *oup) {
	TreeNode *p = root;
	if (p != NULL) {
		fprintf(oup, "%d ", p->key);
		preorder(p->left, oup);
		preorder(p->right, oup);
	}
}
int search(TreeNode *root, int key, FILE *oup) {
	TreeNode *p = root;
	if (p != NULL) {
		fprintf(oup, "%d ", p->key);
		if (p->key == key) return 1;
		else if (p->key < key) return search(p->left, key, oup);
		else return search(p->right, key, oup);
	}
	else return 0;
}
int main() {
	FILE *inp = fopen("hw4.inp", "rt");
	FILE *oup = fopen("hw4.out", "wt");

	if (inp == NULL)
		fprintf(stderr, "can't open %s\n", "hw4.inp");

	if (oup == NULL)
		fprintf(stderr, "can't open %s\n", "hw4.out");

	Tree *tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	int num;
	char star = 0;
	while (star != '\n') { // Ʈ�� ����
		fscanf(inp, "%d", &num);
		fscanf(inp, "%c", &star);
		InsertNode(tree, num);
	}
	preorder(tree->root, oup);
	fprintf(oup, "\n");
	star = 0;
	while (star != '\n') { // Ʈ�� ����
		fscanf(inp, "%d", &num);
		fscanf(inp, "%c", &star);
		DeleteNode(tree, num);
	}
	preorder(tree->root, oup);
	fprintf(oup, "\n");
	star = 0;

	fscanf(inp, "%d", &num);
	if (search(tree->root, num, oup))
		fprintf(oup, "\nYes\n");
	else
		fprintf(oup, "\nNo\n");

	fprintf(oup, "*");

	fclose(inp);
	fclose(oup);
	return 0;
}