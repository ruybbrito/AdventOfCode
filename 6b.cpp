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

bool is_valid_gap(vector<string>& s, int x, int y, int xx, int yy) {
  if (x == xx) {
    for (int i = min(y, yy) + 1; i < max(y, yy); i++) {
      if (s[x][i] == '#') {
        return false;
      }
    }

    return true;
  } else if (y == yy) {
    for (int i = min(x, xx) + 1; i < max(x, xx); i++) {
      if (s[i][y] == '#') {
        return false;
      }
    }

    return true;
  }

  return false;
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

  map<pair<int, int>, vector<int> > knocked;
  vector<pair<int, int> > prev;
  set<pair<int, int> > obs; 
      
  int nx, ny, ans = 0;
  while (true) {
    // Verify if we could put an obstacle
    if (prev.size() >= 3) {
      for (int i = 0; i <= prev.size()-3; i++) {
        int knockedDir = -1;
        for (int j = 0; j < knocked[prev[i]].size(); j++) {
          if (knocked[prev[i]][j] == (dir + 1) % 4) {
            knockedDir = knocked[prev[i]][j];
            break;
          }
        }
        if (knockedDir == -1) {
          continue;
        }

        if (knockedDir == 0 && y == prev[i].second && x > prev[i].first) {
          if (is_valid_gap(s, x, y, prev[i].first, prev[i].second)) {
            cout << x << " " << y - 1 << endl;
            obs.insert(make_pair(x, y - 1));
          }
        } else if (knockedDir == 1 && x == prev[i].first && y < prev[i].second) {
          if (is_valid_gap(s, x, y, prev[i].first, prev[i].second)) {
            cout << x - 1 << " " << y << endl;
            obs.insert(make_pair(x - 1, y));
          }
        } else if (knockedDir == 2 && y == prev[i].second && x < prev[i].first) {
          if (is_valid_gap(s, x, y, prev[i].first, prev[i].second)) {
            cout << x << " " << y + 1 << endl;
            obs.insert(make_pair(x, y + 1));
          }
        } else if (knockedDir == 3 && x == prev[i].first && y > prev[i].second) {
          if (is_valid_gap(s, x, y, prev[i].first, prev[i].second)) {
            cout << x + 1 << " " << y << endl;
            obs.insert(make_pair(x + 1, y));
          }
        }
      }
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
      prev.push_back(make_pair(nx, ny));
      knocked[make_pair(nx, ny)].push_back(dir);
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }
  }

  cout << obs.size() << endl;

  return 0;
}
