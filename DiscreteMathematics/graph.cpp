#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<string.h>
#define MAX 10000
using namespace std;

struct Graph {
	int E; // ���� ����
	int weight; // ����ġ
};

vector< vector<Graph> > graph; // graph
bool check[MAX]; // �湮�޴��� üũ
stack<int> Stack; // ����
queue<int> Queue; // ť

bool compare(Graph &p1, Graph &p2) { //�������� ���� ���Լ�
	return p1.E < p2.E;
}

int DFS_Traversal(int V, int n) { // ���̿켱Ž��, Stack
	int result = 0;
	Stack.push(V); // �������� push
	check[V] = true; // �湮�� ���� true
	while (!Stack.empty()) { // stack�� ������ �� �� ����
		for (int i = 0; i < graph[V].size(); i++) { // ���������� ���� ������ �˻�
			if (check[graph[V][i].E] != true) { // ���� ������ �湮���� ���� ������ ��
				check[graph[V][i].E] = true; // �湮�� ���� true
				Stack.push(graph[V][i].E); // ������ push
				result += graph[V][i].weight; // ����ġ+
				V = graph[V][i].E; // ������ �ٲ�
				i = -1; // ó������ ���� ����
			}
		}
		Stack.pop(); // ���������� �� ������ �� pop
		if (!Stack.empty())
			V = Stack.top(); // �ٵ����� �� top�� ��������
	}
	memset(check, false, sizeof(bool) * n); // check�� �ʱ�ȭ
	return result;
}

int BFS_Traversal(int V, int n) { // �ʺ�켱Ž��, Queue
	int result = 0;
	Queue.push(V); // �������� push
	check[V] = true; // �湮�� ���� true
	while (!Queue.empty()) { // Queue�� ������ �� �� ����
		for (int i = 0; i < graph[V].size(); i++) { // ���������� ���� ������ �˻�
			if (check[graph[V][i].E] != true) { // ���� ������ �湮���� ���� ������ ��
				check[graph[V][i].E] = true; // �湮�� ���� true
				Queue.push(graph[V][i].E); // ������ push
				result += graph[V][i].weight; // ����ġ+
			}
		}
		Queue.pop(); // ���������� �� ������ �� pop
		if (!Queue.empty())
			V = Queue.front(); // �ٵ����� �� top�� ��������
	}
	memset(check, false, sizeof(bool) * n); // check�� �ʱ�ȭ
	return result;
}

int main() {
	ifstream inp("graph.inp");
	ofstream out("graph.out");

	int t; // ���׽�Ʈ���̽�
	int n, m; // ����, ������ ����
	int V; // ����
	int k, start; // ��ȸ�� ������ ��, ��������

	inp >> t;
	while (t--) {
		inp >> n >> m;
		graph.resize(n); // ������ �� ��ŭ �Ҵ�
		for (int i = 0; i < m; i++) {
			Graph input; // ����, ����ġ
			inp >> V >> input.E >> input.weight;
			graph[V].push_back(input); // ����
			swap(V, input.E); // V�� E�� swap
			graph[V].push_back(input); // ����
		}

		for (int i = 0; i < n; i++) // ������ ���̼����� ����
			sort(graph[i].begin(), graph[i].end(), compare);

		inp >> k; // ���������� ��
		while (k--) {
			inp >> start; // ��������
			out << "n=" << n << " m=" << m << " start=" << start
				<< " DFS:" << DFS_Traversal(start, n) << " BFS:" << BFS_Traversal(start, n)
				<< endl;
		}
		graph.clear(); // graph��ȯ
	}
	inp.close(); out.close();
	return 0;
}