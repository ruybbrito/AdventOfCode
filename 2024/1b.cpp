#include <iostream>

using namespace std;

int count_occurrences(vector<int>& v, int target, int l, int r) {
  if (l >= r) return v[r] == target ? 1 : 0;
  else if (v[l] == target && v[r] == target) return r-l+1;
  else return count_occurrences(v, target, l, (l+r)/2) + count_occurrences(v, target, ((l+r)/2)+1, r);
}

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
  for (int i = 0; i < va.size(); i++) ans += va[i] * count_occurrences(vb, va[i], 0, vb.size() - 1);
  cout << ans << endl;
  return 0;
}
