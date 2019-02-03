#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> V; // ���������� ����
vector<int> E; // ���������� ����

int BSearch(int len, int target) {
	int first = 0;
	int last = len - 1;
	int mid = 0;
	while (first <= last) {
		mid = (first + last) / 2;
		if (E[mid] == target) // Ÿ���� ã�� ���
			return mid;
		else {
			if (E[mid] > target) // mid�� Ÿ�ٺ��� ū���
				last = mid - 1;
			else // mid�� Ÿ�ٺ��� ���� ���
				first = mid + 1;
		}
	}
	return -1;
}

int tree() {
	int root = -1; // root�� -1�� �ʱ�ȭ
	sort(V.begin(), V.end()); // V����
	sort(E.begin(), E.end()); // E ����
	for (int i = 1; i < V.size(); i++) { // i - 1�� �����ؾ��ϹǷ� i = 1;
		if (V[i] != V[i - 1]) { // ���� index�� �ٸ� ���� �� root Ž��
			if (!binary_search(E.begin(), E.end(), V[i - 1])) { // ã�� ���� ���� �� root���ǿ� ����
				if (root != -1)// root�� �ΰ��� ���
					return -1;
				else // root�� ���� �� ����
					root = V[i - 1];
			}
		}
		if (E[i] == E[i - 1]) // �ڽ��� ����Ű�� ������ �ΰ� �̻��� ��
			return -1;
	}
	if (!binary_search(E.begin(), E.end(), V[V.size() - 1])) { // ã�� ���� ���� �� root���ǿ� ����
		if (root != -1)// root�� �ΰ��� ���
			return -1;
		else // root�� ���� �� ����
			root = V[V.size() - 1];
	}
	return root;
}

int main() {
	ifstream inp("tree.inp");
	ofstream out("tree.out");
	int v, e; // ��������, ��������
	int TreeNum = 0; // tree�� ��ȣ
	while (true) {
		inp >> v >> e;
		if (v == -1 && e == -1) // v, e�� -1�� �� ���α׷� ����
			break;
		else if (v == 0 && e == 0) {//  v, e�� 0�� �� Ʈ�� �Է� ��
			out << "Test Case " << ++TreeNum << ": " << tree() << "\n";
			V.clear(); E.clear(); // V�� E�� ��ȯ
		}
		else { // ���������� ���������� ����
			V.push_back(v); E.push_back(e);
		}
	}
	return 0;
}