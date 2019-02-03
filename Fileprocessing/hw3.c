#include<stdio.h>
#include<stdlib.h>
#define m_ary 10 // 10�� Ʈ����
#define record 4 // ���ڵ���� || ����
#pragma warning(disable:4996)

int Nodesize = 1; // ����� ������ ���� (��Ʈ����)

typedef struct Node {
	int check_leaf; // �������� üũ
	char trie[record]; // ��θ� ����
	char address[record]; // �����ּ�
	struct Node *next[m_ary]; // �ڽĳ�带 ����ų �迭
}Node;

typedef struct TrieTree { // Ʈ���� ��Ʈ��� ����
	Node *root;
}TrieTree;

Node *createNode() { // ���ο� ��� ����
	Node *newNode = (Node*)malloc(sizeof(Node));
	for (int i = 0; i < m_ary; i++)
		newNode->next[i] = NULL;
	return newNode;
}

void InsertAddress(Node *leaf, char trie[], char address[]) { // ������� : �ּҰ��� ����
	leaf->check_leaf = 1; // üũ������� ����
	for (int i = 0; i < record; i++) // Ű���� ����
		leaf->address[i] = address[i];
	for (int i = 0; i < record; i++) // ��ΰ��� ����
		leaf->trie[i] = trie[i];
		Nodesize--; // �����Ʒ��� ���Ե� ���--
}

void InsertTrie(TrieTree *Trie, char trie[], char address[]) { // Ű���� ����
	Node *child = Trie->root;
	for (int i = 0; i < record; i++) {
		if (!child->next[trie[i] - '0']) { // �ڽĳ�尡 ���� �� ���ο� ��带 ����
			child->next[trie[i] - '0'] = createNode();
			Nodesize++; // ��尳��++
		}
		child = child->next[trie[i] - '0']; // ��尡 ���� ��
	}
	// ������ �ּҸ� ����
	InsertAddress(child, trie, address); 
}

int Check_Wild_Card(char wild_card[]) { // ���ϵ�ī��Ÿ���� ����
	for (int i = 0; i < record; i++) {
		if (wild_card[i] == '*') // ���ϵ�ī�尡 ��������
			return 1;
	}
	return 0; // ���ϵ�ī�尡 ������
}

int address_check(Node *child, char wild_card[]) { // ���� ã�� ���ڵ����� üũ
	for (int i = 0; i < record; i++) {
		if (child->trie[i] != wild_card[i]) // �ϳ��� Ʋ����
			return 0;
	}
	return 1; // ��� ���� ��
}

void Print_Wild_Card(Node *child, FILE *out) { // ���ϵ�ī�尡 ���� �� ���
	int recordCount = 0;
	for (int i = 0; i < m_ary; i++) {
		if (child->next[i] != NULL) { // NULL�� �ƴҶ�
			if (child->next[i]->check_leaf != 1) { // ��������
					Print_Wild_Card(child->next[i], out);
			}
			else { // ������ ���� ���
				for (int j = 0; j < record; j++)
					fprintf(out, "%c", child->next[i]->trie[j]);
				fprintf(out, " %d ", ++recordCount);
				for (int j = 0; j < record; j++)
					fprintf(out, "%c", child->next[i]->address[j]);
				fprintf(out, " ");
			}
			
		}
	}
}

void PrintTrie(TrieTree *Trie, char wild_card[], char address[], FILE *out) { // Ʈ���� ���
	Node *parent = NULL;
	Node *child = Trie->root; // ��Ʈ;
	for (int i = 0; i < record && wild_card[i - 1] != '*'; i++) {
		if (child == NULL) { // �ش��ΰ� �������� ������
			fprintf(out, "no\n");
			return;
		}
		if (wild_card[i] != '*') {
			parent = child;
			child = parent->next[wild_card[i] - '0']; // �ڽ� ����
		}
	}
	if (Check_Wild_Card(wild_card)) { // record�� �ִ� ���
		Print_Wild_Card(child, out); // child����
		fprintf(out, "\n");
	}
	else { // record�� ���� ��� 
		int recordCount = 0;
		for (int i = 0; i < m_ary; i++) {
			if (parent->next[i] != NULL) {// NULL�� �ƴ� ���
				if (address_check(parent->next[i], wild_card)) // �ּҰ� �´��� Ȯ��
					break; // �ּҰ� ������ ��ġ�� á�����Ƿ� break;
				recordCount++;
			}
		}
		if(child == NULL)
			fprintf(out, "no\n");
		else {
			for (int i = 0; i < record; i++)
				fprintf(out, "%c", child->trie[i]);
			fprintf(out, " %d ", ++recordCount);
			for (int i = 0; i < record; i++)
				fprintf(out, "%c", child->address[i]);
			fprintf(out, "\n");
		}
	}
}

int main() {
	FILE *inp = fopen("hw4.inp", "r");
	FILE *out = fopen("hw4.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw3.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw3.out");
	char bracket; // ��ȣ
	TrieTree *Trie = (TrieTree*)malloc(sizeof(TrieTree));
	Trie->root = createNode(); // Ʈ����Ʈ���� ��Ʈ��� ����
	char trie[record], address[record]; // �������ڵ��, ����� �ּҰ�
	while (1) { // ù��° �� �Է�
		fscanf(inp, "%c", &bracket); // (
		for (int i = 0; i < record; i++)
			fscanf(inp, "%c", &trie[i]); // ���ڵ带 �Է¹���
		fscanf(inp, "%c", &bracket);// ,
		for (int i = 0; i < record; i++)
			fscanf(inp, "%c", &address[i]); // �ּҰ��� �Է¹���
		fscanf(inp, "%c", &bracket); // )
		InsertTrie(Trie, trie, address); // Ʈ���̻���
		fscanf(inp, "%c", &bracket); // ' '
		if (bracket == '\n')
			break;
	}
	fprintf(out, "%d\n", Nodesize); // ����� ������ ���
	while (1) {
		char wild_card[record]; // ���ϵ� ī��
		for (int i = 0; i < record && wild_card[i - 1] != '*'; i++)
			fscanf(inp, "%c", &wild_card[i]); // ���ڵ带 �Է¹���
		PrintTrie(Trie, wild_card, address, out);
		fscanf(inp, "%c", &bracket); // ' '
		if (bracket == '\n')
			break;
	}
	fprintf(out, "*");
	fclose(inp); fclose(out);
	return 0;
}