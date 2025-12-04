#include <iostream>

typedef long long int ll;

using namespace std;

int solve(const vector<string> &m, int i, int j) {
    int cnt = 0;
    if (i > 0) {
        if (m[i-1][j] == '@') cnt++;
    }
    if (i + 1 < m.size()) {
        if (m[i+1][j] == '@') cnt++;
    }
    if (j + 1 < m[i].size()) {
        if (m[i][j+1] == '@') cnt++;
    }
    if (j > 0) {
        if (m[i][j-1] == '@') cnt++;
    }
    if (i > 0 && j > 0) {
        if (m[i-1][j-1] == '@') cnt++;
    }
    if (i > 0 && j + 1 < m[i].size()) {
        if (m[i-1][j+1] == '@') cnt++;
    }
    if (i + 1 < m.size() && j + 1 < m[i].size()) {
        if (m[i+1][j+1] == '@') cnt++;
    }
    if (i + 1 < m.size() && j > 0) {
        if (m[i+1][j-1] == '@') cnt++;
    }
    return cnt < 4 ? 1 : 0;
}

int main() {
  string s;
  vector<string> m;
  while (cin >> s) {
    m.push_back(s);
  }

  int ans = 0;
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
        if (m[i][j] == '@') {
            ans += solve(m, i, j);
        }
    }
  }

  cout << ans << endl;

  return 0;
}
