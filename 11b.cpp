#include <iostream>
#include <set>
#include <map>

using namespace std;

long long int mem[1000000][76];

long long int solve(long long int n, int cur) {
  if (cur == 0) return 1;
  else if (n < 1000000 && mem[n][cur] != -1) return mem[n][cur];

  long long int ans = -1;
  
  if (!n) ans = solve(1, cur-1);
  else {
    string s = to_string(n);
    if (s.size() % 2 == 0) {
      ans = solve(stoll(s.substr(0, s.size() / 2)), cur-1) + solve(stoll(s.substr(s.size() / 2, s.size() / 2)), cur-1);
    } else {
      ans = solve(2024*n, cur-1);
    }
  }
  
  if (n < 1000000) mem[n][cur] = ans;
  return ans;
}

int main() {
  vector<long long int> v;
  long long int a;
  while (cin >> a) {
    v.push_back(a);
  }

  for (int i =0; i < 1000001; i++) {
    for (int j = 0; j < 76; j++) {
      mem[i][j] = -1;
    }
  }

  long long int ans = 0;
  for (int i = 0; i < v.size(); i++) ans += solve(v[i], 75);
  cout << ans << endl;

  return 0;
}
