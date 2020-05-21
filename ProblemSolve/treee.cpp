#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#pragma warning(disable :4996)


/*Ʈ���� ��带 ����*/
typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;


/*Ʈ�� root��带 ����*/
typedef struct Tree {
	TreeNode *root;
	int arr[100001];
	int size;
}Tree;

/*���ο� Ʈ���� ����*/
Tree *makeTree() {
	Tree *newTree = (Tree*)malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->size = 0;
	memset(newTree->arr, -1, sizeof(newTree->arr));
	return newTree;
}

/*���ο� TreeNode�� �����Ҵ�*/
TreeNode *CreateNode(int key) {
	TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

/*����Ʈ���� ��带 ����*/
void InsertNode(Tree *tree, int key) {
	int root = 1;
	TreeNode *child = tree->root;
	TreeNode *parent = NULL;
	while (child != NULL) {
		if (key == child->key) {
			return;
		}
		parent = child;
		if (key < child->key) {
			child = child->left;
			root = root * 2;
		}
		else {
			child = child->right;
			root = root * 2 + 1;
		}
	}
	TreeNode *newnode = CreateNode(key);
	tree->arr[root] = key;
	tree->size++;
	if (tree->root == NULL) {
		tree->root = newnode;
	}
	else if (key < parent->key) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}
}


/*����Ʈ���� ��带 ����, ������ ��尡 ���� ��� �������� ����*/
void DeleteNode(Tree *tree, int key) {
	TreeNode *parent = NULL, *child, *p, *succ, *succ_parent;
	p = tree->root;
	int root = 1;
	while ((p != NULL) && (p->key != key)) {  //������ ����� ��ġ Ž�� 
		parent = p;
		if (key < p->key) {
			p = p->left;
			root = root * 2;
		}
		else {
			p = p->right;
			root = root * 2 + 1;
		}
	}

	/*������ ��尡 ���� ��� */
	if (p == NULL) return;

	/*������ ��尡 �ܸ������ ���*/
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {
			tree->root = NULL;
		}
	}
	/*������ ��尡 �� ���� �ڽĳ�带 ���� ���*/
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) {
			child = p->left;
		}
		else {
			child = p->right;
		}
		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
		else {
			tree->root = child;
		}
	}
	/*������ ��尡 �� ���� �ڽĳ�带 ���� ���*/
	else {
		succ_parent = p; succ = p->right;
		while (succ->left != NULL) {
			succ_parent = succ;
			succ = succ->left;
		}
		if (succ_parent->left == succ) {
			succ_parent->left = succ->right;
		}
		else {
			succ_parent->right = succ->right;
		}
		p->key = succ->key;
		p = succ;
	}
	free(p);
	tree->arr[root] = -1;
	tree->size--;
}

/*Ʈ���� ���̸� ����Ͽ� ��ȯ*/
int GetHeight(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	int leftH = GetHeight(root->left); // ���� ���� Ʈ�� ���� ���
	int rightH = GetHeight(root->right); // ������ ���� Ʈ�� ���� ���
	return leftH > rightH ? leftH + 1 : rightH + 1; // ū ���� ���̸� ��ȯ
}

/*�� ���� Ʈ���� ������ ���� ��ȯ*/
int Getbalance(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	return GetHeight(root->left) - GetHeight(root->right); // leftHeight - rightHeight
}

/*Ʈ���� ���������ִ� �������� Ȯ��*/
int isBalanced(TreeNode *root) {
	if (root == NULL) {
		return 1;
	}
	int BF = Getbalance(root); // �����μ��� ���
	if (BF > 1) { // �����μ��� 1���� ū ���
		return 0;
	}
	else if (BF < -1) { // �����μ��� 1���� ���� ���
		return 0;
	}
	return isBalanced(root->left) && isBalanced(root->right);
}

/*��������Ʈ������ Ȯ��*/
int is_complete_binary_tree(Tree *tree) {
	/*Ʈ���� ��尡 �������� �Ǿ����� ���� ��� ��������Ʈ���� �� �� ����*/
	for (int i = 1; i <= tree->size; i++) {
		if (tree->arr[i] == -1) {
			return 0;
		}
	}
	return 1;
}

