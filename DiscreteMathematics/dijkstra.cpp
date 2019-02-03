#include<fstream>
#include<vector>
using namespace std;
#define infinity 1000000
ifstream inp("dijkstra.inp");
ofstream out("dijkstra.out");

typedef struct Graph {
	int E = 0; // ��������
	int weight = 0; // �׷����� ����ġ
	int edge_number = 0; // ��ΰ� ������ ����
}Graph;

typedef struct Dijkstra {
	bool check = false; // ����Ȯ������
	bool none = false; // �ִܰŸ��� �ѹ��� ���ŵ��� �ʾ��� ���
	int distance = 0; // �ִܰŸ�
	int last_index = 0; // ���ŵ� index
	int edge_number = 0; // ���ŵ� edge�� ����
}Dijkstra;

vector< vector<Graph> > graph;
Dijkstra dist[10000];

int Min_index(int n) { // �ּҰŸ��� ������ index�˻�
	int min = infinity;
	int index = -1; // ������ ���
	for (int i = 0; i < n; i++) { // ������ ���� ��ŭ �ݺ�
		if (dist[i].distance < min && dist[i].check != true && dist[i].none == true && dist[i].distance != 0) {
			// ������ ��κ��� �۰�, ���ŵ� ���� ���� ���, �ִܰŸ��� ������, �ѹ��̶� ������ �� ���
			min = dist[i].distance; // �ִܰŸ��� ����
			index = i; // �ִܰŸ��� ������ index
		}
	}
	return (index != -1 ? index : 0); // ��� ����� ������ ������ �� 0 ���
}

void dijkstra(int n) {
	int E; // ��������
	int index = 0; // ������ �׻� 0����
	dist[index].check = true; // �������� �� true������ ����
	dist[index].none = true; // �ѹ��� ���ŵ��� ���� ��� ����
	for (int i = 0; i < n - 1; i++) { // ���������� �������Ƿ� n-1����ŭ ����
		for (int t = 0; t < graph[index].size(); t++) {
			E = graph[index][t].E; // ���������� ����
			if (dist[E].check != true) { // ���� ���ŵ��� ���� index
				if (dist[E].none != true) {// �ִܰŸ��� ���� �ѹ��� ���� ���� �ʴ� ���
					dist[E].distance = dist[index].distance + graph[index][t].weight; // �ִܰŸ� ����
					dist[E].last_index = index; dist[E].none = true; // ���ŵ� ����, �ѹ��� ���ŵ��� ���� ��� ����
					dist[E].edge_number = graph[index][t].edge_number; // edge�� ���� ����
				}
				else if (dist[index].distance + graph[index][t].weight <= dist[E].distance) {
					// ���� �� ���������� �Ÿ� (dist[index].distance) + ���� w������ �Ÿ���
					// ������ w���������� �Ÿ����� �����ٸ� �� ������ �������ش�.
					if (dist[index].distance + graph[index][t].weight == dist[E].distance) { // �ִܰ�ΰ� ���� ��
						if (dist[E].edge_number < graph[index][t].edge_number) //���ο� ��ΰ� �ִ��κ��� ���� ��
							continue;
					}
					dist[E].distance = dist[index].distance + graph[index][t].weight; // �ִܰŸ� ����
					dist[E].last_index = index; // ���ŵǾ��� �� ������ index�� ����
					dist[E].edge_number = graph[index][t].edge_number;  // edge�� ����
				}
			}
		}
		index = Min_index(n); // �ּҰŸ��� ������ index�� ã�´�
		dist[index].check = true; // �ִܰŸ��� ã�� ���
	}
}

void dijkstra_path(int n) { // ���ͽ�Ʈ�� ��θ� ���
	if (dist[n].distance == 0) {// ������ �������� ���� ���� ��
		out << "V0" << ' ';
		return;
	}
	else
		dijkstra_path(dist[n].last_index); // ���ŵǰ� �� ������ ã�ư�
	out << "V" << n << ' ';
}

int main() {
	int n, m; // �����Ǽ�, ������ ��
	int V; // ��������
	inp >> n >> m; // ������ ��, ������ ��
	graph.resize(n);
	for (int edge_number = 0; edge_number < m; edge_number++) { // ������ �� ��ŭ �Է�
		Graph input;
		inp >> V >> input.E >> input.weight; // ����, ����, ����
		input.edge_number = edge_number;
		graph[V].push_back(input);
	}
	dijkstra(n);//���ͽ�Ʈ�� �˰���
	for (int i = 1; i < n; i++) { // ����������� ���
		dijkstra_path(i); // ��θ� ���
		if (dist[i].distance != 0)
			out << "(" << dist[i].distance << ")" << endl; // �Ÿ��� ���
		else
			out << "V" << i << ' ' << "(-1)" << endl;
	}
	graph.clear();
	inp.close(); out.close();
	return 0;
}

