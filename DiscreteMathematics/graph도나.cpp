#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX 10000

typedef struct Graph {
	int E; // ���� ����
	int weight; // ����ġ
}Graph;

Graph graph[MAX][MAX];
int length[MAX];
bool check[MAX]; // �湮�޴��� üũ
int Stack[MAX];
int Queue[MAX];
int top = -1;
int front = -1, rear = -1;

int compare(const void *arg1, const void * arg2) {
	int v1 = ((Graph *)arg1)->E;
	int v2 = ((Graph *)arg2)->E;
	if (v1 > v2) return 1;
	else return -1;
}

int DFS_Traversal(int V, int n) {
	int result = 0;
	Stack[++top] = V;
	check[V] = true; // �湮�� ���� true
	while (top != -1) { // stack�� ������ �� �� ����
		for (int i = 0; i < length[V]; i++) { // ���������� ���� ������ �˻�
			if (check[graph[V][i].E] != true) { // ���� ������ �湮���� ���� ������ ��
				check[graph[V][i].E] = true; // �湮�� ���� true
				Stack[++top] = graph[V][i].E; // ������ push
				result += graph[V][i].weight; // ����ġ+
				V = graph[V][i].E; // ������ �ٲ�
				i = -1; // ó������ ���� ����
			}
		}
		V = Stack[--top]; // �ٵ����� �� top�� ��������
	}
	memset(check, false, sizeof(bool) * n); // check�� �ʱ�ȭ
	return result;
}

int BFS_Traversal(int V, int n) { // �ʺ�켱Ž��, Queue
	int result = 0;
	Queue[++rear] = V; // �������� push
	check[V] = true; // �湮�� ���� true
	while (front != rear) { // Queue�� ������ �� �� ����
		V = Queue[++front]; // �ٵ����� �� top�� �������� 
		for (int i = 0; i < length[V]; i++) { // ���������� ���� ������ �˻�
			if (check[graph[V][i].E] != true) { // ���� ������ �湮���� ���� ������ ��
				check[graph[V][i].E] = true; // �湮�� ���� true
				Queue[++rear] = graph[V][i].E; // ������ push
				result += graph[V][i].weight; // ����ġ+
			}
		}
	}
	front = -1; rear = -1;
	memset(check, false, sizeof(bool) * n); // check�� �ʱ�ȭ
	return result;
}

int main() {
	FILE *inp = fopen("graph.inp", "rt");
	FILE *out = fopen("graph.out", "wt");
	int t; // ���׽�Ʈ���̽�
	int n, m; // ����, ������ ����
	int V, E, weight; // ����
	int k, start; // ��ȸ�� ������ ��, ��������

	fscanf(inp, "%d", &t);
	while (t--) {
		fscanf(inp, "%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			fscanf(inp, "%d %d %d", &V, &E, &weight);
			graph[V][length[V]].E = E; // ����
			graph[V][length[V]++].weight = weight;
			graph[E][length[E]].E = V; // ����
			graph[E][length[E]++].weight = weight;
		}

		for (int i = 0; i < n; i++) // ������ ���̼����� ����
			qsort(graph[i], length[i], sizeof(Graph), compare);

		fscanf(inp, "%d", &k); // ���������� ��
		while (k--) {
			fscanf(inp, "%d", &start); // ��������
			fprintf(out, "n=%d m=%d start=%d DFS:%d BFS:%d\n", n, m, start, DFS_Traversal(start, n), BFS_Traversal(start, n));
		}
		memset(length, 0, sizeof(int)*n);
	}
	return 0;
}