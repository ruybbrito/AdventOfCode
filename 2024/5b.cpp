#include <iostream>

using namespace std;

bool container_contains(vector<pair<int, int> >& container, pair<int, int> v) {
  for (int i = 0; i < container.size(); i++) {
    if (container[i].first == v.first && container[i].second == v.second) {
      return true;
    }
  }
  return false;
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

vector<int> bubble_sort(vector<int> &query, vector<pair<int, int> >& input) {
  for (int i = 0; i < query.size(); i++) {
    for (int j = i+1; j < query.size(); j++) {
      if (container_contains(input, make_pair(query[j], query[i]))) {
        swap(query[i], query[j]);
      }
    }
  }
  return query;
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

  int count = 0;
  for (int i = 0; i < queries.size(); i++) {
    // Query is correct
    if (is_query_correct(queries[i], input)) {
      continue;
    }

    vector<int> ans = bubble_sort(queries[i], input);
    count += ans[ans.size()/2];
  }

  cout << count << endl;
  return 0;
}
