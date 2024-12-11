#include <iostream>
#include <set>
#include <map>

using namespace std;

long long int solve(long long int n, int cur) {
  if (cur == 0) return 1;

  if (!n) return solve(1, cur-1);
  else if (n < 10) return solve(2024 * n, cur-1);
  else if (n < 100) return solve(n/10, cur-1) + solve(n%10, cur-1);
  else if (n < 1000) return solve(2024 * n, cur-1);
  else if (n < 10000) return solve(n/100, cur-1) + solve(n%100, cur-1);
  else if (n < 100000) return solve(2024 * n, cur-1);
  else if (n < 1000000) return solve(n/1000, cur-1) + solve(n%1000, cur-1);
  else if (n < 10000000) return solve(2024 * n, cur-1);
  else if (n < 100000000) return solve(n/10000, cur-1) + solve(n%10000, cur-1);
  else if (n < 1000000000) return solve(2024 * n, cur-1);
  else if (n < 10000000000) return solve(n/100000, cur-1) + solve(n%100000, cur-1);
  else if (n < 100000000000) return solve(2024 * n, cur-1);
  else if (n < 1000000000000) return solve(n/1000000, cur-1) + solve(n%1000000, cur-1);
  else if (n < 10000000000000) return solve(2024 * n, cur-1);
  else if (n < 100000000000000) return solve(n/10000000, cur-1) + solve(n%10000000, cur-1);
  else {
    cout << "ERROR" << endl;
    return 0;
  }
}

int main() {
  vector<long long int> v;
  long long int a, ans = 0;
  while (cin >> a) {
    v.push_back(a);
    ans += solve(a, 75);
  }

  cout << ans << endl;

  return 0;
}
