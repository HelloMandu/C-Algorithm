#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

TreeNode *LL_rotate(TreeNode *root) { // LLȸ��
	TreeNode *child = root->left;
	root->left = child->right;
	child->right = root;
	return child;
}

TreeNode *RR_rotate(TreeNode *root) { // RRȸ��
	TreeNode *child = root->right;
	root->right = child->left;
	child->left = root;
	return child;
}

TreeNode *LR_rotate(TreeNode *root) { // LRȸ��
	TreeNode *child = root->left;
	root->left = RR_rotate(child);
	return LL_rotate(root);
}

TreeNode *RL_rotate(TreeNode *root) { // RLȸ��
	TreeNode *child = root->right;
	root->right = LL_rotate(child);
	return RR_rotate(root);
}

int GetHeight(TreeNode *root) { // Ʈ���� ���̸� ����Ͽ� ��ȯ
	if (root == NULL)
		return 0;
	int leftH = GetHeight(root->left); // ���� ���� Ʈ�� ���� ���
	int rightH = GetHeight(root->right); // ������ ���� Ʈ�� ���� ���
	return leftH > rightH ? leftH + 1 : rightH + 1; // ū ���� ���̸� ��ȯ
}

int Getbalance(TreeNode *root) { // �� ���� Ʈ���� ������ ���� ��ȯ 
	if (root == NULL)
		return 0;
	return GetHeight(root->left) - GetHeight(root->right); // leftHeight - rightHeight
}

TreeNode *rebalance(TreeNode *root) {
	int BF = Getbalance(root); // �����μ��� ���
	if (BF > 1) { // �����μ��� 1���� ū ���
		if (Getbalance(root->left) > 0) // �����ڽ� �����μ��� ����̸� LL
			root = LL_rotate(root);
		else // �����ڽ� �����μ��� �����̸� LR
			root = LR_rotate(root);
	}
	else if (BF < -1) { // �����μ��� 1���� ���� ���
		if (Getbalance(root->right) < 0) // �������ڽ� �����μ��� �����̸� RR
			root = RR_rotate(root);
		else // �������ڽ� �����μ��� ����̸� RL
			root = RL_rotate(root);
	}
	return root;
}

TreeNode *insert_AVL_Node(TreeNode *root, int key) { // AVL��� ����
	if (root == NULL) { // ��Ʈ�� ���� ��
		root = (TreeNode*)malloc(sizeof(TreeNode));
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
	else if (key < root->key) { // Ű���� ��Ʈ���� ���� ��
		root->left = insert_AVL_Node(root->left, key);
		root = rebalance(root);
	}
	else if (key > root->key) {  // Ű���� ��Ʈ���� Ŭ ��
		root->right = insert_AVL_Node(root->right, key);
		root = rebalance(root);
	}
	return root;
}

TreeNode *delete_AVL_Node(TreeNode *root, int key) { // AVL��� ����
	if (root == NULL) // ������ ��尡 ���� ���
		return root;
	else if (key < root->key) // Ű���� ���� ���
		root->left = delete_AVL_Node(root->left, key);
	else if (key > root->key)// Ű���� Ŭ ���
		root->right = delete_AVL_Node(root->right, key);
	else { // Ű ���� ã�� ���
		if (root->left == NULL && root->right == NULL) { // ������ ��尡 �ܸ������ ���
			free(root); // �ܸ���� ����
			return NULL; // NULL�� ��ȯ
		}
		else if (root->left == NULL || root->right == NULL) { // ������ ��尡 �ڽ� ��带 �� �� ���� ���
			TreeNode *child;
			if (root->left != NULL)
				child = root->left;
			else
				child = root->right;
			free(root);
			return child;
		}
		else { // ������ ��尡 �ڽ� ��带 �� �� ���� ���
			TreeNode *succ_parent = root, *succ = root->left;
			while (succ->right != NULL) { // ���� ����Ʈ������ �İ��� ã��
				succ_parent = succ;
				succ = succ->right;
			}
			if (succ_parent->left == succ)
				succ_parent->left = succ->left;
			else
				succ_parent->right = succ->left;
			root->key = succ->key;
			free(succ);
		}
	}
	return rebalance(root);
}

void preorder(TreeNode *root, FILE *out) { // ������ȸ
	if (root) {
		fprintf(out, "%d ", root->key);
		preorder(root->left, out);
		preorder(root->right, out);
	}
}

int main() {
	FILE *inp = fopen("hw4.inp", "r");
	FILE *out = fopen("hw4.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw4.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw4.out");
	TreeNode *root = NULL; // Ʈ���� ��Ʈ��� ����
	int key; // Ű��
	char enter = ' '; // ����
	while (enter != '\n') { // ��� ����
		fscanf(inp, "%d%c", &key, &enter);
		root = insert_AVL_Node(root, key);
	}
	preorder(root, out); fprintf(out, "\n"); // ���� ��ȸ
	while (enter != '\n') { // ��� ����
		fscanf(inp, "%d%c", &key, &enter);
		root = delete_AVL_Node(root, key);
	}
	preorder(root, out); fprintf(out, "\n*"); // ���� ��ȸ
	fclose(inp); fclose(out);
	return 0;
}