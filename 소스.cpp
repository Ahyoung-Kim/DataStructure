#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<algorithm>
#include<queue>
#include<stack>

using namespace std;

#define MAX 1001

typedef struct info {
    vector<int> report_idx;
    int reported = 0;
    int email = 0;
};

info infos[MAX];
bool visit[MAX][MAX];

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    int len = id_list.size();

    for (int i = 0; i < report.size(); i++) {
        string temp = report[i];
        int j;
        for (j = 0; j < temp.size(); j++) {
            if (temp[j] == ' ') {
                break;
            }
        }
        string src = temp.substr(0, j);
        string dest = temp.substr(j + 1);

        int src_idx, dest_idx;
        for (int k = 0; k < len; k++) {
            if (id_list[k] == src)
                src_idx = k;
            else if (id_list[k] == dest)
                dest_idx = k;
        }
        if (visit[src_idx][dest_idx])
            continue;

        visit[src_idx][dest_idx] = true;
        infos[src_idx].report_idx.push_back(dest_idx);
        infos[dest_idx].reported++;
    }

    for (int i = 0; i < len; i++) {
        if (infos[i].reported >= k) {
            for (int j = 0; j < len; j++) {
                for (int s = 0; s < infos[j].report_idx.size(); s++) {
                    if (infos[j].report_idx[s] == i) {
                        infos[j].email++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < len; i++) {
        answer.push_back(infos[i].email);
    }

    return answer;
}

int main(void) {

    vector<string> id_list;
    id_list.push_back("con");
    id_list.push_back("ryan");

    vector<string> report;
    report.push_back("ryan con");
    report.push_back("ryan con");
    report.push_back("ryan con");
    report.push_back("ryan con");


    vector<int> ans = solution(id_list, report, 2);

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }


	return 0;
}