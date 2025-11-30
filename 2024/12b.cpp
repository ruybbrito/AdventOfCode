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

bool cant_go(vector<string>& m, int i, int j, int dir) {
  int iNext = dir == 1 ? i+1 : dir == 3 ? i-1 : i;
  int jNext = dir == 0 ? j+1 : dir == 2 ? j-1 : j;
  return is_oob(m, iNext, jNext) || m[i][j] != m[iNext][jNext];
}

bool can_go(vector<string>& m, int i, int j, int dir) {
  return !cant_go(m, i, j, dir);
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

int find_corners(vector<string>& m, int i, int j) {
  int ans = 0;

  // 90 degree turns
  if (cant_go(m, i, j, 3) && cant_go(m, i, j, 2)) ans++;
  if (cant_go(m, i, j, 1) && cant_go(m, i, j, 2)) ans++;
  if (cant_go(m, i, j, 1) && cant_go(m, i, j, 0)) ans++;
  if (cant_go(m, i, j, 3) && cant_go(m, i, j, 0)) ans++; 
  
  // 270 degree turns
  if (can_go(m, i, j, 3) && can_go(m, i, j, 2) && m[i][j] != m[i-1][j-1]) ans++;
  if (can_go(m, i, j, 1) && can_go(m, i, j, 2) && m[i][j] != m[i+1][j-1]) ans++;
  if (can_go(m, i, j, 1) && can_go(m, i, j, 0) && m[i][j] != m[i+1][j+1]) ans++;
  if (can_go(m, i, j, 3) && can_go(m, i, j, 0) && m[i][j] != m[i-1][j+1]) ans++;

  return ans;
}

int aggregate_corners(vector<string>& m, map<pair<int, int>, int>& corners, int mark[200][200], int i, int j) {
  if (mark[i][j]) return 0;

  mark[i][j] = 1;
  int c = corners[make_pair(i, j)];

  if (!is_oob(m, i+1, j) && !mark[i+1][j] && m[i][j] == m[i+1][j]) c += aggregate_corners(m, corners, mark, i+1, j);
  if (!is_oob(m, i-1, j) && !mark[i-1][j] && m[i][j] == m[i-1][j]) c += aggregate_corners(m, corners, mark, i-1, j);
  if (!is_oob(m, i, j+1) && !mark[i][j+1] && m[i][j] == m[i][j+1]) c += aggregate_corners(m, corners, mark, i, j+1);
  if (!is_oob(m, i, j-1) && !mark[i][j-1] && m[i][j] == m[i][j-1]) c += aggregate_corners(m, corners, mark, i, j-1);

  return c;
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

  map<pair<int, int>, int> areas, corners, sides;

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark[i][j]) continue;
      areas[make_pair(i, j)] = find_area(m, i, j, mark);
    }
  }

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      corners[make_pair(i, j)] = find_corners(m, i, j);
    }
  }

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark2[i][j]) continue;
      sides[make_pair(i, j)] = aggregate_corners(m, corners, mark2, i, j);
    }
  }

  long long int ans = 0;
  for (map<pair<int, int>, int>::iterator it = areas.begin(); it != areas.end(); it++) {
    ans += it->second * sides[it->first];
  }

  cout << ans << endl;

  return 0;
}
