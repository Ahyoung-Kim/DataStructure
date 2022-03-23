#include<iostream>
#include<queue>
#include<vector>

using namespace std;

//중앙값 구하기 
//매번 데이터를 받을 때마다 지금까지 받은 데이터의 중앙값

/*
* 새 데이터가 기존 데이터의 중앙값보다 작으면 최대 힙에 저장,
* 크면 최소 힙에 저장
* -> 두 힙의 최상단 원소를 이용하여 중앙값 계산 가능
*/

/* 힙 -> priority queue
* 최대힙: 모든 노드는 자식 노드보다 큰 값
* 최소힙: 모든 노드는 자식 노드보다 작은 값
*/

typedef struct median {
	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;

	double get() { //중앙값 반환 함수 
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
			if (data <= get()) { //중앙값보다 작으면 최대 힙에 push
				maxHeap.push(data);
			}
			else {
				minHeap.push(data); //중앙값보다 크면 최소 힙에 push
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
	cout << temp << " 삽입 후 중앙값: " << med.get() << endl; //1

	temp = 5;
	med.insert(temp);
	cout << temp << " 삽입 후 중앙값: " << med.get() << endl; //3

	temp = 2;
	med.insert(temp);
	cout << temp << " 삽입 후 중앙값: " << med.get() << endl; //2

	temp = 10;
	med.insert(temp);
	cout << temp << " 삽입 후 중앙값: " << med.get() << endl; //3.5

	temp = 40;
	med.insert(temp);
	cout << temp << " 삽입 후 중앙값: " << med.get() << endl; //5

	return 0;
}