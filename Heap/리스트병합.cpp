#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
* 다수의 정렬된 배열을 합쳐서 하나의 정렬된 배열을 만드는 프로그램
* 
* 1. 각각의 리스트는 이미 정렬되어 있기 때문에 각 리스트의 최소 원소는 맨 앞에 위치 -> 최소 힙 사용
* 2. 힙에서 최소 원소를 가져온 후 제거하고, 최소 원소가 있던 리스트에서 그 다음으로 작은 원소 선택하여 힙에 추가
* 3. 힙의 노드는 이 원소를 어느 리스트에서 가져왔는지, 또한 해당 리스트에서 몇 번째 원소인지를 저장해야 함
*/

typedef struct node {
	int data;
	int listPosition; //어느 리스트에서 가져왔는지
	int dataPosition; //해당 리스트에서 몇 번째 원소인지 
};

vector<int> merge(const vector<vector<int>>& input) {
	auto comparator = [](const node& left, const node& right) {
		if (left.data == right.data) 
			return left.listPosition > right.listPosition; 
		return left.data > right.data;
	}; //정렬, 최소 힙으로

	vector<node> heap;
	for (int i = 0; i < input.size(); i++) {
		heap.push_back({ input[i][0], i, 0 }); //각 리스트에서 가장 작은 원소를 추출하여 최소 힙 구성

		//vector<node> heap 컨테이너를 최소힙으로 구성
		push_heap(heap.begin(), heap.end(), comparator);
	}

	vector<int> result;
	while (!heap.empty()) {
		//heap의 루트 pop
		pop_heap(heap.begin(), heap.end(), comparator);
		auto min = heap.back(); //루트 힙의 최소 노드(루트)
		heap.pop_back();

		result.push_back(min.data);
		int nextIndex = min.dataPosition + 1;

		if (nextIndex < input[min.listPosition].size()) { //해당 리스트에 원소가 남아있으면
			heap.push_back({ input[min.listPosition][nextIndex], min.listPosition, nextIndex }); //힙에 남은 원소 push 
			push_heap(heap.begin(), heap.end(), comparator);
		}
	}

	return result;
}

int main(void) {

	vector<int> v1 = { 1, 3, 8, 15, 105 };
	vector<int> v2 = { 2, 3, 10, 11, 16, 20, 25 };
	vector<int> v3 = { -2, 100, 1000 };
	vector<int> v4 = { -1, 0, 14, 18 };

	auto result = merge({ v1, v2, v3, v4 });

	for (auto i : result) {
		cout << i << " ";
	}

	return 0;
}