#include <iostream>
#include <map>
#include <set>

using namespace std;

set<int> adj[3000];
set<int> nodes;

string to_str(int x) {
  char ch1 = (x % 100) + 'a';
  char ch2 = (x / 100) + 'a';
  return string(1, ch2) + string(1, ch1);
}

int to_int(string str) {
  return 100 * (str[0] - 'a') + (str[1] - 'a');
}

// Starts with t
bool is_good(int x) {
  return (x / 100) == ('t' - 'a');
}

int solve() {
  int ans = 0;

  for (set<int>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    for (set<int>::iterator i = adj[*it].begin(); i != adj[*it].end(); i++) {
      if (*i <= *it) continue;
      for (set<int>::iterator j = adj[*i].begin(); j != adj[*i].end(); j++) {
        if (*j <= *i) continue;
        if (adj[*j].find(*it) != adj[*j].end()) {
          if (is_good(*it) || is_good(*i) || is_good(*j)) {
            ans++;
            // cout << to_str(*it) << "-" << to_str(*i) << "-" << to_str(*j) << endl;
          }
        }
      }
    }
  }

  return ans;
}

int main() {
  string s;
  int a, b;
  while (cin >> s) {
    a = to_int(s.substr(0, 2));
    b = to_int(s.substr(3, 2));
    adj[a].insert(b);
    adj[b].insert(a);
    nodes.insert(a);
    nodes.insert(b);
  }

  cout << solve() << endl;

  return 0;
}
