#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<string>

using namespace std;

typedef struct node {
	string position;
	node* first;
	node* second;
};

typedef struct org_tree {
	node* root;

	static org_tree create_org_structure(const string& pos) {

		org_tree tree;
		tree.root = new node{ pos, NULL, NULL };
		return tree;
	}

	static node* find(node* root, const string& value) {

		if (root == NULL) //탐색 실패 
			return NULL;

		if (root->position == value) //root에서 바로 찾았을 때
			return root;

		auto firstFound = org_tree::find(root->first, value); //왼쪽 자식 노드로 탐색 

		if (firstFound != NULL) //없으면 
			return firstFound;

		return org_tree::find(root->second, value); //오른쪽 자식 노드로 탐색 
	}

	bool addSubordinate(const string& manager, const string& subordinate) {

		auto managerNode = org_tree::find(root, manager);

		if (!managerNode) {
			cout << manager << "을(를) 찾을 수 없습니다. " << endl;
			return false;
		}

		if (managerNode->first && managerNode->second) { //이미 자식 노드 꽉 찼을 때
			cout << manager << " 아래에" << subordinate << "을(를) 추가할 수 없습니다. " << endl;
			return false;
		}

		if (!managerNode->first) {
			managerNode->first = new node{ subordinate, NULL, NULL }; //왼쪽 자식노드 추가
		}
		else {
			managerNode->second = new node{ subordinate, NULL, NULL }; //오른쪽 자식노드 추가 
		}

		cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다." << endl;
		return true;
	}

	static void preOrder(node* start) {
		if (!start)
			return;

		cout << start->position << ", ";
		preOrder(start->first);
		preOrder(start->second);
	}

	static void inOrder(node* start) {
		if (!start)
			return;

		inOrder(start->first);
		cout << start->position << ", ";
		inOrder(start->second);
	}

	static void postOrder(node* start) {
		if (!start)
			return;

		postOrder(start->first);
		postOrder(start->second);
		cout << start->position << ", ";
	}

	static void levelOrder(node* start) {

		if (!start)
			return;

		queue<node*> q;
		q.push(start);

		while (!q.empty()) {
			int size = q.size();

			//현재 q의 size는 한 level에 들어있는 원소 수
			for (int i = 0; i < size; i++) {
				auto current = q.front();
				q.pop();

				cout << current->position << ", ";

				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);
			}

			cout << endl;
		}
	}
};


int main(void) {

	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "부사장");
	tree.addSubordinate("부사장", "IT부장");
	tree.addSubordinate("부사장", "마케팅부장");
	tree.addSubordinate("IT부장", "보안팀장");
	tree.addSubordinate("IT부장", "앱개발팀장");
	tree.addSubordinate("마케팅부장", "물류팀장");
	tree.addSubordinate("마케팅부장", "홍보팀장");
	tree.addSubordinate("부사장", "재무부장");

	cout << endl;
	tree.preOrder(tree.root);
	cout << endl;
	tree.inOrder(tree.root);
	cout << endl;
	tree.postOrder(tree.root);
	cout << endl;
	tree.levelOrder(tree.root);

	return 0;
}
