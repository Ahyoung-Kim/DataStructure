#include<iostream>
#include<vector>

using namespace std;

using uint = unsigned int;

class hash_map {
	vector<int> data;

public:
	hash_map(size_t n) { //생성자, n개 -1로 초기화
		data = vector<int>(n, -1);
	}

	void insert(uint value) { //삽입 함수
		int n = data.size();

		/* 해시 함수 : 모듈로 함수 
		* key = value % n : 해시 값
		* value = value
		*/
		data[value % n] = value;
		cout << value << "을 삽입했습니다. " << endl;
	}

	bool find(uint value) { //룩업 함수
		int n = data.size();

		return (data[value % n] == value);
	}

	void erase(uint value) { //삭제 함수
		int n = data.size();

		if (data[value % n] == value) {
			data[value % n] = -1; //삭제
			cout << value << "을 삭제했습니다." << endl;
		}
	}
};

int main(void) {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value)) {
			cout << "해시 맵에서 " << value << "을 찾았습니다.";
		}
		else {
			cout << "해시 맵에서 " << value << "을 찾지 못했습니다.";
		}
		cout << endl;
	};

	map.insert(2); //key=2
	map.insert(25); //key=4
	map.insert(10); //key=3
	map.insert(25); //key=4
	print(25);

	map.insert(100); //key=2 -> 충돌!(collision)
	print(100);
	print(2); //100으로 덮어짐

	map.erase(25);

	return 0;
}