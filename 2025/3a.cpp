#include <iostream>

typedef long long int ll;

using namespace std;

int memo[105][105];

int solve(vector<int> &batteries, int x, int y) {
    if (x >= batteries.size() || y >= batteries.size() || x >= y) {
        return -100000;
    }

    if (memo[x][y] != -1) {
        return memo[x][y];
    }

    int ans = max(
        (10 * batteries[x]) + batteries[y],
        max(
            solve(batteries, x, y+1),
            solve(batteries, x+1, y)
        )
    );

    return memo[x][y] = ans;
}

int main() {
  string s;
  vector<vector<int> > banks;
  int ans = 0;
  while (cin >> s) {
    vector<int> batteries;
    for (int i = 0; i < s.size(); i++) {
        batteries.push_back(s[i]-'0');
    }

    memset(memo, -1, sizeof(memo));
    ans += solve(batteries, 0, 1);
  }

  cout << ans << endl;

  return 0;
}
