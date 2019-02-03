#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
int arr1[10001];
int arr2[10001];
int main() {
	FILE *inp = fopen("cross.inp", "rt");
	FILE *oup = fopen("cross.out", "wt");

	int test, n, input;
	int result = 0;
	fscanf(inp, "%d\n", &test);
	for (int t = 1; t <= test; t++) {
		fscanf(inp, "%d\n", &n);
		for (int i = 1; i <= n; i++) {
			fscanf(inp, "%d", &input);
			arr1[input] = i; // �������� ��ġ�� arr1[index]���� ����
		}
		for (int i = 1; i <= n; i++) {
			fscanf(inp, "%d", &input);
			arr2[input] = i; // �������� ��ġ�� arr2[index]���� ����
		}
		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if ((arr1[i] < arr1[j] && arr2[i] > arr2[j]) || (arr1[i] > arr1[j] && arr2[i] < arr2[j])) // �����Ǵ� ���
					result++;
			}
		}
		fprintf(oup, "Case %d: %d\n", t, result);
		result = 0;
		memset(arr1, 0, sizeof(arr1));
		memset(arr2, 0, sizeof(arr2));
	}
	return 0;
}