#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

enum class city : int
{
	MOSCOW,
	LONDON,
	SEOUL,
	SEATTLE,
	DUBAI,
	SYDNEY
};

ostream& operator<<(ostream& os, const city c) {
	switch (c) {
	case city::LONDON:
		os << "����";
		return os;
	case city::MOSCOW:
		os << "��ũ��";
		return os;
	case city::SEOUL:
		os << "����";
		return os;
	case city::SEATTLE:
		os << "�þ�Ʋ";
		return os;
	case city::DUBAI:
		os << "�ι���";
		return os;
	case city::SYDNEY:
		os << "�õ��";
		return os;
	default:
		return os;
	}
}

struct graph_matrix {
	vector<vector<int>> data;

	graph_matrix(int n) { //nxn ��� �����
		data.reserve(n);
		vector<int> row(n);
		fill(row.begin(), row.end(), -1); //-1�� ä��� 

		for (int i = 0; i < n; i++) {
			data.push_back(row);
		}
	}

	void addEdge(const city c1, const city c2, int dis) {
		cout << "���� �߰�: " << c1 << "-" << c2 << "=" << dis << endl;

		auto n1 = static_cast<int>(c1); //int������ ��ȯ
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = dis;
		data[n2][n1] = dis;
	}

	void removeEdge(const city c1, const city c2) {
		cout << "���� ����: " << c1 << "-" << c2 << endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = -1;
		data[n2][n1] = -1;
	}
};

struct graph_list {
	vector < vector<pair<int, int>>> data;

	graph_list(int n){
		data = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
	}

	void addEdge(const city c1, const city c2, int dis) {
		cout << "���� �߰�: " << c1 << "-" << c2 << "=" << dis << endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1].push_back({ n2, dis });
		data[n2].push_back({ n1, dis });
	}

	void removeEdge(const city c1, const city c2) {
		cout << "���� ����: " << c1 << "-" << c2 << endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);

		remove_if(data[n1].begin(), data[n1].end(), [n2](const auto& pair) {
			return pair.first == n2;
			});
		remove_if(data[n2].begin(), data[n2].end(), [n1](const auto& pair) {
			return pair.first == n1;
			});
	}
};

int main(void) {

	graph_matrix gM(6);
	graph_list gL(6);

	gM.addEdge(city::LONDON, city::MOSCOW, 2500);
	gM.addEdge(city::LONDON, city::SEOUL, 9000);
	gM.addEdge(city::LONDON, city::DUBAI, 5500);
	gM.addEdge(city::SEOUL, city::MOSCOW, 6600);
	gM.addEdge(city::SEOUL, city::SEATTLE, 8000);
	gM.addEdge(city::SEOUL, city::DUBAI, 7000);
	gM.addEdge(city::SEOUL, city::SYDNEY, 8000);
	gM.addEdge(city::SEATTLE, city::MOSCOW, 8400);
	gM.addEdge(city::SEATTLE, city::SYDNEY, 1200);
	gM.addEdge(city::DUBAI, city::SYDNEY, 1200);

	gL.addEdge(city::LONDON, city::MOSCOW, 2500);
	gL.addEdge(city::LONDON, city::SEOUL, 9000);
	gL.addEdge(city::LONDON, city::DUBAI, 5500);
	gL.addEdge(city::SEOUL, city::MOSCOW, 6600);
	gL.addEdge(city::SEOUL, city::SEATTLE, 8000);
	gL.addEdge(city::SEOUL, city::DUBAI, 7000);
	gL.addEdge(city::SEOUL, city::SYDNEY, 8000);
	gL.addEdge(city::SEATTLE, city::MOSCOW, 8400);
	gL.addEdge(city::SEATTLE, city::SYDNEY, 1200);
	gL.addEdge(city::DUBAI, city::SYDNEY, 1200);

	return 0;
}