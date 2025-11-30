#include <iostream>
#include <set>
#include <map>

using namespace std;

// dir = 0 –> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

bool is_oob(vector<string>& s, int x, int y) {
  return x < 0 || x >= s.size() || y < 0 || y >= s[0].size();
}

bool contains(vector<int>& v, int t) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == t) {
      return true;
    }
  }
  return false;
}

bool is_loop(vector<string>& s, int rx, int ry, int dir) {
  map<pair<int, int>, vector<int> > knocked;
  int x = rx, y = ry, nx, ny;
  while (true) {
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
      return false;
    }

    if (s[nx][ny] == '#') {
      if (contains(knocked[make_pair(nx, ny)], dir)) {
        return true;
      }
      knocked[make_pair(nx, ny)].push_back(dir);
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }
  }
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

  int rx = x, ry = y;
  
  map<pair<int, int>, vector<int> > knocked;
  set<pair<int, int> > obs; 
      
  int nx, ny;
  while (true) {
    // Verify if we could put an obstacle
    if (dir == 0 && x > 0 && s[x-1][y] == '.') {
      s[x-1][y] = '#';
      if (is_loop(s, rx, ry, 0)) {
        obs.insert(make_pair(x-1, y));
      }
      s[x-1][y] = '.';
    } else if (dir == 1 && y < s[0].size()-1 && s[x][y+1] == '.') {
      s[x][y+1] = '#';
      if (is_loop(s, rx, ry, 0)) {
        obs.insert(make_pair(x, y+1));
      }
      s[x][y+1] = '.';
    } else if (dir == 2 && x < s.size()-1 && s[x+1][y] == '.') {
      s[x+1][y] = '#';
      if (is_loop(s, rx, ry, 0)) {
        obs.insert(make_pair(x+1, y));
      }
      s[x+1][y] = '.';
    } else if (dir == 3 && y > 0 && s[x][y-1] == '.') {
      s[x][y-1] = '#';
      if (is_loop(s, rx, ry, 0)) {
        obs.insert(make_pair(x, y-1));
      }
      s[x][y-1] = '.';
    }

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

  cout << obs.size() << endl;

  return 0;
}
