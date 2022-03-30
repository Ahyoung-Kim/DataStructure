#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

using uint = unsigned int;

/* 체이닝
* 
* 삽입: O(1)
* 룩업, 삭제: O(N)
* 
* 부하율(load factor): 해시 테이블에서 각각의 리스트에 저장되는 키의 평균 개수 = 전체 키 개수 / 해시 테이블 크기
* -> 1보다 작으면 메모리 낭비
* -> 1이면 가장 이상적인 상태 : 모든 연산이 O(1) 에 가깝게 작동, 메모리 공간 적절하게 활용
* -> 1보다 크면 검색, 삭제 연산이 느리게 동작할 수 있음
*/

class hash_map {
	vector<list<int>> data;

public:
	hash_map(size_t n) {
		data.resize(n); //해시 맵의 크기를 n으로 resize
	}

	void insert(uint value) {
		int n = data.size();

		/*
		* 해시함수 : 모듈로 함수
		* 해시 값 : value % n -> 연결리스트 -> 체이닝
		*/
		data[value % n].push_back(value);
		cout << value << "을 삽입했습니다." << endl;
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
			cout << value << "을 삭제했습니다." << endl;
		}
	}
};

int main() {
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