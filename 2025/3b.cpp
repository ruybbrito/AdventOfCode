#include <iostream>

typedef long long int ll;

using namespace std;

ll memo[105][15];

ll pow_n(int n) {
    ll ans = 1;
    while (n--) ans *= 10;
    return ans;
}

ll solve(vector<int> &batteries, int x, int num) {
    if (num == 0) {
        return 0;
    }

    if (x >= batteries.size()) {
        return -100000000000000;
    }

    if (memo[x][num] != -1) {
        return memo[x][num];
    }
    
    return memo[x][num] = max(
        (batteries[x] * pow_n(num-1)) + solve(batteries, x+1, num-1),
        solve(batteries, x+1, num)
    );
}

int main() {
  string s;
  vector<vector<int> > banks;
  ll ans = 0;
  while (cin >> s) {
    vector<int> batteries;
    for (int i = 0; i < s.size(); i++) {
        batteries.push_back(s[i]-'0');
    }

    memset(memo, -1LL, sizeof(memo));
    ll ret = solve(batteries, 0, 12);
    ans += ret;
  }

  cout << ans << endl;

  return 0;
}
