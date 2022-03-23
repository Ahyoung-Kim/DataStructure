#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
* �ټ��� ���ĵ� �迭�� ���ļ� �ϳ��� ���ĵ� �迭�� ����� ���α׷�
* 
* 1. ������ ����Ʈ�� �̹� ���ĵǾ� �ֱ� ������ �� ����Ʈ�� �ּ� ���Ҵ� �� �տ� ��ġ -> �ּ� �� ���
* 2. ������ �ּ� ���Ҹ� ������ �� �����ϰ�, �ּ� ���Ұ� �ִ� ����Ʈ���� �� �������� ���� ���� �����Ͽ� ���� �߰�
* 3. ���� ���� �� ���Ҹ� ��� ����Ʈ���� �����Դ���, ���� �ش� ����Ʈ���� �� ��° ���������� �����ؾ� ��
*/

typedef struct node {
	int data;
	int listPosition; //��� ����Ʈ���� �����Դ���
	int dataPosition; //�ش� ����Ʈ���� �� ��° �������� 
};

vector<int> merge(const vector<vector<int>>& input) {
	auto comparator = [](const node& left, const node& right) {
		if (left.data == right.data) 
			return left.listPosition > right.listPosition; 
		return left.data > right.data;
	}; //����, �ּ� ������

	vector<node> heap;
	for (int i = 0; i < input.size(); i++) {
		heap.push_back({ input[i][0], i, 0 }); //�� ����Ʈ���� ���� ���� ���Ҹ� �����Ͽ� �ּ� �� ����

		//vector<node> heap �����̳ʸ� �ּ������� ����
		push_heap(heap.begin(), heap.end(), comparator);
	}

	vector<int> result;
	while (!heap.empty()) {
		//heap�� ��Ʈ pop
		pop_heap(heap.begin(), heap.end(), comparator);
		auto min = heap.back(); //��Ʈ ���� �ּ� ���(��Ʈ)
		heap.pop_back();

		result.push_back(min.data);
		int nextIndex = min.dataPosition + 1;

		if (nextIndex < input[min.listPosition].size()) { //�ش� ����Ʈ�� ���Ұ� ����������
			heap.push_back({ input[min.listPosition][nextIndex], min.listPosition, nextIndex }); //���� ���� ���� push 
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