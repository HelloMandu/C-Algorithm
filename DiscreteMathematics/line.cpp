#include<stdio.h>
#include<math.h>
#include<string.h>
#pragma warning(disable : 4996)

typedef struct Person {
	int k = 0; // �ᱣ��
	int max = 1000000000; // �ִ�
	int min = 0; // �ּ�
	int count = 0; // �˻��� Ƚ��
}Person;

int sequence(int A, int n) {
	if (A == 2)
		return 1;
	else
		return n + sequence(A - 1, n + 1);
}

int setsequence(int A) {
	if (A == 1)
		return 0;
	else
		return sequence(A, 1);
}

void line(Person *person, int Q, int A) {

	if (person->k != 0)
		return;
	int k;
	double mink, maxk;
	double minNum, maxNum;

	if (A == 1) {
		minNum = 1;
		maxNum = 0;
	}
	else {
		minNum = setsequence(A); // ��� ����
		maxNum = setsequence(A + 1) - 1;
	}
		mink = (Q - maxNum) / A; // �ּ�k��
		maxk = (Q - minNum) / (A - 1); // �ִ�k��
		mink = ceil(mink); maxk = floor(maxk); // �ּڰ�, �ִ� �ݿø�

	if (person->min < mink) // �ּڰ� ����
		person->min = mink;
	if (person->max > maxk) // �ִ� ����
		person->max = maxk;
	if (person->min == person->max)
		person->k = person->min;
	person->count++; // ����� ���
}

int main() {
	FILE *inp = fopen("line.inp", "rt");
	FILE *out = fopen("line.out", "wt");
	int t, m; // testcase, Question
	int Q, A; // PeopleNum, Line
	Person person;
	fscanf(inp, "%d\n", &t);
	while (t--) {
		fscanf(inp, "%d\n", &m);
		while (m--) {
			fscanf(inp, "%d %d\n", &Q, &A);
			line(&person, Q, A); // ���� ������Ʈ
		}
		if (person.k != 0)
			fprintf(out, "%d %d\n", person.count, person.k);
		else
			fprintf(out, "-1\n");
		memset(&person, 0, sizeof(person));
		person.max = 1000000000;
	}
	
	return 0;
}