/*������ Ű���� ���� ����� ���̸� ��ȯ*/
int level(TreeNode *root, int key, int height) {
	/*������ Ű���� ���� ��尡 ���� ��� 0�� ��ȯ*/
	if (root == NULL) {
		return 0;
	}
	/*������ Ű���� ã�� ��� ���̸� ��ȯ*/
	else if (root->key == key) {
		return height;
	}
	/*�����ڽ� ��带 ���� Ű���� Ž��*/
	else if (root->key > key) {
		return level(root->left, key, height + 1);
	}
	/*�������ڽ� ��带 ���� Ű���� Ž��*/
	else {
		return level(root->right, key, height + 1);
	}
}

/*��Ʈ�������� ��� �ڽĳ������� ����� ������ ���� ��ȯ*/
int path_length(TreeNode *root, int height) {
	/*��尡 NULL�� ��� 0�� ��ȯ*/
	if (root == NULL) {
		return 0;
	}
	/*���� ����� ���̿� �ڽĳ����� ���̸� ���Ͽ� ��ȯ*/
	return height + path_length(root->left, height + 1) + path_length(root->right, height + 1);
}

/*����Ʈ���� �¿��Ī*/
void reverse(TreeNode *root) {
	/*�ش��尡 NULL�� ��� ��ȯ*/
	if (root == NULL) {
		return;
	}
	/*�����ڽİ� �������ڽ��� swap*/
	TreeNode *temp;
	temp = root->right;
	root->right = root->left;
	root->left = temp;
	/*�����ڽ��� reverse*/
	reverse(root->left);
	/*�������ڽ��� reverse*/
	reverse(root->right);
}

/*Ʈ���� ������ȸ�Ͽ� ����� ������*/
void preorder(TreeNode *root) {
	TreeNode *p = root;
	if (p != NULL) {
		printf("%d ", p->key);
		preorder(p->left);
		preorder(p->right);
	}
}

int main() {
	/*Ʈ������*/
	Tree *tree = makeTree();
	/*Ʈ���� ��� ����*/
	InsertNode(tree, 5);
	InsertNode(tree, 2);
	InsertNode(tree, 7);
	InsertNode(tree, 1);
	InsertNode(tree, 3);
	InsertNode(tree, 6);
	InsertNode(tree, 8);

	/*������ Ʈ���� ����� ������ȸ�Ͽ� ��� ���*/
	printf("������� ������ Ʈ���� ���(������ȸ) : ");
	preorder(tree->root);
	printf("\n\n-------------------------------------------------------------------\n\n");

	printf("���� Ʈ���� �������� Ʈ���ΰ�? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");


	printf("key �� 0 ����\n");
	InsertNode(tree, 0);
	printf("���� Ʈ���� �������� Ʈ���ΰ�? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");


	printf("key �� 9 ����\n");
	InsertNode(tree, 9);
	printf("���� Ʈ���� �������� Ʈ���ΰ�? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");

	printf("Ű �� 5�� level : %d\n", level(tree->root, 5, 0));
	printf("Ű �� 3�� level : %d\n", level(tree->root, 3, 0));
	printf("Ű �� 9�� level : %d\n", level(tree->root, 9, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	printf("���� Ʈ���� ���� ���� Ʈ���ΰ�? : %c\n", isBalanced(tree->root) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");

	printf("key �� 10 ����\n");
	InsertNode(tree, 10);
	printf("���� Ʈ���� �������� Ʈ���ΰ�? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");
	
	printf("��� �ڽĳ������� ����� ���� : %d\n", path_length(tree->root, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	printf("key �� 10 ����\n");
	DeleteNode(tree, 10);
	printf("��� �ڽĳ������� ����� ���� : %d\n", path_length(tree->root, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	reverse(tree->root);
	printf("�¿� ��Ī�� Ʈ���� ������ȸ ��� : ");
	preorder(tree->root);
	printf("\n\n");

	return 0;
}