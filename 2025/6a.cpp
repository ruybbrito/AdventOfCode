#include <iostream>

typedef long long int ll;

using namespace std;

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main() {
  string s;
  vector<int> in;
  vector<char> op;
  while (cin >> s) {
    vector<string> parts = split(s, " ");
    if (parts[0] == "*" || parts[0] == "+") {
        for(int i = 0; i < parts.size(); i++) {
            op.push_back(parts[i][0]);
        }
    } else {
        for(int i = 0; i < parts.size(); i++) {
            in.push_back(stoi(parts[i]));
        }
    }
  }

  vector<vector<int> > add, mult;

  for (int i = 0; i < op.size(); i++) {
    vector<int> cur;
    for (int j = i; j < in.size(); j += op.size()) {
        cur.push_back(in[j]);
    }
    if (op[i] == '+') add.push_back(cur);
    else mult.push_back(cur);
  }

  ll ans = 0;

  for (int i = 0; i < add.size(); i++) {
    ll cur = add[i][0];
    for (int j = 1; j < add[i].size(); j++) cur += add[i][j];
    ans += cur;
  }

  for (int i = 0; i < mult.size(); i++) {
    ll cur = mult[i][0];
    for (int j = 1; j < mult[i].size(); j++) cur *= mult[i][j];
    ans += cur;
  }

  cout << ans << endl;

  return 0;
}


