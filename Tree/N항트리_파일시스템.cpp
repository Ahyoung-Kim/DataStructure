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
		if (path[0] == '/') { //절대 경로
			return find_impl(root, path.substr(1));
		}
		else { //상대경로
			return find_impl(cwd, path);
		}
	};

	//디렉토리 생성
	bool add(const string& path, bool is_dir) {
		if (path[0] == '/')
			return add_impl(root, path.substr(1), is_dir);
		else
			return add_impl(cwd, path, is_dir);
	};

	//디렉토리 이동하는 함수
	bool change_dir(const string& path) {
		auto found = find(path);

		if (found && found->is_dir) {
			cwd = found;
			cout << "현재 디렉토리를 " << cwd->name << "로 이동합니다. " << endl;
			return true;
		}

		cout << path << " 경로를 찾을 수 없습니다. " << endl;
		return false;
	};

	//디렉토리와 파일 목록 출력
	void show_path(const string& path) {
		auto found = find(path);

		if (not found) {
			cout << path << " 경로가 존재하지 않습니다." << endl;
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

		auto sep = path.find('/'); //'/'가 존재하는지 확인, 존재하면 '/'의 index, 존재하지 않으면 npos 

		//sep에 '/'가 존재하지 않으면 string::npos 리턴
		//sep이 npos면 curr_path는 path, 그렇지 않으면 path의 처음부터 '/'까지
		string curr_path = sep == string::npos ? path : path.substr(0, sep);

		//sep이 npos면 rest_path는 " "이고 그렇지 않다면 '/'다음부터 쭉
		string rest_path = sep == string::npos ? "" : path.substr(sep + 1);

		//children중에서 curr_path와 동일한 child 있으면 리턴
		auto found = find_if(dir->children.begin(), dir->children.end(),
			[&](const node* child) {
				return child->name == curr_path;
			});

		if (found != dir->children.end())
			return find_impl(*found, rest_path);

		return NULL;
	};

	bool add_impl(node* dir, const string& path, bool is_dir) {

		if (not dir->is_dir) { //파일
			cout << dir->name << " 은(는) 파일입니다. " << endl;
			return false;
		}

		auto sep = path.find('/');

		if (sep == string::npos) { //경로에 '/' 없을 때

			//path와 동일한 경로를 가진 자식이 있는지 탐색
			auto found = find_if(dir->children.begin(), dir->children.end(),
				[&](const node* child) {
					return child->name == path;
				});

			//이미 있을 때
			if (found != dir->children.end()) {
				cout << dir->name << "에 이미 " << path << " 이름의 파일/디렉토리가 있습니다." << endl;
				return false;
			}

			//자식 노드에 디렉토리 경로 추가 
			dir->children.push_back(new node{ path, is_dir, {} });
			return true;
		}

		//디렉토리 있을 때

		string next_dir = path.substr(0, sep);
		//하위 디렉토리 포인터 found
		auto found = find_if(dir->children.begin(), dir->children.end(),
			[&](const node* child) {
				return child->name == next_dir && child->is_dir;
			});

		if (found != dir->children.end()) {
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		cout << dir->name << "에 " << next_dir << " 이름의 디렉토리가 없습니다. " << endl;
		return false;
	};
};


int main(void) {

	file_system fs;

	fs.add("usr", true);
	fs.add("etc", true);
	fs.add("var", true);
	fs.add("tmp_file", false);

	cout << "\"/\"의 파일/디렉토리 목록: " << endl;
	fs.show_path("/");

	cout << endl;
	fs.change_dir("usr");
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	cout << "현재 디렉토리에서 usr의 파일/디렉토리 목록: " << endl;
	fs.show_path("usr");

	cout << "\"/usr\"의 파일/디렉토리 목록: " << endl;
	fs.show_path("/usr");

	cout << "\"/usr/gilbut/Downloads\"의 파일/디렉토리 목록: " << endl;
	fs.show_path("/usr/gilbut/Downloads");

	return 0;
}
