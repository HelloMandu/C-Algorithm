#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

struct Process {
	int pid, arrivedTime, cpuSchedule, waitedTime = 0;
};

vector<Process> readyQueue, srtfQueue;
int front = 0;

/*readyQueue����*/
bool compare1(Process &a, Process &b) {
	if (a.arrivedTime == b.arrivedTime) {
		if (a.cpuSchedule == b.cpuSchedule) {
			return a.pid < b.pid;
		}
		return a.cpuSchedule < b.cpuSchedule;
	}
	return a.arrivedTime < b.arrivedTime;
}

/*srtfQueue����*/
bool compare2(Process &a, Process &b) {
	if (a.cpuSchedule == b.cpuSchedule) {
		if (a.arrivedTime == b.arrivedTime) {
			return a.pid < b.pid;
		}
		return a.arrivedTime < b.arrivedTime;
	}
	return a.cpuSchedule < b.cpuSchedule;
}

/*��� cpuSchedule�� �������� �˻�*/
bool isFisish() {
	int cpuSchedule = 0;
	for (int i = 0; i < srtfQueue.size(); i++) {
		cpuSchedule += srtfQueue[i].cpuSchedule;
	}
	if (cpuSchedule == 0 && readyQueue.empty()) {
		return true;
	}
	return false;
}

/*�� waitingTime���*/
int computeWaitingTime() {
	int waitingTime = 0;
	for (int i = 0; i < srtfQueue.size(); i++) {
		waitingTime += srtfQueue[i].waitedTime;
	}
	return waitingTime;
}

int getWaitingTime() {
	int allTime = 0;
	while (!isFisish()) {
		/*���ο� ���μ��� ���� : srtf, ���� : ready*/
		while (!readyQueue.empty() && readyQueue[0].arrivedTime == allTime) {
			srtfQueue.push_back(readyQueue[0]);
			readyQueue.erase(readyQueue.begin());
			sort(srtfQueue.begin(), srtfQueue.end(), compare2);
		}
		if (front < srtfQueue.size()) {
			for (int i = front + 1; i < srtfQueue.size(); i++) {
				srtfQueue[i].waitedTime++;
			}
			if (srtfQueue[front].cpuSchedule > 0) {
				srtfQueue[front].cpuSchedule--;
				/*cpu�����ٸ��� ������ ��� front++*/
				if (srtfQueue[front].cpuSchedule == 0) {
					front++;
					sort(srtfQueue.begin(), srtfQueue.end(), compare2);
				}
			}
		}
		allTime++;
	}
	return computeWaitingTime();
}

int main() {
	ifstream inp("srtf.inp");
	ofstream out("srtf.out");
	int n;
	inp >> n;
	readyQueue.reserve(n);
	for (int i = 0; i < n; i++) {
		Process input;
		inp >> input.pid >> input.arrivedTime >> input.cpuSchedule;
		readyQueue.push_back(input);
	}
	sort(readyQueue.begin(), readyQueue.end(), compare1);
	out << getWaitingTime();
	return 0;
}