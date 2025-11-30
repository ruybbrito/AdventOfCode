#include <iostream>
#include <vector>

using namespace std;

bool container_contains(vector<pair<int, int> >& container, pair<int, int> v) {
  vector<pair<int, int> >::iterator it = std::lower_bound(
    container.begin(),
    container.end(),
    v
  );
  return it != container.end() && *it == v;
}

bool is_query_correct(vector<int> &query, vector<pair<int, int> >& input) {
  for (int i = 0; i < query.size(); i++) {
    for (int j = i+1; j < query.size(); j++) {
      if (container_contains(input, make_pair(query[j], query[i]))) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  string s;
  vector<pair<int, int> > input;
  vector<vector<int> > queries;
  while (cin >> s) {
    int a, b, c;
    int pos = s.find("|");
    if (pos != string::npos) {
      a = stoi(s.substr(0, pos));
      s.erase(0, pos + 1);
      b = stoi(s);
      input.push_back(make_pair(a, b));
    } else {
      vector<int> q;
      while ((pos = s.find(",")) != string::npos) {
        q.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + 1);
      }
      q.push_back(stoi(s.substr(0, pos)));
      if (q.size() > 0) {
        queries.push_back(q);
      }
    }
  }

  sort(input.begin(), input.end());

  int ans = 0;
  for (int i = 0; i < queries.size(); i++) {
    if (is_query_correct(queries[i], input)) {
      ans += queries[i][queries[i].size()/2];
    }
  }

  cout << ans << endl;
  return 0;
}
