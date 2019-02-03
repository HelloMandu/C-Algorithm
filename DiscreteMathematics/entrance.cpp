#include<fstream>
#include<string.h>
#define MAX 1000
using namespace std;

int Qsize = 0; // Queue�� ��

void Entrance(int entrance[], int people) {
	Qsize = 0;
	bool check = false;
	for (int i = 0; i <= Qsize; i++) {
		if (entrance[i] < people) { // ���ο� ����� ������ �� ���� ��
			entrance[i] = people; // ���ο� ������� ����
			check = true; // ���� �Ϸ�
			break;
		}
	}
	if(!check) // ������ ���� �ʾ��� �� Qsize�� �� ĭ �ø�
		entrance[++Qsize] = people;
}

int main() {
	ifstream inp("entrance.inp");
	ofstream out("entrance.out");
	int t; // �� �׽�Ʈ ���̽�
	int n, people; // �� ��� ��
	int entrance[MAX] = { 0 };
	inp >> t;
	while (t--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> people;
			Entrance(entrance, people);
		}
		out << Qsize + 1 << '\n';
		Qsize = 0; memset(entrance, 0, sizeof(int) * n);
	}
	return 0;
}