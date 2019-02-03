#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int arr[300][300];

int matrix(int n) {
	int check = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 1) { // 1�� �ƴҶ�
				for (int t = 0; t < n; t++) {
					for (int s = 0; s < n; s++) {
						if (arr[i][s] + arr[t][j] == arr[i][j]) { // ������ �� ���� ���� ��
							check = 1;
							break; // s�ݺ���Ż��
						}
					}
					if (check == 1) // t�ݺ���Ż��
						break;
				}
				if (check == 0) // Good Matrix�� �ƴ� ��
					return 0;
				else
					check = 0;
			}
		}
	}
	return 1; // �� ������ �� �ȵǴ� ���� �����Ƿ� Good Matrix
}
int main() {
	FILE *inp = fopen("matrix.inp", "rt");
	FILE *out = fopen("matrix.out", "wt");

	int t, n;
	fscanf(inp, "%d\n", &t);
	while (t--) {

		fscanf(inp, "%d\n", &n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fscanf(inp, "%d", &arr[i][j]);
			}
		}

		fprintf(out, "%d\n", matrix(n));
		memset(arr, 0, sizeof(arr));
	}
	return 0;
}