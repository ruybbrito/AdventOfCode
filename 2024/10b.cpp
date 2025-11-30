#include <iostream>
#include <set>
#include <map>

using namespace std;

int findPaths(vector<vector<int> >& v, int x, int y, int cur) {
  if (x < 0 || x >= v.size() || y < 0 || y >= v[0].size()) {
    return 0;
  }

  if (cur == 9) {
    return 1;
  }

  int ans = 0;
  if (x+1 < v.size() && v[x+1][y] == cur+1) ans += findPaths(v, x+1, y, cur+1);
  if (x-1 >= 0 && v[x-1][y] == cur+1) ans += findPaths(v, x-1, y, cur+1);
  if (y+1 < v[0].size() && v[x][y+1] == cur+1) ans += findPaths(v, x, y+1, cur+1);
  if (y-1 >= 0 && v[x][y-1] == cur+1) ans += findPaths(v, x, y-1, cur+1);

  return ans;
}

int main() {
  vector<vector<int> > v;
  string a;

  while (cin >> a) {
    vector<int> w;
    for (int i = 0; i < a.size(); i++) {
      w.push_back(a[i] - '0');
    }
    v.push_back(w);
  }

  int ans = 0;
  for(int i = 0 ; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      if (v[i][j] == 0) {
        ans += findPaths(v, i, j, 0);
      }
    }
  }

  cout << ans << endl;

  return 0;
}
