#include <iostream>
#include <set>
#include <map>

using namespace std;

long long int P_INT_MAX = 1000000000000000;
// long long int OFFSET = 10000000000000;

int main() {
  string s;
  pair<long long int, long long int> a, b, p;
  long long int ans = 0;

  while (getline(cin, s)) {
    if (s == "") {
      continue;
    } else if (s.substr(0, 8) == "Button A") {
      s.erase(0, 12);
      int pos = s.find(", Y+");
      a.first = stoll(s.substr(0, pos));
      s.erase(0, pos + 4);
      a.second = stoll(s);
    } else if (s.substr(0, 8) == "Button B") {
      s.erase(0, 12);
      int pos = s.find(", Y+");
      b.first = stoll(s.substr(0, pos));
      s.erase(0, pos + 4);
      b.second = stoll(s);
    } else if (s.substr(0, 5) == "Prize") {
      s.erase(0, 9);
      int pos = s.find(", Y=");
      p.first = stoll(s.substr(0, pos));
      s.erase(0, pos + 4);
      p.second = stoll(s);

      long long int sol = P_INT_MAX;
      for (long long int x = 0; x <= 201; x++) {
        if (x * a.first > p.first || x * a.second > p.second) {
          break;
        }

        pair<long long int, long long int> g = make_pair(p.first - x * a.first, p.second - x * a.second);
        if (g.first % b.first == 0 && g.second % b.second == 0 && g.first * b.second == g.second * b.first) {
          int y = g.first / b.first;
          sol = min(sol, x * 3 + y);
        }
      }

      ans += (sol == P_INT_MAX ? 0 : sol);
    }

    s = "";
  }

  cout << ans << endl;

  return 0;
}
