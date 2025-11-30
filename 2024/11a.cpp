#include <iostream>
#include <set>
#include <map>

using namespace std;

pair<long long int, long long int> split(long long int v) {
  string s = to_string(v);
  if (s.size() % 2 == 0) {
    return make_pair(stoll(s.substr(0, s.size() / 2)), stoll(s.substr(s.size() / 2, s.size() / 2)));
  } 

  return make_pair(-1, -1);
}

int main() {
  vector<long long int> v, vNext;
  long long int a;
  while (cin >> a) {
    v.push_back(a);
  }

  for (int i = 0; i < 25; i++) { 
    for (int j = 0; j < v.size(); j++) {
      if (v[j] == 0) vNext.push_back(1);
      else {
        pair<long long int, long long int> p = split(v[j]);
        if (p.first != -1) {
          vNext.push_back(p.first);
          vNext.push_back(p.second);
        } else {
          vNext.push_back(v[j] * 2024);
        }
      }
    }

    v = vNext;
    vNext.clear();
  }

  cout << v.size() << endl;

  return 0;
}
