#include<iostream>
#include<queue>
#include<vector>

using namespace std;

//�߾Ӱ� ���ϱ� 
//�Ź� �����͸� ���� ������ ���ݱ��� ���� �������� �߾Ӱ�

/*
* �� �����Ͱ� ���� �������� �߾Ӱ����� ������ �ִ� ���� ����,
* ũ�� �ּ� ���� ����
* -> �� ���� �ֻ�� ���Ҹ� �̿��Ͽ� �߾Ӱ� ��� ����
*/

/* �� -> priority queue
* �ִ���: ��� ���� �ڽ� ��庸�� ū ��
* �ּ���: ��� ���� �ڽ� ��庸�� ���� ��
*/

typedef struct median {
	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;

	double get() { //�߾Ӱ� ��ȯ �Լ� 
		if (maxHeap.size() == minHeap.size()) {
			return (maxHeap.top() + minHeap.top()) / 2.0;
		}

		if (maxHeap.size() < minHeap.size()) {
			return minHeap.top();
		}

		return maxHeap.top();
	}

	void insert(int data) {
		if (maxHeap.size() == 0) {
			maxHeap.push(data);
			return;
		}

		if (maxHeap.size() == minHeap.size()) {
			if (data <= get()) { //�߾Ӱ����� ������ �ִ� ���� push
				maxHeap.push(data);
			}
			else {
				minHeap.push(data); //�߾Ӱ����� ũ�� �ּ� ���� push
			}
			return;
		}

		if (maxHeap.size() < minHeap.size()) {
			if (data > get()) {
				maxHeap.push(minHeap.top());
				minHeap.pop();
				minHeap.push(data);
			}
			else
				maxHeap.push(data);
			return;
		}

		if (data < get()) {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
			maxHeap.push(data);
		}
		else
			minHeap.push(data);
	}
};

int main(void) {
	
	median med;
	int temp;

	temp = 1;
	med.insert(temp);
	cout << temp << " ���� �� �߾Ӱ�: " << med.get() << endl; //1

	temp = 5;
	med.insert(temp);
	cout << temp << " ���� �� �߾Ӱ�: " << med.get() << endl; //3

	temp = 2;
	med.insert(temp);
	cout << temp << " ���� �� �߾Ӱ�: " << med.get() << endl; //2

	temp = 10;
	med.insert(temp);
	cout << temp << " ���� �� �߾Ӱ�: " << med.get() << endl; //3.5

	temp = 40;
	med.insert(temp);
	cout << temp << " ���� �� �߾Ӱ�: " << med.get() << endl; //5

	return 0;
}