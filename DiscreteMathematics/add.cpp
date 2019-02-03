#include<iostream>
#include<fstream>
#include <queue>
#pragma warning(disable : 4996)
using namespace std;
typedef long long lint;

lint add (priority_queue< lint, vector<lint>, greater<lint> > *heap) {
	lint cost = 0; // ��� ��
	while (true) {
		lint num1 = heap->top(); heap->pop();
		lint num2 = heap->top(); heap->pop(); // ���� ���� �� 2���� �̴´�
		cost += num1 + num2; // ����� ����
		if (!heap->empty()) // ������� ���� ��
			heap->push(num1 + num2); // �� �� ���� ���� �ִ´�
		else // ����� ��
			return cost;
	}
}

int main() {
	ifstream inp("add.inp");
	ofstream out("add.out");
	int n, num;
	priority_queue< lint, vector<lint>, greater<lint> > heap; // �ּ���
	while (true) {
		inp >> n;
		if (!n) break;
		for (int i = 0; i < n; i++) {
			inp >> num;
			heap.push(num); // ����
		}
		out << add(&heap) << "\n";
	}
	return 0;
}