#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

class Graph {
public:
	int E;
	int weight;
};

class Traversal {
private:
	enum { MAX = 10000 };
	bool check[MAX];
public:
	vector< vector<Graph> > graph;
	void createGraph(const int n);
	void setGraph(const int V, const int E, const int weight);
	int DFS_Traversal(int V, int n);
	int BFS_Traversal(int V, int n);
	void Print_Travarsal(ofstream &out, int n, int m, int start);
};

bool compare(const Graph &p1, const Graph &p2) { //�������� ���� ���Լ�
	return p1.E < p2.E;
}

void Traversal::createGraph(const int n) {
	graph.resize(n);
}

void Traversal::setGraph(const int V, const int E, const int weight) {
	graph[V].push_back({ E, weight }); // ����
	graph[E].push_back({ V, weight }); // ����
}

int Traversal::DFS_Traversal(int V, int n) { // ���̿켱Ž��, Stack
	stack<int> Stack; // ����
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

int Traversal::BFS_Traversal(int V, int n) { // �ʺ�켱Ž��, Queue
	queue<int> Queue; // ť
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

void Traversal::Print_Travarsal(ofstream &out, int n, int m, int start) {
	out << "n=" << n << " m=" << m << " start=" << start
		<< " DFS:" << DFS_Traversal(start, n) << " BFS:" << BFS_Traversal(start, n)
		<< '\n';
}

int main() {
	ifstream inp("graph.inp");
	ofstream out("graph.out");
	int t; // ���׽�Ʈ���̽�
	int n, m; // ����, ������ ����
	int V, E, weight; // ����, ����, ����ġ
	int k, start; // ��ȸ�� ������ ��, ��������
	inp >> t;
	Traversal traversal; // ��ȸ class����
	while (t--) {
		inp >> n >> m;
		traversal.createGraph(n); // ������ �� ��ŭ �Ҵ�
		for (int i = 0; i < m; i++) {
			inp >> V >> E >> weight;
			traversal.setGraph(V, E, weight);
		}
		for (int i = 0; i < n; i++) // ������ ���̼����� ����
			sort(traversal.graph[i].begin(), traversal.graph[i].end(), compare);
		inp >> k; // ���������� ��
		while (k--) {
			inp >> start; // ��������
			traversal.Print_Travarsal(out, n, m, start); // ��ȸ��� ���
		}
		traversal.graph.clear(); // graph��ȯ
	}
	inp.close(); out.close();
	return 0;
}