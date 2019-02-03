#include<stdio.h>
#pragma warning(disable : 4996)

int dice[10000][6];

int setceiling(int floor, int row) { // �ٴڼ���
	int i;
	for (i = 0; i < 6; i++) { // �ٴ��� ����ִ��� ã�´�
		if (floor == dice[row][i]) {
			break;
		}
	}
	switch (i) { // �ٴڿ���
	case 0:
		return dice[row][5];
	case 1:
		return dice[row][3];
	case 2:
		return dice[row][4];
	case 3:
		return dice[row][1];
	case 4:
		return dice[row][2];
	case 5:
		return dice[row][0];
	}
}

int sum(int t, int surface) { // dice�迭
	int max = 0, result = 0; // �ִ�, �����
	int ceiling, floor; // õ��, �ٴ�
	int i = 0, j = 0;
	floor = dice[0][surface]; // �ʱ�ٴڼ���
	ceiling = setceiling(floor, i); // �ʱ�õ�弳��
	for (i = 0; i < t; i++) {
		for (j = 0; j < 6; j++) {
			if (dice[i][j] != ceiling && dice[i][j] != floor) { // õ��� �ٴ��� �ƴ� ��
				if (max < dice[i][j]) // �ִ� ����
					max = dice[i][j];
			}
		}
		result += max; // ����� ����
		floor = ceiling; // �ٴڼ���
		ceiling = setceiling(floor, i+1); // õ�弳��
		max = 0;
	}
	return result;
}

int max(int result[]) {
	int max = 0;
	for (int i = 0; i < 6; i++) {
		if (max < result[i])
			max = result[i];
	}
	return max;
}

int main() {
	FILE *inp = fopen("dice.inp", "rt");
	FILE *out = fopen("dice.out", "wt");
	int t;
	int result[6]; // ���6������
	fscanf(inp, "%d\n", &t);
	for (int i = 0; i < t; i++) {
		fscanf(inp, "%d %d %d %d %d %d\n",
		&dice[i][0], &dice[i][1], &dice[i][2], &dice[i][3], &dice[i][4], &dice[i][5]);
	}
	for (int i = 0; i < 6; i++)
		result[i] = sum(t, i); // ��� 6�� ����
	
	fprintf(out, "%d", max(result)); // 6���� ���� ū �� ���

	return 0;
}