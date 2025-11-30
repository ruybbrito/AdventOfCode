#include <iostream>
#include <set>
#include <map>

using namespace std;

bool is_oob(vector<string>& m, int i, int j) {
  return i < 0 || j < 0 || i >= m.size() || j >= m[0].size();
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

int find_perimeter(vector<string>& m, int i, int j, int mark[200][200]) {
  if (mark[i][j]) return 0;

  mark[i][j] = 1;
  int p = 0;
  if (!is_oob(m, i+1, j) && !mark[i+1][j] && m[i][j] == m[i+1][j]) p += find_perimeter(m, i+1, j, mark);
  else if (is_oob(m, i+1, j) || m[i][j] != m[i+1][j]) p++;
  
  if (!is_oob(m, i-1, j) && !mark[i-1][j] && m[i][j] == m[i-1][j]) p += find_perimeter(m, i-1, j, mark);
  else if (is_oob(m, i-1, j) || m[i][j] != m[i-1][j]) p++;
  
  if (!is_oob(m, i, j+1) && !mark[i][j+1] && m[i][j] == m[i][j+1]) p += find_perimeter(m, i, j+1, mark);
  else if (is_oob(m, i, j+1) || m[i][j] != m[i][j+1]) p++;
  
  if (!is_oob(m, i, j-1) && !mark[i][j-1] && m[i][j] == m[i][j-1]) p += find_perimeter(m, i, j-1, mark);
  else if (is_oob(m, i, j-1) || m[i][j] != m[i][j-1]) p++;

  return p;
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

  map<pair<int, int>, int> areas, perimeters;

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark[i][j]) continue;
      areas[make_pair(i, j)] = find_area(m, i, j, mark);
    }
  }

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (mark2[i][j]) continue;
      perimeters[make_pair(i, j)] = find_perimeter(m, i, j, mark2);
    }
  }

  long long int ans = 0;
  for (map<pair<int, int>, int>::iterator it = areas.begin(); it != areas.end(); it++) {
    ans += it->second * perimeters[it->first];
  }

  cout << ans << endl;

  return 0;
}
