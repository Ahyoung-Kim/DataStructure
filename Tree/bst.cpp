#include<iostream>

using namespace std;

typedef struct node {
	int data;
	node* left;
	node* right;
};

typedef struct bst {
	node* root = nullptr;

	node* find(int value) {
		return find_impl(root, value);
	}

	void insert(int value) {

		if (!root)
			root = new node{ value, NULL, NULL };
		else
			insert_impl(root, value);
	}

	void inorder() {
		inorder_impl(root);
	}

	node* successor(node* start) {
		auto current = start->right;

		while (current && current->left)
			current = current->left;

		return current;
	}

	void deleteValue(int value) {
		root = delete_impl(root, value); //트리 갱신 
	}

private: //외부에서 직접 호출할 수 없도록
	node* find_impl(node* current, int value) {
		if (!current) {
			cout << endl;
			return NULL;
		}

		if (current->data == value) {
			cout << value << "을(를) 찾았습니다." << endl;
			return current;
		}

		if (value < current->data) {
			cout << current->data << "에서 왼쪽으로 이동: ";
			return find_impl(current->left, value);
		}

		cout << current->data << "에서 오른쪽으로 이동: ";
		return find_impl(current->right, value);
	}

	void insert_impl(node* current, int value) {

		if (value < current->data) { //왼쪽 서브 트리에 추가 
			if (current->left == NULL) {
				current->left = new node{ value, NULL, NULL };
			}
			else {
				insert_impl(current->left, value);
			}
		}
		else {
			if (current->right == NULL)
				current->right = new node{ value, NULL, NULL };
			else
				insert_impl(current->right, value);
		}

	}

	void inorder_impl(node* current) {
		if (!current)
			return;

		inorder_impl(current->left);
		cout << current->data << ", ";
		inorder_impl(current->right);
	}

	node* delete_impl(node* current, int value) { //갱신 되어야 되는 노드 리턴 

		if (!current) //삭제할 노드 없을 때
			return NULL;

		if (value < current->data) { //왼쪽 서브 트리로 이동 
			current->left = delete_impl(current->left, value); //왼쪽 자식 노드 갱신
		}
		else if (value > current->data) { //오른쪽 서브 트리로 이동
			current->right = delete_impl(current->right, value); //오른쪽 자식 노드 갱신 
		}
		else { //삭제할 노드 찾음
			if (!current->left) { //삭제할 노드의 왼쪽 자식 없을 때 -> 오른쪽 자식 노드로 대체 
				auto tmp = current->right;
				delete current;
				return tmp; //삭제한 노드 오른쪽 자식 노드 포인터
			}

			if (!current->right) { //오른쪽 자식 노드 없을 때 -> 왼쪽 자식 노드로 대체 
				auto tmp = current->left;
				delete current;
				return tmp; //삭제한 노드 왼쪽 자식 노드 포인터 
			}

			//자식 노드 둘 다 있을 경우
			auto succNode = successor(current); //오른쪽 서브 트리에서 가장 작은 노드 
			current->data = succNode->data;

			//오른쪽 서브 트리에서 후속을 찾아 삭제
			current->right = delete_impl(current->right, succNode->data); //오른쪽 자식 노드 갱신 
		}

		return current;

	}
};

int main(void) {

	bst tree;

	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);

	cout << "inoder print: "; //오름차순
	tree.inorder();

	cout << endl << endl;

	tree.deleteValue(12);
	tree.inorder();

	return 0;
}
