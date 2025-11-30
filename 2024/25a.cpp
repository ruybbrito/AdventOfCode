#include <iostream>
#include <map>
#include <set>

using namespace std;

vector<map<int, int> > locks, keys;

void get_config(vector<string> &v) {
  bool is_lock = true;
  for (int j = 0; j < v[0].size(); j++) {
    is_lock = is_lock && (v[0][j] == '#');
  }

  if (is_lock) {
    map<int, int> config;
    for (int i = 0; i < v.size(); i++) {
      for (int j = 0; j < v[i].size(); j++) {
        if (v[i][j] == '#') {
          config[j] = max(config[j], i);
        }
      }
    }

    locks.push_back(config);
  } else {
    map<int, int> config;
    for (int i = 0; i < v.size(); i++) {
      for (int j = 0; j < v[i].size(); j++) {
        if (v[i][j] == '#') {
          config[j] = max(config[j], 6 - i);
        }
      }
    }

    keys.push_back(config);
  }

  return;
}

int main() {
  vector<string> v;
  string s;
  while (getline(cin, s)) {
    if (s == "") {
      get_config(v);
      v.clear();
    } else {
      v.push_back(s);
    }
  }

  if (v.size() > 0) {
    get_config(v);
  }

  int ans = 0;
  for (int i = 0; i < locks.size(); i++) {
    for (int j = 0; j < keys.size(); j++) {
      bool fits = true;
      for (int k = 0; k < 5; k++) {
        if (locks[i][k] + keys[j][k] > 5) {
          fits = false;
          break;
        } 
      }

      if (fits) ans++;
    }
  }
  
  cout << ans << endl;

  return 0; 
}
