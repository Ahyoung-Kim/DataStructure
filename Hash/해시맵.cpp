#include<iostream>
#include<vector>

using namespace std;

using uint = unsigned int;

class hash_map {
	vector<int> data;

public:
	hash_map(size_t n) { //������, n�� -1�� �ʱ�ȭ
		data = vector<int>(n, -1);
	}

	void insert(uint value) { //���� �Լ�
		int n = data.size();

		/* �ؽ� �Լ� : ���� �Լ� 
		* key = value % n : �ؽ� ��
		* value = value
		*/
		data[value % n] = value;
		cout << value << "�� �����߽��ϴ�. " << endl;
	}

	bool find(uint value) { //��� �Լ�
		int n = data.size();

		return (data[value % n] == value);
	}

	void erase(uint value) { //���� �Լ�
		int n = data.size();

		if (data[value % n] == value) {
			data[value % n] = -1; //����
			cout << value << "�� �����߽��ϴ�." << endl;
		}
	}
};

int main(void) {
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

	map.insert(2); //key=2
	map.insert(25); //key=4
	map.insert(10); //key=3
	map.insert(25); //key=4
	print(25);

	map.insert(100); //key=2 -> �浹!(collision)
	print(100);
	print(2); //100���� ������

	map.erase(25);

	return 0;
}