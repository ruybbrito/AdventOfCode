#include <iostream>
#include <set>
#include <map>

using namespace std;

bool is_oob(vector<string>& s, int x, int y) {
  return x < 0 || x >= s.size() || y < 0 || y >= s[0].size();
}

int main() {
  vector<string> s;
  string a;

  set<char> chars;
  map<char, vector<pair<int, int> > > locations;

  while (cin >> a) {
    s.push_back(a);
  }

  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < s[i].size(); j++) {
      if (s[i][j] != '.') {
        chars.insert(s[i][j]);
        locations[s[i][j]].push_back(make_pair(i, j));
      }
    }
  }

  set<pair<int, int> > pos;
  for (set<char>::iterator it = chars.begin(); it != chars.end(); it++) {
    vector<pair<int, int> > v = locations[*it];
    if (v.size() == 1) {
      continue;
    }

    for (int i = 0; i < v.size(); i++) {
      for (int j = 0; j < v.size(); j++) {
        if (i == j) continue;

        int a = v[i].first - v[j].first;
        int b = v[i].second - v[j].second;
        if (!is_oob(s, v[i].first + a, v[i].second + b)) {
          pos.insert(make_pair(v[i].first + a, v[i].second + b));
        }
      }
    }
  }

  cout << pos.size() << endl;

  return 0;
}
