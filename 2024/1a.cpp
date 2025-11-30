#include <iostream>

using namespace std;

int main() {
  int a, b;
  vector<int> va, vb;
  while (cin >> a >> b) {
    va.push_back(a);
    vb.push_back(b);
  }
  sort(va.begin(), va.end());
  sort(vb.begin(), vb.end());
  long long int ans = 0;
  for (int i = 0; i < va.size(); i++) ans += abs(va[i] - vb[i]);
  cout << ans << endl;
  return 0;
}