/*#include<fstream>
using namespace std;
#define infinity 1000000
ifstream inp("dijkstra.inp");
ofstream out("dijkstra.out");

typedef struct Dijkstra {
	bool check = false; // ����Ȯ������
	bool none = false; // �ִܰŸ��� �ѹ��� ���ŵ��� �ʾ��� ���
	int distance = 0; // �ִܰŸ�
	int last_index = 0; // ���ŵ� index
	int edge_number = 0; // ���ŵ� edge�� ����
}Dijkstra;

typedef struct Graph {
	int weight = infinity; // �׷����� ����ġ
	int edge_number = 0; // ��ΰ� ������ ����
}Graph;

Graph graph[10000][10000];
Dijkstra dist[10000];

int Min_index(int n) { // �ּҰŸ��� ������ index�˻�
	int min = infinity;
	int index = -1; // ������ ���
	for (int i = 0; i < n; i++) { // ������ ���� ��ŭ �ݺ�
		if (dist[i].distance < min && dist[i].check != true && dist[i].none == true && dist[i].distance != 0) {
			// ������ ��κ��� �۰�, ���ŵ� ���� ���� ���, �ִܰŸ��� ������, �ѹ��̶� ������ �� ���
			min = dist[i].distance; // �ִܰŸ��� ����
			index = i; // �ִܰŸ��� ������ index
		}
	}
	return (index != -1 ? index : 0); // ��� ����� ������ ������ �� -1 ���
}

void dijkstra(int n, int m) {
	int index = 0; // ������ �׻� 0����
	dist[index].check = true; // �������� �� true������ ����
	dist[index].none = true; // �ѹ��� ���ŵ��� ���� ��� ����
	for (int i = 0; i < n - 1; i++) { // ���������� �������Ƿ� n-1����ŭ ����
		for (int t = 0; t < n; t++) {
			if (dist[t].check != true) { // ���� ���ŵ��� ���� index
				if (dist[t].none != true && graph[index][t].weight != infinity) {// �ִܰŸ��� ���� �ѹ��� ���� ���� �ʴ� ���
					dist[t].distance = dist[index].distance + graph[index][t].weight; // �ִܰŸ� ����
					dist[t].last_index = index; dist[t].none = true; // ���ŵ� ����, �ѹ��� ���ŵ��� ���� ��� ����
					dist[t].edge_number = graph[index][t].edge_number; // edge�� ���� ����
				}
				else if (dist[index].distance + graph[index][t].weight <= dist[t].distance) {
					// ���� �� ���������� �Ÿ� (dist[index].distance) + ���� w������ �Ÿ���
					// ������ w���������� �Ÿ����� �����ٸ� �� ������ �������ش�.
					if (dist[index].distance + graph[index][t].weight == dist[t].distance) { // �ִܰ�ΰ� ���� ��
						if (dist[t].edge_number > graph[index][t].edge_number) //���ο� ��ΰ� �ִ��κ��� ���� ��
							continue;
					}
					dist[t].distance = dist[index].distance + graph[index][t].weight; // �ִܰŸ� ����
					dist[t].last_index = index; // ���ŵǾ��� �� ������ index�� ����
					dist[t].edge_number = graph[index][t].edge_number;  // edge�� ����
				}
			}
		}
		index = Min_index(n); // �ּҰŸ��� ������ index�� ã�´�
		dist[index].check = true; // �ִܰŸ��� ã�� ���
	}
}

void dijkstra_path(int n) { // ���ͽ�Ʈ�� ��θ� ���
	if (dist[n].distance == 0) {// ������ �������� ���� ���� ��
		out << "V0" << ' ';
		return;
	}
	else
		dijkstra_path(dist[n].last_index); // ���ŵǰ� �� ������ ã�ư�
	out << "V" << n << ' ';
}

int main() {
	int n, m; // �����Ǽ�, ������ ��
	int V, E, weight; // ���� ����, ���� ����, ����
	inp >> n >> m;
	for (int edge_number = 0; edge_number < m; edge_number++) { // ������ �� ��ŭ �Է�
		inp >> V >> E >> weight; // ����, ����, ����
		graph[V][E].weight = weight; // ���ͽ�Ʈ�� ����
		graph[V][E].edge_number = edge_number; // ����� ���� ����
	}
	dijkstra(n, m);//���ͽ�Ʈ�� �˰���
	for (int i = 1; i < n; i++) { // ����������� ���
		dijkstra_path(i); // ��θ� ���
		if (dist[i].distance != 0)
			out << "(" << dist[i].distance << ")" << endl; // �Ÿ��� ���
		else
			out << "V" << i << ' ' << "(-1)" << endl;
	}
	inp.close(); out.close();
	return 0;
}*/