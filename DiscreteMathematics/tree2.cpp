#include<fstream>
#include<vector>
#include<stack>
#include<string.h>
#define root 0
using namespace std;

typedef struct Tree {
	int child; // �ڽ�����
	int weight; // ����ġ
}Tree;

vector< vector<Tree> > tree;
bool check[100000]; // �湮����üũ
int root_length; // ��Ʈ�κ����� �ִ밪
int result; // �����

int MAX_length(int V, int n) { // �ش��������κ��� �ִ�Ÿ�
	stack<int> Stack;
	stack<int> weight;
	int result = 0;
	int sum = 0;
	Stack.push(V); // �������� push
	while (!Stack.empty()) { // stack�� ������ �� �� ����
		for (int i = 0;  i < tree[V].size(); i++) { // ���������� ���� ������ �˻�
			if (!check[tree[V][i].child]) {
				check[tree[V][i].child] = true;
				Stack.push(tree[V][i].child); // ������ push
				sum += tree[V][i].weight;
				weight.push(tree[V][i].weight);
				V = tree[V][i].child; // ������ �ٲ�
				i = -1;
			}
		}
		if (sum > result)
			result = sum;
		Stack.pop(); // ���������� �� ������ �� pop
		if (!Stack.empty()) {
			V = Stack.top(); // �ٵ����� �� top�� ��������
			sum -= weight.top();
			weight.pop();
		}
	}
	memset(check, false, sizeof(bool) * n);
	return result;
}


void tree_update(int V, int length, int n) {
	if (tree[V].size() != 0) { // ������尡 �ƴҶ�
		for (int i = 0; i < tree[V].size(); i++) {
			int max_length = length + tree[V][i].weight + MAX_length(tree[V][i].child , n);
			tree[V][i].weight += root_length - max_length; // �� ������ �ִ� ���̿� �� �ִ������ ���̸�ŭ ������
			result += root_length - max_length; // �ű⼭ �߻��� ����� ������
			tree_update(tree[V][i].child, length + tree[V][i].weight, n); // child�� �ڽ� ��� ��ȸ
		}
	}
}

int main() {
	ifstream inp("tree.inp");
	ofstream out("tree.out");
	int t, n;
	int parent, weight;
	inp >> t;
	while (t--) {
		inp >> n;
		tree.resize(n);
		for (int i = 1; i < n; i++) {
			inp >> parent >> weight;
			tree[parent].push_back({ i, weight });
		}
		root_length = MAX_length(root, n);
		tree_update(root, 0, n);
		out << result << '\n';
		result = 0; tree.clear();
	}
	inp.close();
	out.close();
	return 0;
}