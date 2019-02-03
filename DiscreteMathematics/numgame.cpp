#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<char *> bucket;

void setbucket() {
	for (char i1 = '1'; i1 <= '9'; i1++) {
		for (char i2 = '1'; i2 <= '9'; i2++) {
			if (i1 == i2) continue; // õ���ڸ��� �����ڸ��� ���� �� 
			for (char i3 = '1'; i3 <= '9'; i3++) {
				if (i1 == i3 || i2 == i3) continue; // �����ڸ��� �����ڸ��� ���� ��
				for (char i4 = '1'; i4 <= '9'; i4++) {
					if (i1 == i4 || i2 == i4 || i3 == i4) continue; // �����ڸ��� ���� �ڸ��� ���� ��
					char *temp = new char[5];
					temp[0] = i1; temp[1] = i2; temp[2] = i3; temp[3] = i4; temp[4] = '\0';
					bucket.push_back(temp); // ��Ŷ�� ����
				}
			}
		}
	}
}

int StrikeCheck(char *bucketnum, char *strike) {
	int check = 0;
	for (int i = 0; i < 4; i++) {
		if (bucketnum[i] == strike[i]) check++;
	}
	return check;
}
int BallCheck(char *bucketnum, char *ball) {
	int check = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				continue; // strike�� ��
			else if (bucketnum[i] == ball[j])
				check++; // ball�϶�
		}
	}
	return check;
}

void numgame(char *num, int strike, int ball) {
	vector<char *> newBucket;
	for (int i = 0; i < bucket.size(); i++) {
		if (StrikeCheck(bucket[i], num) == strike && BallCheck(bucket[i], num) == ball)
			newBucket.push_back(bucket[i]);
	}
	bucket.clear(); // �޸� ����
	bucket = newBucket;
}

int main() {
	ifstream inp("numgame.inp");
	ofstream out("numgame.out");
	int t, k;
	char *num = new char[5]; // ����
	int strike, ball; // ��ũ����Ʈ, ��
	inp >> t;
	while (t--) {
		inp >> k;
		setbucket(); //��Ŷ �ʱ�ȭ
		while (k--) {
			inp >> num >> strike >> ball;
			numgame(num, strike, ball);
		}
		if (bucket.size() <= 6) { // ������ ���� 6�� ������ ��
			out << bucket.size() << "\n";
			for (int i = 0; i < bucket.size(); i++)
				out << bucket[i] << "\n";
		}
		else { // 6�� �̻��� ��
			out << bucket.size() << "\n";
			for (int i = 0; i < 3; i++)
				out << bucket[i] << "\n";
			for (int i = 3; i > 0; i--) {
				out << bucket[bucket.size() - i] << "\n";
			}
		}
		bucket.clear();
	}
	inp.close();
	out.close();
	return 0;
}