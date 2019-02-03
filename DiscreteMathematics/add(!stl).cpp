#include<iostream>
#include<fstream>
#pragma warning(disable : 4996)
using namespace std;
typedef long long lint;
#define MAX_ELEMENT 100000

typedef struct { // ������ ���� 1���� �迭�� ���� ������ ������ ����ü�� ��� ����
	lint heap[MAX_ELEMENT];
	lint heap_size;
} heapType;

heapType* createHeap() // ���� ������ �����ϴ� ����
{
	heapType *h = (heapType *)malloc(sizeof(heapType));
	h->heap_size = 0;
	return h;
}

void insertHeap(heapType *h, lint item) // ������item�� �����ϴ� ����
{
	lint i;
	h->heap_size = h->heap_size + 1;
	i = h->heap_size;
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
lint deleteHeap(heapType *h) // ������ ��Ʈ�� �����Ͽ� ��ȯ�ϴ� ����
{
	lint parent, child;
	lint item, temp;
	item = h->heap[1];
	temp = h->heap[h->heap_size];
	h->heap_size = h->heap_size - 1;
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child]) > h->heap[child + 1])
			child++;
		if (temp <= h->heap[child]) break;
		else {
			h->heap[parent] = h->heap[child];
			parent = child;
			child = child * 2;
		}
	}
	h->heap[parent] = temp;
	return item;
}

lint add(heapType *h) {
	lint cost = 0; // ��� ��

	while (true) {
		lint num1 = deleteHeap(h);
		lint num2 = deleteHeap(h); // ���� ���� �� 2���� �̴´�

		cost += num1 + num2; // ����� ����

		if (h->heap_size != 0) // ������� ���� ��
			insertHeap(h, num1 + num2); // �� �� ���� ���� �ִ´�
		else // ����� ��
			return cost;
	}

}

int main()
{
	ifstream inp("add.inp");
	ofstream out("add.out");
	int n, num;
	heapType *heap = createHeap();
	while (true) {
		inp >> n;
		if (!n) break;
		for (int i = 0; i < n; i++) {
			inp >> num;
			insertHeap(heap, num); // ����
		}
		out << add(heap) << "\n";
	}
	return 0;
}