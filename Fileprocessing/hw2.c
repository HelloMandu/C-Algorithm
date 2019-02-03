#include<stdio.h>
#include<math.h>
#define MAX 100
#pragma warning(disable:4996)

int Hash_Table[MAX]; // �ؽ����̺� ����

int Hash_index(int key, int N, double Real_number) { // �ؽ� index�� ���
	double cal = key * Real_number; // �ε��� �� * �Ǽ�
	int temp = (int)cal; // �Ҽ��� ���� ����ϱ� ���� �ӽð�
	cal -= temp; //�Ҽ��� ������ ���
	cal = floorf(cal * 100) / 100; // �Ҽ��� 2��° �ڸ����� ����
	return (int)(N * cal); // index���� ���
}

void Hashing(int key, int N, double Real_number) {
	int index = Hash_index(key, N, Real_number); // �ؽ� ���
	if (Hash_Table[index] != 0) { // �浹�� �߻����� ��
		while (1) {
			if (index == N - 1 && Hash_Table[index] != 0)
				index %= N - 1; //  N-1�� �ڸ��� á���� ��带 ����� 0���� �ٽ� �̵�
			if (Hash_Table[index] == 0) { // Hash_Table�� ����
				Hash_Table[index] = key;
				return;
			}
			index++;
		}
	}
	// �浹�� ���� ���
	Hash_Table[index] = key; // Hash_Table�� ����
}

int main() {
	FILE *inp = fopen("hw2.inp", "r");
	FILE *out = fopen("hw2.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw2.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw2.out");
	int N; // �ؽ����̺��� ũ��
	double Real_number; // �Ǽ���
	int key; // Hash_Table�� ���� ��
	fscanf(inp, "%d%lf", &N, &Real_number);
	while (fscanf(inp, "%d", &key))
		Hashing(key, N, Real_number); // �ؽ��Լ�����
	for (int i = 0; i < N; i++) {
		if (Hash_Table[i] != 0) // 0�� �ƴ� ��� ���
			fprintf(out, "[%d,%d]\n", i, Hash_Table[i]);
	}
	fprintf(out, "*");
	fclose(inp); fclose(out);
	return 0;
}