#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

typedef struct node {
	string name;
	bool is_dir; //false: file, true: directory
	vector<node*> children;
};

typedef struct file_system {

	file_system() {
		root = new node{ "/", true, {} };
		cwd = root;
	};

	node* find(const string& path) {
		if (path[0] == '/') { //���� ���
			return find_impl(root, path.substr(1));
		}
		else { //�����
			return find_impl(cwd, path);
		}
	};

	//���丮 ����
	bool add(const string& path, bool is_dir) {
		if (path[0] == '/')
			return add_impl(root, path.substr(1), is_dir);
		else
			return add_impl(cwd, path, is_dir);
	};

	//���丮 �̵��ϴ� �Լ�
	bool change_dir(const string& path) {
		auto found = find(path);

		if (found && found->is_dir) {
			cwd = found;
			cout << "���� ���丮�� " << cwd->name << "�� �̵��մϴ�. " << endl;
			return true;
		}

		cout << path << " ��θ� ã�� �� �����ϴ�. " << endl;
		return false;
	};

	//���丮�� ���� ��� ���
	void show_path(const string& path) {
		auto found = find(path);

		if (not found) {
			cout << path << " ��ΰ� �������� �ʽ��ϴ�." << endl;
			return;
		}

		if (found->is_dir) {
			for (auto child : found->children) {
				cout << (child->is_dir ? "d " : "- ") << child->name << endl;
			}
		}
		else
			cout << "- " << found->name << endl;
	};

private:

	node* root;
	node* cwd;

	node* find_impl(node* dir, const string& path) {
		if (path.empty()) {
			return dir;
		}

		auto sep = path.find('/'); //'/'�� �����ϴ��� Ȯ��, �����ϸ� '/'�� index, �������� ������ npos 

		//sep�� '/'�� �������� ������ string::npos ����
		//sep�� npos�� curr_path�� path, �׷��� ������ path�� ó������ '/'����
		string curr_path = sep == string::npos ? path : path.substr(0, sep);

		//sep�� npos�� rest_path�� " "�̰� �׷��� �ʴٸ� '/'�������� ��
		string rest_path = sep == string::npos ? "" : path.substr(sep + 1);

		//children�߿��� curr_path�� ������ child ������ ����
		auto found = find_if(dir->children.begin(), dir->children.end(),
			[&](const node* child) {
				return child->name == curr_path;
			});

		if (found != dir->children.end())
			return find_impl(*found, rest_path);

		return NULL;
	};

	bool add_impl(node* dir, const string& path, bool is_dir) {

		if (not dir->is_dir) { //����
			cout << dir->name << " ��(��) �����Դϴ�. " << endl;
			return false;
		}

		auto sep = path.find('/');

		if (sep == string::npos) { //��ο� '/' ���� ��

			//path�� ������ ��θ� ���� �ڽ��� �ִ��� Ž��
			auto found = find_if(dir->children.begin(), dir->children.end(),
				[&](const node* child) {
					return child->name == path;
				});

			//�̹� ���� ��
			if (found != dir->children.end()) {
				cout << dir->name << "�� �̹� " << path << " �̸��� ����/���丮�� �ֽ��ϴ�." << endl;
				return false;
			}

			//�ڽ� ��忡 ���丮 ��� �߰� 
			dir->children.push_back(new node{ path, is_dir, {} });
			return true;
		}

		//���丮 ���� ��

		string next_dir = path.substr(0, sep);
		//���� ���丮 ������ found
		auto found = find_if(dir->children.begin(), dir->children.end(),
			[&](const node* child) {
				return child->name == next_dir && child->is_dir;
			});

		if (found != dir->children.end()) {
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		cout << dir->name << "�� " << next_dir << " �̸��� ���丮�� �����ϴ�. " << endl;
		return false;
	};
};


int main(void) {

	file_system fs;

	fs.add("usr", true);
	fs.add("etc", true);
	fs.add("var", true);
	fs.add("tmp_file", false);

	cout << "\"/\"�� ����/���丮 ���: " << endl;
	fs.show_path("/");

	cout << endl;
	fs.change_dir("usr");
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	cout << "���� ���丮���� usr�� ����/���丮 ���: " << endl;
	fs.show_path("usr");

	cout << "\"/usr\"�� ����/���丮 ���: " << endl;
	fs.show_path("/usr");

	cout << "\"/usr/gilbut/Downloads\"�� ����/���丮 ���: " << endl;
	fs.show_path("/usr/gilbut/Downloads");

	return 0;
}
