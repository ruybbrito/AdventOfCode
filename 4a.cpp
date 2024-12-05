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
      if (j < s[i].size() - 3) {
        if (s[i][j] == 'X' && s[i][j + 1] == 'M' && s[i][j + 2] == 'A' && s[i][j + 3] == 'S') {
          ans++;
        }
      }
      if (j >= 3) {
        if (s[i][j] == 'X' && s[i][j - 1] == 'M' && s[i][j - 2] == 'A' && s[i][j - 3] == 'S') {
          ans++;
        }
      }
      if (i < s.size() - 3) {
        if (s[i][j] == 'X' && s[i + 1][j] == 'M' && s[i + 2][j] == 'A' && s[i + 3][j] == 'S') {
          ans++;
        }
      }
      if (i >= 3) {
        if (s[i][j] == 'X' && s[i - 1][j] == 'M' && s[i - 2][j] == 'A' && s[i - 3][j] == 'S') {
          ans++;
        }
      }
      if (j < s[i].size() - 3 && i < s.size() - 3) {
        if (s[i][j] == 'X' && s[i + 1][j + 1] == 'M' && s[i + 2][j + 2] == 'A' && s[i + 3][j + 3] == 'S') {
          ans++;
        }
      }
      if (j >= 3 && i >= 3) {
        if (s[i][j] == 'X' && s[i - 1][j - 1] == 'M' && s[i - 2][j - 2] == 'A' && s[i - 3][j - 3] == 'S') {
          ans++;
        }
      }
      if (j < s[i].size() - 3 && i >= 3) {
        if (s[i][j] == 'X' && s[i - 1][j + 1] == 'M' && s[i - 2][j + 2] == 'A' && s[i - 3][j + 3] == 'S') {
          ans++;
        }
      }
      if (j >= 3 && i < s.size() - 3) {
        if (s[i][j] == 'X' && s[i + 1][j - 1] == 'M' && s[i + 2][j - 2] == 'A' && s[i + 3][j - 3] == 'S') {
          ans++;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
