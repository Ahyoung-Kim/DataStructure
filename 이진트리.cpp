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

		if (root == NULL) //Ž�� ���� 
			return NULL;

		if (root->position == value) //root���� �ٷ� ã���� ��
			return root;

		auto firstFound = org_tree::find(root->first, value); //���� �ڽ� ���� Ž�� 

		if (firstFound != NULL) //������ 
			return firstFound;

		return org_tree::find(root->second, value); //������ �ڽ� ���� Ž�� 
	}

	bool addSubordinate(const string& manager, const string& subordinate) {

		auto managerNode = org_tree::find(root, manager);

		if (!managerNode) {
			cout << manager << "��(��) ã�� �� �����ϴ�. " << endl;
			return false;
		}

		if (managerNode->first && managerNode->second) { //�̹� �ڽ� ��� �� á�� ��
			cout << manager << " �Ʒ���" << subordinate << "��(��) �߰��� �� �����ϴ�. " << endl;
			return false;
		}

		if (!managerNode->first) {
			managerNode->first = new node{ subordinate, NULL, NULL }; //���� �ڽĳ�� �߰�
		}
		else {
			managerNode->second = new node{ subordinate, NULL, NULL }; //������ �ڽĳ�� �߰� 
		}

		cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��߽��ϴ�." << endl;
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

			//���� q�� size�� �� level�� ����ִ� ���� ��
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

	tree.addSubordinate("CEO", "�λ���");
	tree.addSubordinate("�λ���", "IT����");
	tree.addSubordinate("�λ���", "�����ú���");
	tree.addSubordinate("IT����", "��������");
	tree.addSubordinate("IT����", "�۰�������");
	tree.addSubordinate("�����ú���", "��������");
	tree.addSubordinate("�����ú���", "ȫ������");
	tree.addSubordinate("�λ���", "�繫����");

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
