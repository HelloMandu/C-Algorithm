#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#define YEARS 2201
#define MONTH 13
#define WEEK 7
#define DAY 32

using namespace std;

int abs(int n) {
	if (n > 0) return n;
	return -n;
}

typedef struct Calender {
	int weekDay, exchangeDay, weekCnt; // ���� ���������� �� �� ��, �� ��° ������ ����
}Calender; // �޷� ����ü ����

string weekList[WEEK] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" }; // ��, ��, ȭ, ��, ��, ��, �� �� �� ���� ���� ����
Calender calender[YEARS][MONTH][DAY]; // �޷� ���� ���� �迭

void CreateCalender() { // �޷� ���� �Լ�
	int totalDay = 1, weekDayCnt = 1; // �� �� ���� �� ���� �� ��° ������
	for (int year = 1; year < YEARS; year++) {
		/* �ų� */
		for (int month = 1; month < MONTH; month++) {
			/* �ſ� */
			int weekCnt = 1, wc = 0, minusDay = 0; // ���ο� ���� ���۵Ǹ� �ְ� ī��Ʈ�� 1�� �ʱ�ȭ, �׸��� ������ �ٸ� ������ �� ó�� ���� ����
			if (month < 8) {
				/* 8�� ���� ����Ǵ� ��Ģ */
				if (month % 2 == 0) { // �� ���� ¦��(2,4,6)�̸� 31�� ����
					if (month == 2) { // 2�� ���� ���� ó��
						if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) minusDay = 2; // ���� ó��
						else minusDay = 3; // �� �ܿ� 28�ϱ���
					}
					else minusDay = 1;
				}
			}
			else {
				/* 8�� ���Ŀ� ����Ǵ� ��Ģ */
				if (month % 2 == 1) minusDay = 1; // �� ���� Ȧ��(9, 11)�̸� 31�� ����
			}
			for (int day = 1; day < DAY - minusDay; day++) {
				/* ���� */
				calender[year][month][day].exchangeDay = totalDay;
				calender[year][month][day].weekDay = weekDayCnt;
				calender[year][month][day].weekCnt = weekCnt;
				totalDay++; // �� �� �� �Ϸ� �÷���
				weekDayCnt++; // ���� ī��Ʈ�� �ϳ� �÷���
				wc++;
				if (weekDayCnt % WEEK == 0) // 7���� ������ �ʱ�ȭ
					weekDayCnt = 0;
				if (wc % WEEK == 0) // �� �޿� �� ������ �� �� �־����� ī����
					weekCnt++;
			}
		}
	}
}

void split(vector<string> &list, string &date) { // ���ڿ��� ���ǿ� �°� �߶�
	while (date.find('-') != -1) {
		list.push_back(date.substr(0, date.find('-')));
		date = date.substr(date.find('-') + 1);
	}
}

int IndexingType1(string &date) { // ����-��-���� �ε����Ͽ� �� �� ���� ��ȯ
	vector<string> list;
	split(list, date);
	int y = atoi(list[0].c_str()), m = atoi(list[1].c_str()), d = atoi(date.c_str());
	return calender[y][m][d].exchangeDay;
}

int IndexingType2(string &date) { // ����-��-Ƚ��-������ �ε����Ͽ� �� �� ���� ��ȯ
	vector<string> list;
	split(list, date);
	int y = atoi(list[0].c_str()), m = atoi(list[1].c_str()), c = atoi(list[2].c_str());
	for (int day = 1; day < DAY && calender[y][m][day].exchangeDay != 0; day++) {
		/* Ư���� ���ķ� exchangeDay�� ���� 0�̸� �� ���� ���̻� �� �ʿ䰡 ���� */
		if (calender[y][m][day].weekCnt == c && weekList[calender[y][m][day].weekDay] == date) {
			/* �� ��° �������� �� ���� ���ϱ��� �Ϻ��ϰ� ������ => �� ���� �� �� �� ��ȯ */
			return calender[y][m][day].exchangeDay;
		}
	}
	return -1; // �Ϻ��ϰ� ���� �����Ͱ� ������ => �� �� �� �Է�
}

int main() {
	ifstream inp("calender.inp");
	ofstream out("calender.out");
	CreateCalender(); // �޷� ����
	while (true) {
		int type, dateResult1, dateResult2, result;
		string date1, date2;
		inp >> type;
		if (type == -1) break; // End Input
		inp >> date1 >> date2;
		/* Input Data */
		if (type > 1) dateResult1 = IndexingType2(date1);
		else dateResult1 = IndexingType1(date1);
		if (type % 2 == 1) dateResult2 = IndexingType2(date2);
		else dateResult2 = IndexingType1(date2);
		/* Calculate */
		if (dateResult1 <= 0 || dateResult2 <= 0) result = -1; // �̻��� ���� ������
		else result = abs(dateResult1 - dateResult2);
		out << result << '\n';
		/* Output Data */
	}
	inp.close();
	out.close();
	return 0;
}