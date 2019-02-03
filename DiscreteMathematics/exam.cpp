#include<fstream>
#include<string>
using namespace std;

bool Check_Question_mark(string good, char Qidx) { // ?���ǿ� �´� ���
	for (int i = 0; i < good.length(); i++) {
		if (good[i] == Qidx) // ���ǿ� �´� ���ĺ��� ������
			return true;
	}
	return false;
}

bool Check_Star_mark(string good, string Q, int index, int starlength) {// *���ǿ� �´� ��� �Ųٷ� ���
	int check = 0; // ����Ȯ��
	for (int i = 0; i < good.length(); i++) {
		for (int j = index; j < index + starlength; j++) {
			if (good[i] == Q[j]) // good�� �ִ� �������� üũ
				check++;
		}
	}
	if (check < starlength) // �ϳ��̻��� ���� ���ڰ� �ƴ� ��
		return true;
	else
		return false;
}

bool Question(string good, string P, string Q) {
	for (int i = 0; i < P.length(); i++) {
		if (P[i] == '?') { // ?�� ���
			if (!Check_Question_mark(good, Q[i])) // ?�� �f�� �� Ʋ�� ���
				return false;
		}
		else if (P[i] == '*') { // *�ΰ�� �Ųٷ� ���
			int starlength = (Q.length() - P.length()) + 1; // *���ڿ��� ����
			if (!Check_Star_mark(good, Q, i, starlength) && starlength != 0) // ?�� �f�� �� Ʋ�� ���
				return false;
			if (starlength != 0)
				Q.erase(i, starlength - 1); // *�κ��� ���ڿ��� ����� �ϳ��� index�� ���ܵΰ� �����
			else
				Q.insert(i, "*");
		}
		else if (P[i] != Q[i]) // �񱳰����� �� ���ڰ� �ٸ� ��
			return false;
	}
	return true; // *�̾��� ?�� ������ ��찡 �´� ���
}

int main() {
	ifstream inp("exam.inp");
	ofstream out("exam.out");
	int testcase, query;
	string good, P, Q;
	inp >> testcase;
	for (int i = 1; i <= testcase; i++) {
		inp >> good; // ��������
		inp >> P; // ?, * ������ ���ڿ�
		inp >> query; // ���Ǿ� ��
		out << "Test Case: #" << i << endl;
		while (query--) {
			inp >> Q; // ���Ǿ�
			if (Question(good, P, Q))
				out << "Yes" << endl;
			else
				out << "No" << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}