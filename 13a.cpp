#include <iostream>
#include <set>
#include <map>

using namespace std;

// int memo[101][101];
pair<int, int> a, b, p;

pair<int, int> mult(int x, int y) {
  return make_pair(x * a.first + y * b.first, x * a.second + y * a.second);
}

int sol(int x, int y) {
  pair<int, int> cur = mult(x, y);
  if (x > 100 || y > 100) {
    return 1000000;
  }

  if (p.first - cur.first < 0 || p.second - cur.second < 0) {
    return 1000000;
  }

  if (p.first - cur.first == 0 && p.second - cur.second == 0) {
    return 3 * x + y;
  }

  return min(sol(x + 1, y), sol(x, y + 1));  
}

int main() {
  string s, x;
  while (getline(cin, s)) {
    if (s == "") {
      continue;
    } else if (s.substr(0, 8) == "Button A") {
      s.erase(0, 12);
      int pos = s.find(", Y+");
      a.first = stoi(s.substr(0, pos));
      s.erase(0, pos + 4);
      a.second = stoi(s);
    } else if (s.substr(0, 8) == "Button B") {
      s.erase(0, 12);
      int pos = s.find(", Y+");
      b.first = stoi(s.substr(0, pos));
      s.erase(0, pos + 4);
      b.second = stoi(s);
    } else if (s.substr(0, 5) == "Prize") {
      s.erase(0, 9);
      int pos = s.find(", Y=");
      p.first = stoi(s.substr(0, pos));
      s.erase(0, pos + 4);
      p.second = stoi(s);

      // for (int i = 0; i < 101; i++) {
      //   for (int j = 0; j < 101; j++) {
      //     memo[i][j] = -1;
      //   }
      // }

      cout << sol(0, 0) << endl;
    }

    s = "";
  }

  return 0;
}
