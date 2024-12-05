#include <iostream>

using namespace std;

int main() {
  vector<string> s;
  string a;
  while (cin >> a) {
    s.push_back(a);
  }
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < s[i].size(); j++) {
      if (s[i][j] == 'A') {
        if (j < s[i].size() - 1 && j >= 1 && i >= 1 && i < s.size() - 1) {
          if (s[i - 1][j - 1] == 'M' && s[i + 1][j + 1] == 'S' && s[i - 1][j + 1] == 'M' && s[i + 1][j - 1] == 'S') {
            ans++;
          } else if (s[i - 1][j - 1] == 'S' && s[i + 1][j + 1] == 'M' && s[i - 1][j + 1] == 'S' && s[i + 1][j - 1] == 'M') {
            ans++;
          } else if (s[i - 1][j - 1] == 'M' && s[i + 1][j + 1] == 'S' && s[i - 1][j + 1] == 'S' && s[i + 1][j - 1] == 'M') {
            ans++;
          } else if (s[i - 1][j - 1] == 'S' && s[i + 1][j + 1] == 'M' && s[i - 1][j + 1] == 'M' && s[i + 1][j - 1] == 'S') {
            ans++;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
