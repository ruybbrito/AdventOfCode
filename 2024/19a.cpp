#include <iostream>
#include <map>

using namespace std;

int memo[200];

int solve(vector<string> &designs, string pattern, int idx) {
  if (idx == pattern.size()) return memo[idx] = 1;

  if (memo[idx] != -1) {
    return memo[idx];
  }

  int ans = 0;
  for (int i = 0; i < designs.size(); i++) {
    int len = designs[i].size();
    if (idx + len <= pattern.size() && designs[i] == pattern.substr(idx, len)) {
      ans = max(ans, solve(designs, pattern, idx + designs[i].size()));
    }
  }

  return memo[idx] = ans;
}

int main() {
  vector<string> designs, patterns;
  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    else if (s.find(",") != string::npos) {
      while (s.find(",") != string::npos) {
        int pos = s.find(",");
        designs.push_back(s.substr(0, pos));
        s.erase(0, pos+2);
      }
      designs.push_back(s.substr(0, s.size()));
    } else {
      patterns.push_back(s);
    }
  }

  int ans = 0;
  for (int i = 0; i < patterns.size(); i++) {
    memset(memo, -1, sizeof(memo));
    ans += solve(designs, patterns[i], 0);
  }
  cout << ans << endl;

  return 0;
}
