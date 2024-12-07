#include <iostream>
#include <set>

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

  int knocked[1000][1000];
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      knocked[i][j] = -1;
    }
  }
  
  vector<pair<int, int> > prev;
  set<pair<int, int> > obs; 
      
  int nx, ny, ans = 0;
  while (true) {
    // cout << "MOVE: " << x << " " << y << endl;
    // Verify if we could put an obstacle
    if (prev.size() >= 3) {
      for (int i = 0; i <= prev.size()-3; i++) {
        int knockedDir = knocked[prev[i].first][prev[i].second];
        if (knockedDir == (dir + 1) % 4) {
          if (knockedDir == 0 && y == prev[i].second && x > prev[i].first) {
            bool shouldUse = true;
            for (int j = x - 1; j > prev[i].first; j--) {
              if (s[j][y] == '#') {
                shouldUse = false;
                break;
              }
            }
            if (shouldUse) {
              cout << x << " " << y - 1 << endl;
              obs.insert(make_pair(x, y - 1));
            }
          } else if (knockedDir == 1 && x == prev[i].first && y < prev[i].second) {
            bool shouldUse = true;
            for (int j = y + 1; j < prev[i].second; j++) {
              if (s[x][j] == '#') {
                shouldUse = false;
                break;
              }
            }
            if (shouldUse) {
              cout << x - 1 << " " << y << endl;
              obs.insert(make_pair(x - 1, y));
            }
          } else if (knockedDir == 2 && y == prev[i].second && x < prev[i].first) {
            bool shouldUse = true;
            for (int j = x + 1; j < prev[i].first; j++) {
              if (s[j][y] == '#') {
                shouldUse = false;
                break;
              }
            }
            if (shouldUse) {
              cout << x << " " << y + 1 << endl;
              obs.insert(make_pair(x, y + 1));
            }
          } else if (knockedDir == 3 && x == prev[i].first && y > prev[i].second) {
            bool shouldUse = true;
            for (int j = y - 1; j > prev[i].second; j--) {
              if (s[x][j] == '#') {
                shouldUse = false;
                break;
              }
            }
            if (shouldUse) {
              cout << x + 1 << " " << y << endl;
              obs.insert(make_pair(x + 1, y));
            }
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
      knocked[nx][ny] = dir;
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }
  }

  cout << obs.size() << endl;

  return 0;
}
