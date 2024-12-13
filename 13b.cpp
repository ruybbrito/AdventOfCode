#include <iostream>
#include <set>
#include <map>

using namespace std;

long long int P_INT_MAX = 1000000000000000;
long long int OFFSET = 10000000000000;

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
      p.first = stoll(s.substr(0, pos)) + OFFSET;
      s.erase(0, pos + 4);
      p.second = stoll(s) + OFFSET;

      long long int y1 = p.second * a.first - p.first * a.second;
      long long int y2 = b.second * a.first - b.first * a.second;
      long long int x1 = p.first * b.second - p.second * b.first;
      long long int x2 = a.first * b.second - a.second * b.first;
      
      if (y1 % y2 == 0 && x1 % x2 == 0) {
        ans += (y1 / y2) + 3 * (x1 / x2);
      }
    }

    s = "";
  }

  cout << ans << endl;

  return 0;
}

// 94 = a.first
// 34 = a.second
// 22 = b.first
// 67 = b.second
// 10000000008400 = p.first
// 10000000005400 = p.second


// x * 94 + y * 22 = 10000000008400
// x * 94 = 10000000008400 - y * 22
// x = (10000000008400 - y * 22) / 94

// x * 34 + y * 67 = 10000000005400
// x * 34 = 10000000005400 - y * 67
// x = (10000000005400 - y * 67) / 34

// (10000000005400 - y * 67) / 34 = (10000000008400 - y * 22) / 94
// (10000000005400 - y * 67) * 94 = (10000000008400 - y * 22) * 34
// 10000000005400 * 94 - y * 67 * 94 = 10000000008400 * 34 - y * 22 * 34
// 10000000005400 * 94 - 10000000008400 * 34 = y * (67 * 94 - 22 * 34)
// y = (10000000005400 * 94 - 10000000008400 * 34) / (67 * 94 - 22 * 34)

// y = (p.second * a.first - p.first * a.second) / (b.second * a.first - b.first * a.second)





// x * 94 + y * 22 = 10000000008400
// x * 94 = 10000000008400 - y * 22
// y = (10000000008400 - x * 94) / 22

// x * 34 + y * 67 = 10000000005400
// x * 34 = 10000000005400 - y * 67
// y = (10000000005400 - x * 34) / 67

// (10000000008400 - x * 94) / 22 = (10000000005400 - x * 34) / 67
// (10000000008400 - x * 94) * 67 = (10000000005400 - x * 34) * 22
// 10000000008400 * 67 - x * 94 * 67 = 10000000005400 * 22 - x * 34 * 22
// 10000000008400 * 67 - 10000000005400 * 22 = x * (94 * 67 - 34 * 22)
// x = (10000000008400 * 67 - 10000000005400 * 22) / (94 * 67 - 34 * 22)

// x = (p.first * b.second - p.second * b.first) / (a.first * b.second - a.second * b.first)
