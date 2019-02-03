#include<iostream>
#include<fstream>
#include<string>
#define _CRT_SECURE_NO_WARNINGS
#define abs(a) (a > 0 ? a : a * -1)
using namespace std;

int Month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
string Day[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

typedef struct Date1 { //����1
	int year;
	int month;
	int day;
}Date1;
typedef struct Date2 { // ����2
	int year;
	int month;
	int week;
	string day;
}Date2;

int year(int year) { // �⵵ ��� �Լ� // don't touch
	int result = 0;
	for (int i = 1; i < year; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
			result += 366;
		else
			result += 365;
	}
	return result;
}

int month(int year, int month) { // ���� ��� �Լ� // don't touch
	int result = 0;
	for (int i = 0; i < month - 1; i++)
		result += Month[i]; // ���� ���ϱ�
	return result;
}

int Week_day(int month, int week, string day, int result) { // �� ��� �Լ�
	// 0° ��, ����, �����
	int present = result % 7 + 1; // ���� ����
	int presult = result;
	string pday = Day[present]; // ���� ����
	int pweek = 0;
	int cnt = 0;
	for (int i = 0; i < Month[month - 1]; i++) {
		if (present == (result % 7) + 1)
			pweek++;
		if (pweek == week)
			break;
		result++;
	}
	for (int i = 0; i < 7; i++) {
		result++;
		if (Day[result % 7] == day)
			break;
	}
	if ((result - presult) > Month[month - 1]) return -1;

	return result;
}

int Result_Date1(Date1 *date) { //����-��-��
	Month[1] = 28;
	int y = 0;
	if (date->year % 4 == 0) {
		if (date->year % 100 == 0) {
			if (date->year % 400 != 0 && (date->month == 2 && date->day == 29)) 
				return -1;
			else if (date->year % 400 == 0) {
				Month[1]++;
				y++;
			}
		}
		else {
			Month[1]++;
			y++;
		}
	}
	else if(date->month == 2 && date->day == 29)
		return -1;

	if (y == 1&&date->month==2) {
		if (Month[date->month - 1] + 1 < date->day)
			return -1;
	}
	else if (Month[date->month - 1] < date->day)
		return -1;

	int result = year(date->year); // �⵵ ���
	result += month(date->year, date->month); // ���� ���
	result += date->day; // �� �� ���ϱ�
	
	return result;
}

int Result_Date2(Date2 *date) { // ����-��-Ƚ��-����
	Month[1] = 28;
	if (date->year % 4 == 0) {
		if (date->year % 100 == 0) {
			if (date->year % 400 == 0)
				Month[1]++;
		}
		else
			Month[1]++;
	}
	int result = year(date->year); // �⵵ ���
	result += month(date->year, date->month); // ���� ���
	result = Week_day(date->month, date->week, date->day, result);
	
	return result;
}

int main() {
	ifstream inp("calender.inp");
	ofstream out("calender.out");
	int type; // type
	char bar; // bar�Է¿�
	Date1 date1_1, date1_2;
	Date2 date2_1, date2_2;
	int result1, result2;
	while (true) {
		inp >> type;
		if (type == -1)	break;
		switch (type) {
		case 0:
			inp >> date1_1.year >> bar >> date1_1.month >> bar >> date1_1.day;
			inp >> date1_2.year >> bar >> date1_2.month >> bar >> date1_2.day;
			result1 = Result_Date1(&date1_1); result2 = Result_Date1(&date1_2);
			break;
		case 1:
			inp >> date1_1.year >> bar >> date1_1.month >> bar >> date1_1.day;
			inp >> date2_1.year >> bar >> date2_1.month >> bar >> date2_1.week >> bar >> date2_1.day;
			result1 = Result_Date1(&date1_1); result2 = Result_Date2(&date2_1);
			break;
		case 2:
			inp >> date2_1.year >> bar >> date2_1.month >> bar >> date2_1.week >> bar >> date2_1.day;
			inp >> date1_1.year >> bar >> date1_1.month >> bar >> date1_1.day;
			result1 = Result_Date2(&date2_1); result2 = Result_Date1(&date1_1);
			break;
		case 3:
			inp >> date2_1.year >> bar >> date2_1.month >> bar >> date2_1.week >> bar >> date2_1.day;
			inp >> date2_2.year >> bar >> date2_2.month >> bar >> date2_2.week >> bar >> date2_2.day;
			result1 = Result_Date2(&date2_1);  result2 = Result_Date2(&date2_2);
			break;
		}
		if (result1 != -1 && result2 != -1) // �� �� ��� �� ��
			out << abs(result1 - result2) << "\n"; 
		else // �� �� �ϳ��� �� �� ���� ��
			out << -1 << "\n";
	}
	return 0;
}