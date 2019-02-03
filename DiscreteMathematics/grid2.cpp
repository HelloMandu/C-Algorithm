#include<stdio.h>
// m, n-1, m-1, n-2, m-2, n-3, m-3....
int StartPoint3(int n, int m, int start) { // type3�� �ʱⰪ ����
	switch (start) {
	case 1:
		return 0; // �����:�»�
	case 2:
		return 0; // �����:���
	case 3:
		return n * m + 1; // �����:����
	case 4:
		return n * m + 1; // �����:����
	}
}
int StartPoint4(int n, int m, int start) { // type4�� �ʱⰪ ����
	switch (start) {
	case 1:
		return -m + 1; // �����:�»�
	case 2:
		return m + 1; // �����:���
	case 3:
		return n * m + m; // �����:����
	case 4:
		return n * m - m; // �����:����
	}
}

int type3(int n, int m, int start, int len) {
	int result = StartPoint3(n, m, start); // �����
	int dir;
	int row = n, col = m; // ��, �� ���� ����
	n--; m--;
	switch (start) { // ó�� ���� ���� : type3
	case 1:
		dir = 1; // right
		m++;
		break;
	case 2:
		dir = 2; // down
		n++;
		break;
	case 3:
		dir = 3; // left
		m++;
		break;
	case 4:
		dir = 4; // up
		n++;
		break;
	}
	while (len > 0) {
		if (dir > 4) // ���� ����
			dir = 1;
		switch (dir) { // ���Ⱚ�� 1�� �����ϸ鼭 ���
		case 1:
			if ((len - m) > 0)
				result += m;
			else
				return result + len;
			dir++;
			len -= m--;
			break;
		case 2:
			if ((len - n) > 0)
				result += col*n;
			else
				return result + col*len;
			dir++;
			len -= n--;
			break;
		case 3:
			if ((len - m) > 0)
				result -= m;
			else
				return result - len;
			dir++;
			len -= m--;
			break;
		case 4:
			if ((len - n) > 0)
				result -= col * n;
			else
				return result - col*len;
			dir++;
			len -= n--;
			break;
		}
	}
}

int type4(int n, int m, int start, int len) {
	int result = StartPoint4(n, m, start); // �����
	int dir;
	int row = n, col = m; // ��, �� ���� ����
	n--; m--;
	switch (start) { // ó�� ���� ���� : type4
	case 1:
		dir = 1; // right
		n++;
		break;
	case 2:
		dir = 4; // down
		m++;
		break;
	case 3:
		dir = 3; // left
		n++;
		break;
	case 4:
		dir = 2; // up
		m++;
		break;
	}
	while (len > 0) {
		if (dir > 4) // ���� ����
			dir = 1;
		switch (dir) { // ���Ⱚ�� 1�� �����ϸ鼭 ���
		case 1:
			if ((len - n) > 0)
				result += col * n;
			else
				return result + col * len;
			dir++;
			len -= n--;
			break;
		case 2:
			if ((len - m) > 0)
				result += m;
			else
				return result + len;
			dir++;
			len -= m--;
			break;
		case 3:
			if ((len - n) > 0)
				result -= col * n;
			else
				return result - col * len;
			dir++;
			len -= n--;
			break;
		case 4:
			if ((len - m) > 0)
				result -= m;
			else
				return result - len;
			dir++;
			len -= m--;
			break;
		}
	}
}
int main() {

	FILE *inp = fopen("grid2.inp", "r");
	FILE *out = fopen("grid2.out", "w");

	int test;
	fscanf(inp, "%d", &test);

	int n, m, type, start, len;
	int result;
	while (test--) {
		fscanf(inp, "%d %d %d %d %d", &n, &m, &type, &start, &len);
		if (type == 3)
			result = type3(n, m, start, len);
		else
			result = type4(n, m, start, len);
		fprintf(out, "%d\n", result);
	}
	return 0;
}