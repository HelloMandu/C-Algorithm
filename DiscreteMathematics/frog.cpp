#include<fstream>
#include<vector>
using namespace std;

typedef struct Stone {
	char kind; // ���� ����
	int width; // �ʺ�
	bool check; // ���� ��Ѵ��� üũ
}Stone;

vector<Stone> stone;

int Foward(int N, int D) { // ������
	int max = 0; //�ִ� �Ÿ�
	int width = 0; // ���� �̵��� �Ÿ�
	for (int i = 1; i <= N; i++) {
		if (stone[i].kind == 'B') { // B�϶� ������ ����
			if (max < stone[i].width - width) // ���� �̵��Ÿ��� �����̵��Ÿ����� ���� ��
				max = stone[i].width - width; // �ִ� �̵��Ÿ� ����
			width = stone[i].width; // �̵��Ÿ� ����
		}
		else if (stone[i].kind == 'S' && stone[i].check != true) { // S�϶� �ȹ��� ���
			if (max < stone[i].width - width) // ���� �̵��Ÿ��� �����̵��Ÿ����� ���� ��
				max = stone[i].width - width; // �ִ� �̵��Ÿ� ����
			width = stone[i].width; // �̵��Ÿ� ����
			stone[i].check = true; // ���� check
			if (stone[i + 1].kind == 'S') // ���� ���� ���� S�� ��� ��ĭ �ǳ� ��
				i++;
		}
	}
	if (D - width > max) // ������ ���� ����� �Ÿ��� �ִ� �Ÿ��� ��
		max = D - width;
	return max;
}

int Reverse(int N, int D) { // ������
	int max = 0; //�ִ� �Ÿ�
	int width = D; // ���� �̵��� �Ÿ�
	for (int i = N; i > 0; i--) {
		if (stone[i].kind == 'B') { // B�϶� ������ ����
			if (max < width - stone[i].width) // ���� �̵��Ÿ��� �����̵��Ÿ����� ���� ��
				max = width - stone[i].width; // �ִ� �̵��Ÿ� ����
			width = stone[i].width; // �̵��Ÿ� ����
		}
		else if (stone[i].kind == 'S' && stone[i].check != true) { // S�϶� �ȹ��� ���
			if (max < width - stone[i].width) // ���� �̵��Ÿ��� �����̵��Ÿ����� ���� ��
				max = width - stone[i].width; // �ִ� �̵��Ÿ� ����
			width = stone[i].width; // �̵��Ÿ� ����
			stone[i].check = true; // ���� check
			if (stone[i - 1].kind == 'S') // ���� ���� ���� S�� ��� ��ĭ �ǳ� ��
				i--;
		}
	}
	if (width > max) // ������ ���� ����� �Ÿ��� �ִ� �Ÿ��� ��
		max = width;
	return max;
}

int frog(int N,/*���� ����*/ int D/*�ʺ�*/) {
	int foward = Foward(N, D);
	int reverse = Reverse(N, D);
	return foward > reverse ? foward : reverse; // ������� ������ �� ū ���� ����
}

int main() {
	ifstream inp("frog.inp");
	ofstream out("frog.out");
	int t; // �׽�Ʈ���̽�
	int N, D; // ���� ����, ���� �ʺ�
	char bar;
	inp >> t;
	for (int i = 1; i <= t; i++) {
		inp >> N >> D;
		stone.resize(N + 2); // stone �Ҵ�
		for(int j = 1; j <= N; j++)
			inp >> stone[j].kind >> bar >> stone[j].width;
		out << "Case " << i << ": " << frog(N,D) << endl;
		stone.clear(); // stone ��ȯ
	}
	inp.close(); out.close();
	return 0;
}