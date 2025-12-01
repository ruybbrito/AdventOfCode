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
    if (dir) { // R
        if (k >= 100-n) ans++;
        ans += abs((k-100+n)/100);
    } else { // L
        if (n && k >= n) ans++;
        ans += abs((k-n)/100);
    }
    n = safe_mod(t, 100);
  }
  cout << ans << endl;
  return 0;
}
