#include <iostream>
#include <set>

typedef long long int ll;

using namespace std;

int main() {
  string s;
  vector<string> m;
  while (cin >> s) {
    m.push_back(s);
  }

  set<int> c;
  for (int j = 0; j < m[0].size(); j++) {
    if (m[0][j] == 'S') c.insert(j);
  }

  int ans = 0;
  for (int i = 1; i < m.size(); i++) {
    set<int> nc, sp;
    for (int j = 0; j < m[i].size(); j++) {
        if (m[i][j] == '^' && c.find(j) != c.end()) {
            ans++;
            sp.insert(j);
            if (j > 0) nc.insert(j-1);
            if (j+1 < m[i].size()) nc.insert(j+1);
        }
    }
    // Remove sp
    for (set<int>::iterator it = sp.begin(); it != sp.end(); it++) {
        c.erase(*it);
    }

    // Add nc
    for (set<int>::iterator it = nc.begin(); it != nc.end(); it++) {
        c.insert(*it);
    }
  }

  cout << ans << endl;

  return 0;
}


