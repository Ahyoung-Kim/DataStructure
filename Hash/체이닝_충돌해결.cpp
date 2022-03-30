#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

using uint = unsigned int;

/* ü�̴�
* 
* ����: O(1)
* ���, ����: O(N)
* 
* ������(load factor): �ؽ� ���̺��� ������ ����Ʈ�� ����Ǵ� Ű�� ��� ���� = ��ü Ű ���� / �ؽ� ���̺� ũ��
* -> 1���� ������ �޸� ����
* -> 1�̸� ���� �̻����� ���� : ��� ������ O(1) �� ������ �۵�, �޸� ���� �����ϰ� Ȱ��
* -> 1���� ũ�� �˻�, ���� ������ ������ ������ �� ����
*/

class hash_map {
	vector<list<int>> data;

public:
	hash_map(size_t n) {
		data.resize(n); //�ؽ� ���� ũ�⸦ n���� resize
	}

	void insert(uint value) {
		int n = data.size();

		/*
		* �ؽ��Լ� : ���� �Լ�
		* �ؽ� �� : value % n -> ���Ḯ��Ʈ -> ü�̴�
		*/
		data[value % n].push_back(value);
		cout << value << "�� �����߽��ϴ�." << endl;
	}

	bool find(uint value) { //lookup
		int n = data.size();

		auto& entries = data[value % n];
		return (std::find(entries.begin(), entries.end(), value) != entries.end());
	}

	void erase(uint value) {
		int n = data.size();

		auto& entries = data[value % n];
		auto iter = std::find(entries.begin(), entries.end(), value);

		if (iter != entries.end()) {
			entries.erase(iter);
			cout << value << "�� �����߽��ϴ�." << endl;
		}
	}
};

int main() {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value)) {
			cout << "�ؽ� �ʿ��� " << value << "�� ã�ҽ��ϴ�.";
		}
		else {
			cout << "�ؽ� �ʿ��� " << value << "�� ã�� ���߽��ϴ�.";
		}
		cout << endl;
	};


	map.insert(2);
	map.insert(25);
	map.insert(10);

	map.insert(100);
	map.insert(55);

	print(100);
	print(2);

	map.erase(2);

	return 0;
}