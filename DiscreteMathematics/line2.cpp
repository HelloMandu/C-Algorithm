#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)
int Line1[1000];
int Line2[1000];
int result[1000];

void swap(int i, int j) {
	int temp;
	for (int a = j; a < i; a++) { // Line2�� �������� ã�ư���
		temp = Line2[a];
		Line2[a] = Line2[a + 1];
		Line2[a + 1] = temp;
	}
}

void Line(int n) {
	for (int i = n - 1; i > 0; i--) { // �ڿ��� ����
		for (int j = 0; j < n; j++) {
			if (Line1[i] == Line2[j]) {// ���� ������ ã�´�
				result[Line1[i] - 1] = i - j; // �̵��� ��ġ��ŭ ����
				swap(i, j);
				break;
			}
		}
	}
}

int main() {
	FILE *inp = fopen("line2.inp", "rt");
	FILE *out = fopen("line2.out", "wt");
	int t, n;
	fscanf(inp, "%d\n", &t);
	while (t--) {
		fscanf(inp, "%d\n", &n);
		for (int i = 0; i < n; i++)
			fscanf(inp, "%d", &Line1[i]);
		for (int i = 0; i < n; i++)
			fscanf(inp, "%d", &Line2[i]);
		Line(n);
		for (int i = 0; i < n; i++)
			fprintf(out, "%d ", result[i]);
		fprintf(out, "\n");
		memset(Line1, 0, sizeof(Line1)); memset(Line2, 0, sizeof(Line2)); memset(result, 0, sizeof(result));
	}
	return 0;
}