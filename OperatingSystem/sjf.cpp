#include<fstream>
#include<algorithm>
#include<queue>
using namespace std;

struct Process {
	int num, arrivedTime, cpuSchedule;
};

/*readyQueue ��*/
struct compare1{
	bool operator()(Process &a, Process &b) {
		if (a.arrivedTime == b.arrivedTime) {
			if (a.cpuSchedule == b.cpuSchedule) {
				return a.num > b.num;
			}
			return a.cpuSchedule > b.cpuSchedule;
		}
		return a.arrivedTime > b.arrivedTime;
	}
};

/*sjfQueue ��*/
struct compare2 {
	bool operator()(Process &a, Process &b) {
		if (a.cpuSchedule == b.cpuSchedule) {
			if (a.arrivedTime == b.arrivedTime) {
				return a.num > b.num;
			}
			return a.arrivedTime > b.arrivedTime;
		}
		return a.cpuSchedule > b.cpuSchedule;
	}
};

priority_queue<Process, vector<Process>, compare1> readyQueue; // ��ü ť
priority_queue<Process, vector<Process>, compare2> sjfQueue; // schedule �켱 ť

void pushProcess(int allTime) {
	while (!readyQueue.empty() && allTime >= readyQueue.top().arrivedTime) {
		sjfQueue.push(readyQueue.top()); readyQueue.pop();
	}
}

int getWaitingTime() {
	int waitingTime = 0, allTime = 0;
	while (!readyQueue.empty() || !sjfQueue.empty()) {
		Process front;
		/*scheduleť�� ���� ��*/
		if (!sjfQueue.empty()) {
			front = sjfQueue.top(); sjfQueue.pop();
			waitingTime += allTime - front.arrivedTime;
			allTime += front.cpuSchedule;
		}
		/*scehduleť�� ���� ��*/
		else {
			front = readyQueue.top(); readyQueue.pop();
			allTime = front.arrivedTime + front.cpuSchedule;
		}
		pushProcess(allTime);
	}
	return waitingTime;
}

int main() {
	ifstream inp("sjf.inp");
	ofstream out("sjf.out");
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		Process input;
		inp >> input.num >> input.arrivedTime >> input.cpuSchedule;
		readyQueue.push(input);
	}
	out << getWaitingTime();
	return 0;
}