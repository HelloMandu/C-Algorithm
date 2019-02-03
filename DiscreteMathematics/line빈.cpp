#include<stdio.h>
#include<math.h>
#pragma warning(disable : 4996)
#define MAX(a,b) (a > b  ? a: b)
#define min(a,b) (a< b ? a:b)

typedef struct line {
	int q;
	int a;
};
line arr[100]; //m�� �ִ� 100

int main() {

	FILE *input = fopen("line.inp", "r");
	FILE *output = fopen("line.out", "w");

	int k_max, k_min, k;
	int t, m, q, a, b;
	int i;
	int num, add;

	fscanf(input, "%d", &t);
	while (t--) {
		fscanf(input, "%d", &m);
		for (i = 0; i < m; i++)
			fscanf(input, "%d %d", &arr[i].q, &arr[i].a); //line �迭�� ��� �ޱ�
		k_max = 1000000000, k_min = 1; //q�� ���� �ִ� 1000000000 �ּ� 1
		for (i = 0; i < m; i++) {
			num = 1, add = 0;
			if (arr[i].a == 1) { //ù ��° ������ ���
				k_min = MAX(arr[i].q, k_min); //������ min���� ũ�� min�ٲ�. �� ũ�� min �״��
				continue;
			}
			b = arr[i].a; //num���ϱ� ���� ����
			while (--b) {
				num += add++; //2��° ���� ù ���� ��ȣ k+num(1), 3��° ���� ù ���� ��ȣ 2k+num+1, 4��° ���� ù ���� ��ȣ 3k+num+2, n��° ���� ù ���۹�ȣ (n-1)k+num+(n-2)
			}
			k = (arr[i].q - num) / (arr[i].a - 1); //q�� a���� ���� ó���� ���� ���, ������ �����ϸ� ��(int�� �ٲ�鼭 �˾Ƽ� ����ó��)
			k_max = min(k, k_max); //������ ���ں��� �۾ƾ� min<k<MAX �� MAX �ٲ�
			k = ceil((arr[i].q - (num + arr[i].a - 2)) / (double)arr[i].a); //q�� a���� ���� ���� ���� ���, ������ �ø��ϸ� ��(ceil�� ���� ������ �ø�ó��)
			k_min = MAX(k, k_min); //������ ���ں��� Ŀ�� min<k<MAX �� min �ٲ�
			if (k_min == k_max) {
				fprintf(output, "%d %d\n", i + 1, k_min); //�迭�� 0���� �����ϹǷ� i+1���ֱ�
				break;
			}
		}
		if (k_min != k_max)
			fprintf(output, "-1\n");
	}
	return 0;
}