#include <iostream>

typedef long long int ll;

using namespace std;

vector<int> rearrange(vector<string> &s) {
    vector<int> ret;
    for (int j = s[0].size()-1; j >= 0; j--) {
        string cur = "";
        for (int i = 0; i < s.size(); i++) {
            cur.push_back(s[i][j]);
        }
        ret.push_back(stoi(cur));
    }
    return ret;
}

int main() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    vector<int> gaps;
    int l = 0;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] != ' ') {
            gaps.push_back(i - l - 1);
            l = i;
        }
    }
    gaps.push_back(line.size() - l);

    vector<vector<string> > mat;
    for (int i = 0; i < lines.size(); i++) {
        vector<string> v;
        line = lines[i];
        int cur = 0;
        for (int j = 0; j < gaps.size(); j++) {
            v.push_back(line.substr(cur, gaps[j]));
            cur += gaps[j] + 1;
        }
        mat.push_back(v);
    }

    vector<char> op;
    for (int i = 0; i < mat[0].size(); i++) {
        op.push_back(mat[mat.size()-1][i][0]);
    }

    vector<vector<int> > mat2;
    for (int j = 0; j < mat[0].size(); j++) {
        vector<string> v;
        for (int i = 0; i < mat.size()-1; i++) {
            v.push_back(mat[i][j]);
        }
        mat2.push_back(rearrange(v));
    }

    vector<vector<int> > add, mult;

    for (int i = 0; i < mat2.size(); i++) {
        vector<int> cur = mat2[i];
        if (op[i] == '+') add.push_back(cur);
        else mult.push_back(cur);
    }

    ll ans = 0;

    for (int i = 0; i < add.size(); i++) {
        ll cur = add[i][0];
        for (int j = 1; j < add[i].size(); j++) cur += add[i][j];
        ans += cur;
    }

    for (int i = 0; i < mult.size(); i++) {
        ll cur = mult[i][0];
        for (int j = 1; j < mult[i].size(); j++) cur *= mult[i][j];
        ans += cur;
    }

    cout << ans << endl;

    return 0;
}


