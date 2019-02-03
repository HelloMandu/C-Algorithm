#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int *bucket;
int setarr() {
	bucket = (int*)malloc(sizeof(int) * 10000); // �迭 10000�� ����
	int idx = 0;
	for (char i1 = '1'; i1 <= '9'; i1++) {
		for (char i2 = '1'; i2 <= '9'; i2++) {
			if (i1 == i2) continue; // õ���ڸ��� �����ڸ��� ���� �� 
			for (char i3 = '1'; i3 <= '9'; i3++) {
				if (i1 == i3 || i2 == i3) continue; // �����ڸ��� �����ڸ��� ���� ��
				for (char i4 = '1'; i4 <= '9'; i4++) {
					if (i1 == i4 || i2 == i4 || i3 == i4) continue; // �����ڸ��� ���� �ڸ��� ���� ��
					int temp;
					temp = (i1 - 48) * 1000 + (i2 - 48) * 100 + (i3 - 48) * 10 + (i4 - 48);
					bucket[idx++] = temp;
				}
			}
		}
	}
	return idx;
}

int Strike(int *bucketnum, char num[]) {//strike ��
	int check = 0;
	int temp = *bucketnum;
	int a = temp / 1000;
	temp %= 1000;
	int b = temp / 100;
	temp %= 100;
	int c = temp / 10;
	temp %= 10;
	int d = temp;

	if (a == num[0] - '0') check++;
	if (b == num[1] - '0') check++;
	if (c == num[2] - '0') check++;
	if (d == num[3] - '0') check++;

	return check;
}
int Ball(int *bucketnum, char num[]) {//ball �� 
	int check = 0;
	int temp = *bucketnum;
	char tmp[4];
	tmp[0] = temp / 1000;
	temp %= 1000;
	tmp[1] = temp / 100;
	temp %= 100;
	tmp[2] = temp / 10;
	temp %= 10;
	tmp[3] = temp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) continue;
			else if (tmp[i] + '0' == num[j]) check++;
		}
	}
	return check;
}

int Cal(char num[], int strike, int ball, int count) {
	int *newbucket = (int*)malloc(sizeof(int) * count);
	int cnt = 0;
	for (int i = 0; i < count; i++) {
		if (Strike(&bucket[i], num) == strike && Ball(&bucket[i], num) == ball)
			newbucket[cnt++] = bucket[i];
	}
	free(bucket);
	bucket = newbucket;
	newbucket = NULL;
	return cnt;
}

int main() {
	FILE *inp = fopen("numgame.inp", "r");
	FILE *out = fopen("numgame.out", "w");
	int T, Q;
	char num[5];
	int strike = 0;
	int ball = 0;
	int count = 0;
	//Testcase�Է� 
	fscanf(inp, "%d\n", &T);
	while (T--) {//Testcase��ŭ ������
		count = setarr();
		fscanf(inp, "%d\n", &Q);//������ Ƚ��k �Է�
		for (int i = 0; i < Q; i++) {
			fscanf(inp, "%s %d %d\n", &num, &strike, &ball);//k�ٸ�ŭ ������ 4�ڸ���, strike, ball
			count = Cal(num, strike, ball, count);
		}
		fprintf(out, "%d\n", count);
		if (count >= 6) {
			for (int j = 0; j < 3; j++)   //�׸�ŭ ���
				fprintf(out, "%d\n", bucket[j]);
			for (int k = count - 3; k < count; k++)
				fprintf(out, "%d\n", bucket[k]);
		}
		else {
			for (int j = 0; j < count; j++)
				fprintf(out, "%d\n", bucket[j]);
		}
		free(bucket);
	}
	return 0;
}