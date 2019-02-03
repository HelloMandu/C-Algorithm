#include<fstream>
#include<vector>
#include<algorithm>
#define Year 372
#define Month 31
#define Start true
#define End false
using namespace std;

typedef struct Date {
	bool type; // start : true, end : false
	int year; // ��
	int month; // ��
	int day; // ��
}Date;

int Allday(Date time) { // ����� ����, ���� �� �ϼ��� ��ȯ��
	return time.year * Year + time.month * Month + time.day;
}

bool compare(Date &event1, Date &event2) { // sort ���Լ�
	int Event1 = Allday(event1), Event2 = Allday(event2);
	if (Event1 == Event2) // ��¥�� ���� �� end�� start���� �տ�������
		return event1.type < event2.type;
	else
		return Event1 < Event2;
}

int timeline(vector<Date> &event) {
	int result = 0, row = 0; // �ִ� row�� ��, ���� row�� ��
	for (int i = 0; i < event.size(); i++) {
		row = (event[i].type == Start) ? row + 1 : row - 1; // start : +1, end : -1
		if (result < row) // ���� ������ ����
			result = row;
	}
	return result;
}

int main() {
	ifstream inp("timeline.inp");
	ofstream out("timeline.out");
	int t, n; // �� �׽�Ʈ ���̽�, ����� ��
	int year, month, day;
	char dot;
	inp >> t;
	while (t--) {
		vector<Date> event; Date input;
		inp >> n; 
		event.reserve(n * 2); // start + end
		while (n--) {
			inp >> input.year >> dot >> input.month >> dot >> input.day;
			input.type = Start; event.push_back(input); // Start
			inp	>> input.year >> dot >> input.month >> dot >> input.day;
			input.type = End; event.push_back(input); // End
		}
		sort(event.begin(), event.end(), compare); // ��ǵ��� �������� �������� ����
		out << timeline(event) << '\n';
	}
	return 0;
}