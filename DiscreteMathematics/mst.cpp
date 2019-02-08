#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#define MAX 10000
using namespace std;

typedef struct Graph {
	int E; // ��������
	int weight; // ����ġ
}Graph;

vector< vector<Graph> > graph; // �׷��� ����
vector<Graph> result; // ����� ����
bool visit[MAX]; // �湮���� üũ

struct compare { // �ּ��� ��
	bool operator()(Graph &a, Graph &b) {
		return a.weight > b.weight;
	}
};

bool Sort_compare(Graph &a, Graph &b) { // ���� ��
	if (a.E == b.E) // �������� ���� ������ ����� ��
		return a.weight < b.weight;
	return a.E < b.E; // �������� �� ��
}

void Prim_Algorithm(int start) { // �����˰�����
	priority_queue< Graph, vector<Graph>, compare > heap; // �ּ��� ����
	visit[start] = true; // �������� true
	int All_cost = 0, V_count = 1;
	for (int i = 0; i < graph[start].size(); i++) { // ���������� ������ ����
		if (!visit[graph[start][i].E])// �湮���� ���� ������ ���Ͽ� push
			heap.push(graph[start][i]);
	}
	while (!heap.empty()) {
		Graph Min_node = heap.top(); heap.pop(); // ��� �������� �� �ּҺ���� ������ ���� pop
		int V = Min_node.E; int cost = Min_node.weight; // ���� ������ ����
		if (!visit[V]) { // �湮���� ���� ������ ���Ͽ�
			visit[V] = true; // �湮�� ���� true
			V_count++; // ������ ��++
			All_cost += cost; // ���++
			for (int i = 0; i < graph[V].size(); i++) {
				if (!visit[graph[V][i].E]) // �湮���� ���� ���������Ͽ� push
					heap.push(graph[V][i]);
			}
		}
	}
	result.push_back({ V_count, All_cost }); // ����� ����
}

int main() {
	ifstream inp("mst.inp");
	ofstream out("mst.out");
	int n, m; // ������ ��, ������ ��
	int V, E, weight; // ���� ����, ��������, ����ġ
	inp >> n >> m;
	graph.resize(n);
	while (m--) {
		inp >> V >> E >> weight;
		graph[V].push_back({ E, weight });
		graph[E].push_back({ V, weight });
	}
	for (int V = 0; V < n; V++) {
		if(!visit[V]) // �湮���� ������ ���Ͽ� 
			Prim_Algorithm(V);
	}
	sort(result.begin(), result.end(), Sort_compare); // ����
	for (int i = 0; i < result.size(); i++)
		out << result[i].E << ' ' << result[i].weight << '\n';
	inp.close(); out.close();
	return 0;
}