#include<stdio.h>
#include<math.h>

FILE *input, *output;

int cal2(int y, int m, int cnt, char date1, char date2) { //Ƚ���� ������ ������ �� �ش� ���� ���ڸ� ���ϱ�
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	char arr[] = "SuMoTuWeThFrSa";
	int i;
	int s_date = 1; //���ؾ��� ���ڸ� ������ ����, ���� ���� ��¥�� ������ 1�Ϻ��� ����
	int start, total; // start:���� ���ۿ��� total: �� �ޱ����� �� day��

	if (!(y % 4) && y % 100 || !(y % 400))
		months[1]++;

	total = (y - 1 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400) + 1); // �־��� �⵵������ �� day�� 2016���̶�� 2015������� �� day�� ���Ѵ�.
				//(y - 1) / 4:���� 1�� ���ϱ�, (y - 1) / 100:������ �ƴ� 1�� ����, (y - 1) / 400):���� 1�� ���ϱ�

	for (i = 0; i < m - 1; i++)
		total += months[i];

	start = total % 7; // �� 7���̹Ƿ� 7�� ������ �Ǹ� ������ ���´� 0:�Ͽ���~6:�����
	s_date += (cnt - 1) * 7; // Ƚ����ŭ 7�� �����ش�. cnt�� 1�̸� ������ �ʿ䰡 ����.

	while (arr[(start * 2) % 14] != date1 || arr[(start * 2 + 1) % 14] != date2) { // ������ �ٸ��ٸ�, 2�־� ���� �ֱ� ������ *2���ش�.
		s_date++; // ���ϴ� ���� ����
		start++; // 2�־� ���� �ֱ� ������
	}
	if (months[m - 1] < s_date) // ���� ���ڰ� �ش� �� ���� ũ�ٸ�
		return -1; // -1����
	return s_date;
}

int cal1(int y, int m, int d) { // �ش� ��¥������ �� ���� ���ϱ�
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	int total = 0;

	total = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;

	if (!(y % 4) && y % 100 || !(y % 400))
		months[1]++;

	for (i = 0; i < m - 1; i++)
		total += months[i];

	total += d; // day�� ���Ѵ�

	return total;
}

int main() {

	input = fopen("input.inp", "r");
	output = fopen("output.out", "w");

	int t = 1;
	int y1, m1, d1, y2, m2, d2, cnt1, cnt2; // cnt�� Ƚ��
	char date1, date2, date3, date4, date5; // date�� ��¥ (date1,date2) , (date3,date4) , date5�� �ʿ���� �� �ޱ�
	int t_gap, gap1, gap2, gap3; // �� ��¥������ �� day��
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	while (1) {
		fscanf(input, "%d", &t);
		if (t == -1)
			break;
		switch (t) { //if �ʹ� ���Ƽ�
		case 0: {
			fscanf(input, "%d-%d-%d %d-%d-%d", &y1, &m1, &d1, &y2, &m2, &d2);
			if (!(y1 % 4) && y1 % 100 || !(y1 % 400))  // 4�� ���� �������� 100���� ���� �������� �����鼭 400���� ���� �������ٸ�
				months[1]++; // ���� üũ
			if (d1 > months[m1 - 1]) { // d1�� m1�� �ִ� ��¥���� ũ��
				fprintf(output, "-1\n");
				continue;
			}
			gap1 = cal1(y1, m1, d1); // ù��° ��¥
			months[1] = 28; // �ٽ� 28�� �ʱ�ȭ ���ش�
			if (!(y2 % 4) && y2 % 100 || !(y2 % 400))
				months[1]++;
			if (d2 > months[m2 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap2 = cal1(y2, m2, d2); // �ι�° ��¥
			t_gap = gap1 - gap2; // �� ��¥ ������ ����
			break;
		}
		case 1: {
			fscanf(input, "%d-%d-%d %d-%d-%d-%c%c%c", &y1, &m1, &d1, &y2, &m2, &cnt2, &date3, &date4, &date5); // date5�� ���� ����
			if (!(y1 % 4) && y1 % 100 || !(y1 % 400))
				months[1]++;
			if (d1 > months[m1 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap2 = cal2(y2, m2, cnt2, date3, date4); // day���ϱ�
			if (gap2 == -1) { // ���� day�� -1�̶�� -1���
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, d1) - cal1(y2, m2, gap2);
			break;
		}
		case 2: {
			fscanf(input, "%d-%d-%d-%c%c%c %d-%d-%d", &y1, &m1, &cnt1, &date1, &date2, &date5, &y2, &m2, &d2); // date5�� ���� ����
			if (!(y2 % 4) && y2 % 100 || !(y2 % 400))
				months[1]++;
			if (d2 > months[m2 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap1 = cal2(y1, m1, cnt1, date1, date2);
			if (gap1 == -1) {
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, gap1) - cal1(y2, m2, d2);
			break;
		}
		case 3: {
			fscanf(input, "%d-%d-%d-%c%c%c %d-%d-%d-%c%c%c", &y1, &m1, &cnt1, &date1, &date2, &date5, &y2, &m2, &cnt2, &date3, &date4, &date5);
			gap1 = cal2(y1, m1, cnt1, date1, date2);
			gap2 = cal2(y2, m2, cnt2, date3, date4);
			if (gap1 == -1 || gap2 == -1) {
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, gap1) - cal1(y2, m2, gap2);
			break;
		}
		}
		fprintf(output, "%d\n", abs(t_gap));
		months[1] = 28;
	}
	return 0;
}