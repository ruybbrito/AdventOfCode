#include <iostream>
#include <set>
#include <map>

using namespace std;

// dir = 0 -> right
// dir = 1 -> down
// dir = 2 -> left
// dir = 3 -> up

bool is_oob(vector<string>& m, int i, int j) {
  return i < 0 || j < 0 || i >= m.size() || j >= m[0].size();
}

bool can_go(vector<string>& m, int i, int j, int dir) {
  int iNext = dir == 1 ? i+1 : dir == 3 ? i-1 : i;
  int jNext = dir == 0 ? j+1 : dir == 2 ? j-1 : j;
  return !is_oob(m, iNext, jNext) && m[i][j] == m[iNext][jNext];
}

int find_area(vector<string>& m, int i, int j, int mark[200][200]) {
  if (mark[i][j]) return 0;

  mark[i][j] = 1;
  int a = 1;
  if (!is_oob(m, i+1, j) && !mark[i+1][j] && m[i][j] == m[i+1][j]) a += find_area(m, i+1, j, mark);
  if (!is_oob(m, i-1, j) && !mark[i-1][j] && m[i][j] == m[i-1][j]) a += find_area(m, i-1, j, mark);
  if (!is_oob(m, i, j+1) && !mark[i][j+1] && m[i][j] == m[i][j+1]) a += find_area(m, i, j+1, mark);
  if (!is_oob(m, i, j-1) && !mark[i][j-1] && m[i][j] == m[i][j-1]) a += find_area(m, i, j-1, mark);

  return a;
}

int find_sides(vector<string>& m, int i, int j, int mark[200][200]) {
  int dir = 0, initDir = 0;
  int x = i, y = j;
  int s = 0;
  
  while (true) {
    mark[x][y] = 1;
    
    if (!can_go(m, x, y, dir)) {
      s++;
      dir = (dir + 1) % 4;
    } else {
      x = dir == 1 ? x+1 : dir == 3 ? x-1 : x;
      y = dir == 0 ? y+1 : dir == 2 ? y-1 : y;

      // Check if we should change direction
      int dirPrev = (((dir - 1) % 4) + 4) % 4;
      if (can_go(m, x, y, dirPrev)) {
        dir = dirPrev;
        s++;
      }
    }

    if (x == i && y == j && dir == initDir) break;
  }

  // Find if there are islands of non- m[i][j]
  // If yes, then check their sides and add to s
  
  return s;
}

int main() {
  vector<string> m;
  string s;
  while (cin >> s) {
    m.push_back(s);
  }

  int mark[200][200], mark2[200][200];
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      mark[i][j] = 0;
      mark2[i][j] = 0;
    }
  }

  map<pair<int, int>, int> areas, sides;

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark[i][j]) continue;
      areas[make_pair(i, j)] = find_area(m, i, j, mark);
    }
  }

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark2[i][j]) continue;
      sides[make_pair(i, j)] = find_sides(m, i, j, mark2);
    }
  }

  long long int ans = 0;
  for (map<pair<int, int>, int>::iterator it = areas.begin(); it != areas.end(); it++) {
    ans += it->second * sides[it->first];
  }

  cout << ans << endl;

  return 0;
}
