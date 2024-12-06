#include <iostream>

using namespace std;

// dir = 0 –> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

bool is_oob(vector<string>& s, int x, int y) {
  return x < 0 || x >= s.size() || y < 0 || y >= s[0].size();
}

int main() {
  vector<string> s;
  string a;
  int x = 0, y = 0, dir = 0;
  while (cin >> a) {
    s.push_back(a);
    for (int i = 0; i < a.size(); i++) {
      if (a[i] == '^') {
        x = s.size()-1;
        y = i;
        break;
      }
    }
  }
  
  int visited[1000][1000];
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      visited[i][j] = 0;
    }
  }
      
  int nx, ny;
  while (true) {
    visited[x][y] = 1;
    if (dir == 0) {
      nx = x - 1;
      ny = y;
    } else if (dir == 1) {
      nx = x;
      ny = y + 1;
    } else if (dir == 2) {
      nx = x + 1;
      ny = y;
    } else if (dir == 3) {
      nx = x;
      ny = y - 1;
    }

    if (is_oob(s, nx, ny)) {
      break;
    }

    if (s[nx][ny] == '#') {
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }
  }

  int ans = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      ans += visited[i][j];
    }
  }
  cout << ans << endl;

  return 0;
}
