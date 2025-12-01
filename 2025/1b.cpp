#include <iostream>

using namespace std;

int safe_mod(int n, int k) {
  return ((n % k) + k) % k;
}

int main() {
  string s;
  int n = 50;
  int ans = 0;
  while (cin >> s) {
    int dir = s[0] == 'L' ? 0 : 1;
    s = s.substr(1, s.size()-1);
    int k = stoi(s);
    int t = dir ? n+k : n-k;
    n = dir ? safe_mod(n+k, 100) : safe_mod(n-k, 100);
    if (k >= 100) {
        ans += k/100;
    } else if (t >= 100 || t <= 0) {
        ans++;
    }
  }
  cout << ans << endl;
  return 0;
}
