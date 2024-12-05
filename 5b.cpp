#include <iostream>
#include <vector>

using namespace std;

bool container_contains(vector<pair<int, int> >& container, pair<int, int> v) {
  for (int i = 0; i < container.size(); i++) {
    if (container[i].first == v.first && container[i].second == v.second) {
      return true;
    }
  }
  return false;
  // vector<pair<int, int> >::iterator it = std::lower_bound(
  //   container.begin(),
  //   container.end(),
  //   v
  // );
  // return it != container.end() && *it == v;
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

void visit(vector<pair<int, int> >& input, vector<int> &query, vector<int> &ans, int mark[], int val) {
  if (mark[val]) return;

  mark[val] = 1;
  for (int i = 0; i < input.size(); i++) {
    if (input[i].first == val) {
      visit(input, query, ans, mark, input[i].second);
    }
  }

  ans.push_back(val);
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
    if (is_query_correct(queries[i], input)) {
      continue;
    }

    // for (int j = 0; j < queries[i].size(); j++) {
    //   cout << queries[i][j] << " ";
    // }
    // cout << endl;

    vector<int> ans;
    int mark[101] = {0};
    for(int j = 0; j < queries[i].size(); j++) {
      visit(input, queries[i], ans, mark, queries[i][j]);
    }
    
    vector<int> filtered;
    for(int j = 0; j < ans.size(); j++) {
      for (int k = 0; k < queries[i].size(); k++) {
        if (ans[j] == queries[i][k]) {
          filtered.push_back(ans[j]);
          break;
        }
      }
    }

    // for (int j = 0; j < filtered.size(); j++) {
    //   cout << filtered[j] << " ";
    // }
    // cout << endl;
    
    count += filtered[filtered.size()/2];
  }

  cout << count << endl;
  return 0;
}
