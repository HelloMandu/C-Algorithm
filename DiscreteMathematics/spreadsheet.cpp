#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
char input[20];
char output[20];

int NumtoAlphabet(int num) {
	int cnt = 0;
	int temp = 0;
	int div = num / 26; // ��
	int mod = num % 26; // ������
	for (int i = 0; num > 0; i++) {
		
		if (mod == 0 || (num % 26) == 0) {
			div--; mod += 26; num--;
		}
		output[i] = mod + 64;
		num /= 26;
		div = num / 26;
		mod = num % 26;
		
		cnt++;
	}
	for (int i = 0; i < cnt/2; i++) { //swap
		temp = output[i];
		output[i] = output[cnt - (i+1)];
		output[cnt - (i+1)] = temp;
	}
	return cnt;
}

void AlphabettoNum() {
	char arr[20];
	int num = 1;
	while (output[num] >= '0' && output[num] <= '9') // ���ڱ��� �̵�, �ڸ��� ���
		num++;
	int SC = num+1; // C�޺κ� index
	int Tnum = 0;//input���� �ڸ���
	output[num] = 67;
	int change = 0;
	while (input[Tnum] < '0' || input[Tnum] > '9')
		Tnum++;
	int temp = Tnum;

	for (int i = 0; i < temp; i++) 
		change += (int)pow(26, temp - (i + 1)) * ((input[i] - 64));

	sprintf(arr, "%d", change); // ���ڸ� ���ڿ���

	for (int i = SC, j = 0; arr[j] != NULL; i++, j++) {
		output[i] = arr[j];
	}
}

void typeA() {
	int C = 0;
	int cnt; // ����κг����� ���ںκ� ����
	int num = 0; //���ڸ� ������ ����
	while (input[C] != 'C')
		C++; // Cindex�� ã�ư�
	for (int i = C + 1; input[i] != NULL; i++) { //C���ںκ�����
		num *= 10;
		num += input[i] - '0';
	}
	cnt = NumtoAlphabet(num);
	//���� ��
	for (int i = 1; --C; i++) { // ���������ڳ־��ֱ�
		output[cnt++] = input[i];
	}
}
void typeB() {
	int num = 0;
	output[0] = 'R';
	while (input[num] < '0' || input[num] > '9') // ���ںκб��� �Ѿ
		num++;

	for (int i = 1; input[num] != NULL; i++) { // ó���� R�̹Ƿ� 1����
		output[i] = input[num++];
	}
	AlphabettoNum();
}
void spreadsheet() {
	if (input[0] == 'R' && input[1] > '0' && input[1] <= '9')
		typeA();
	else
		typeB();
}
int main() {
	FILE *inp = fopen("spreadsheet.inp", "rt");
	FILE *out = fopen("spreadsheet.out", "wt");

	int t;
	
	fscanf(inp, "%d\n", &t);
	while (t--) {
		fscanf(inp, "%s\n", &input);
		spreadsheet();
		for (int i = 0; output[i] != 0; i++) {
			fprintf(out, "%c", output[i]);
		}
		fprintf(out, "\n");
		memset(input, 0, sizeof(input));
		memset(output, 0, sizeof(output));
	}
	
	return 0;
}