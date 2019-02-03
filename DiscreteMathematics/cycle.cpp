#include<fstream>
#include<vector>
#include<queue>
#include<string.h>
#define MAX 1000000
using namespace std;

int state[MAX]; // 0: �湮���� 1: Ȧ�� 2: ¦��

bool OddCycle(vector< vector<int> > &graph) {
	queue<int> Queue; // Queue����
	int V = 0; // ������ 0
	Queue.push(V); // �������� push
	state[V] = 2; // ���¸� ����
	int level = 1; // level�� ¦������ Ȧ������ ����
	int prepush = 1, pushcount = 0, popcount = 0; // ���� push���� ����, push�� Ƚ���� ����, pop�� Ƚ���� ����
	while (!Queue.empty()) {
		for (int i = 0; i < graph[V].size(); i++) {
			if (state[V] == state[graph[V][i]]) // ���°� ���� ���
				return true; // Ȧ�� ����Ŭ�̹Ƿ� true��ȯ
			else if (state[graph[V][i]] == 0) { // �ѹ��� �湮���� ���� ������ ��
				state[graph[V][i]] = level; // ���¸� ����
				Queue.push(graph[V][i]); // �湮�� ������ push
				pushcount++; // push�� ���� ����
			}
		}
		Queue.pop(); // ���������� �� ������ �� pop
		popcount++; // pop�� Ƚ���� ����
		if (!Queue.empty())
			V = Queue.front(); // �ٵ����� �� top�� ��������
		if (prepush == popcount) { // pushȽ���� popȽ���� ��ĥ �� level++
			level = (level == 1) ? 2 : 1;
			prepush = pushcount;
			pushcount = 0; popcount = 0;
		}
	}
	return false; // Ȧ�� ����Ŭ�� �ƴѰ��
}

int main() {
	ifstream inp("cycle.inp");
	ofstream out("cycle.out");
	int t; // �� �׽�Ʈ���̽�
	int n, m; // ������ ��, ������ ��
	int V, E; // ���� ����, ��������
	vector< vector<int> > graph; // �׷�������
	inp >> t;
	while (t--) {
		inp >> n >> m;
		graph.resize(n); // ������ ����ŭ �����Ҵ�
		for (int i = 0; i < m; i++) {
			inp >> V >> E;
			graph[V].push_back(E); // ��������
			graph[E].push_back(V); // ��������
		}
		if (OddCycle(graph))
			out << "O\n";
		else
			out << "X\n";
		memset(state, 0, sizeof(int) * n); // check�� �ʱ�ȭ
		graph.clear();
	}
	return 0;
}