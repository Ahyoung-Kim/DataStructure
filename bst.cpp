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
		root = delete_impl(root, value); //Ʈ�� ���� 
	}

private: //�ܺο��� ���� ȣ���� �� ������
	node* find_impl(node* current, int value) {
		if (!current) {
			cout << endl;
			return NULL;
		}

		if (current->data == value) {
			cout << value << "��(��) ã�ҽ��ϴ�." << endl;
			return current;
		}

		if (value < current->data) {
			cout << current->data << "���� �������� �̵�: ";
			return find_impl(current->left, value);
		}

		cout << current->data << "���� ���������� �̵�: ";
		return find_impl(current->right, value);
	}

	void insert_impl(node* current, int value) {

		if (value < current->data) { //���� ���� Ʈ���� �߰� 
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

	node* delete_impl(node* current, int value) { //���� �Ǿ�� �Ǵ� ��� ���� 

		if (!current) //������ ��� ���� ��
			return NULL;

		if (value < current->data) { //���� ���� Ʈ���� �̵� 
			current->left = delete_impl(current->left, value); //���� �ڽ� ��� ����
		}
		else if (value > current->data) { //������ ���� Ʈ���� �̵�
			current->right = delete_impl(current->right, value); //������ �ڽ� ��� ���� 
		}
		else { //������ ��� ã��
			if (!current->left) { //������ ����� ���� �ڽ� ���� �� -> ������ �ڽ� ���� ��ü 
				auto tmp = current->right;
				delete current;
				return tmp; //������ ��� ������ �ڽ� ��� ������
			}

			if (!current->right) { //������ �ڽ� ��� ���� �� -> ���� �ڽ� ���� ��ü 
				auto tmp = current->left;
				delete current;
				return tmp; //������ ��� ���� �ڽ� ��� ������ 
			}

			//�ڽ� ��� �� �� ���� ���
			auto succNode = successor(current); //������ ���� Ʈ������ ���� ���� ��� 
			current->data = succNode->data;

			//������ ���� Ʈ������ �ļ��� ã�� ����
			current->right = delete_impl(current->right, succNode->data); //������ �ڽ� ��� ���� 
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

	cout << "inoder print: "; //��������
	tree.inorder();

	cout << endl << endl;

	tree.deleteValue(12);
	tree.inorder();

	return 0;
}