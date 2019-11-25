#include<fstream>
#include<vector>
#define FindRoot(form, n) form > 0 ? n - 1 : 0  //��Ʈ�� ����ִ��� ã��
#define Lsize(root, begin) root - begin // ���� �ڽ��� ������ ����
#define Rsize(root, finish) finish - root // ������ �ڽ��� ������ ����
using namespace std;

ifstream inp("tree2.inp");
ofstream out("tree2.out");

vector<int> pre, ino, post;

void INPUT(vector<int> &arr, int n) { // �Է¹���
	int key;
	arr.resize(n); // n�����ŭ �Ҵ�
	for (int i = 0; i < n; i++) {
		inp >> key;
		arr[i] = key;
	}
}

int Find_inorder_root(vector<int> &arr, int root_index, int begin, int finish) { // ���� ��ȸ���� ��Ʈ�� index���� ��ȯ
	for (int i = begin; i <= finish; i++) { // ���� ��ȸ�� ��Ʈ�ε����� ã��
		if (ino[i] == arr[root_index])
			return i;
	}
	return root_index;
}

void Find_Postorder(int pre_root_index, int begin, int finish) { // postorder�� ã��
	int ino_root_index = Find_inorder_root(pre, pre_root_index, begin, finish); // ���� ��ȸ�� ��Ʈ�ε����� ã��
	if (begin < finish) {
		int L_size = Lsize(ino_root_index, begin), R_size = Rsize(ino_root_index, finish); // ���ʻ������ �����ʻ�����
		int L_child = pre_root_index + 1, R_child = pre_root_index + L_size + 1; // �����ڽİ� �������ڽ�
		if (L_size > 0) // �����ڽ��� ������
			Find_Postorder(L_child, begin, ino_root_index - 1); // L��ġ�� ��Ʈ��
		if (R_size > 0) // �������ڽ��� ������
			Find_Postorder(R_child, ino_root_index + 1, finish); // R��ġ�� ��Ʈ��
	}
	out << ino[ino_root_index] << '\n';
}

void Find_Preorder(int post_root_index, int begin, int finish) { // preorder�� ã��
	int ino_root_index = Find_inorder_root(post, post_root_index, begin, finish); // ���� ��ȸ�� ��Ʈ�ε����� ã��
	out << ino[ino_root_index] << '\n';
	if (begin < finish) {
		int L_size = Lsize(ino_root_index, begin), R_size = Rsize(ino_root_index, finish); // ���ʻ������ �����ʻ�����
		int L_child = post_root_index - R_size - 1, R_child = post_root_index - 1; // �����ڽİ� �������ڽ�
		if (L_size > 0) // �����ڽ��� ������
			Find_Preorder(L_child, begin, ino_root_index - 1); // L��ġ�� ��Ʈ��
		if (R_size > 0) // �������ڽ��� ������
			Find_Preorder(R_child, ino_root_index + 1, finish); // R��ġ�� ��Ʈ��
	}
}

int main() {
	int n, type; // ������ ��, ��ȸ type - pre : -1, in : 0, post : 1
	int form = 0, two = 2; // �Ÿ���� ���Ӵ��� ������ ����
	inp >> n;
	while (two--) { // �ΰ��� ��ȸ����� ����
		inp >> type;
		form += type;
		switch (type) {
		case -1: //�����Է�
			INPUT(pre, n);
			break;
		case 0: // �����Է�
			INPUT(ino, n);
			break;
		case 1: // �����Է�
			INPUT(post, n);
			break;
		}
	}
	int root = FindRoot(form, n); // ��Ʈ��ã��
	if (form > 0)
		Find_Preorder(root, 0, n - 1);
	else
		Find_Postorder(root, 0, n - 1);
	inp.close(); out.close();
	return 0;
}