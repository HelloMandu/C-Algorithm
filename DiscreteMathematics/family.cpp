#include<fstream>
#include<string.h>
#define MAX 500000
using namespace std;

typedef struct Pedigree{
	int distance; // �Ÿ��� ����
	bool check; // ���ۿ���
}Pedigree;

int graph[MAX];
Pedigree pedigree[MAX]; // �������� ����

int family(int n) {
	int max = 0; // ��ȯ�� �����
	int distance = 0; // ����� �ִ�
	for (int child = 1; child <= n; child++) { // n���� ������ ������������ 
		pedigree[child].check = true; // ������ ���� true
		int parent = graph[child]; // �θ��� ���� ����
		while (parent != 0) { // ��Ʈ�� ������ �� ���� �ݺ�
			if (pedigree[parent].check == true) { // ������ �θ��� ������ �Ÿ��� ������ ���� ��
				distance += pedigree[parent].distance + 1; // �θ������� ��Ʈ���� �Ÿ��� ����
				break;
			}
			parent = graph[parent]; // �θ� -> �ڽ�
			distance++; // �Ÿ� + 1;
		}
		max = max > distance ? max : distance; // �Ÿ��� �ִ� ����
		pedigree[child].distance = distance; // parent�������κ����� �Ÿ�
		distance = 0; // �Ÿ��� 0���� �ʱ�ȭ
	}
	memset(graph, 0, sizeof(int) * (n + 1));
	memset(pedigree, 0, sizeof(Pedigree) * (n + 1));
	return max + 1; // ������ ����
}

int main() {
	ifstream inp("family.inp");
	ofstream out("family.out");
	int t; // �� ����� ��
	int n; // ������ ��
	int V, E; // ���� ����, ���� ����
	inp >> t;
	while (t--) {
		inp >> n;
		for (int i = 0; i < n - 1; i++) {
			inp >> V >> E;
			graph[E] = V; // index = ��������, V = ��������
		}
		out << family(n) << endl;
	}
	return 0;
}