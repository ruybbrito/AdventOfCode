#include <iostream>
#include <map>

using namespace std;

// Tries to find a gap of length >= len with index up to r
pair<int, int> findGap(vector<pair<int, int> >& gaps, int len, int r) {
  pair<int, int> bestGap = make_pair(-1, -1);
  for (int i = 0; i < gaps.size(); i++) {
    if (gaps[i].first < r && gaps[i].second >= len) {
      if (bestGap.first < gaps[i].first) {
        bestGap = gaps[i];
      }
    }
  }
  
  return bestGap;
}

int main() {
  string s;
  cin >> s;

  string mem = "";
  map<int, long long int> id;
  vector<pair<int, int> > gaps;
  for (int i = 0; i < 100 * s.size(); i++) id[i] = -1;
  
  int x = 1, cur_id = 0;
  for (int i = 0; i < s.size(); i++) {
    if (!x && s[i]-'0' > 0) {
      gaps.push_back(make_pair(mem.size(), s[i]-'0'));
    }

    for (int j = 0; j < s[i]-'0'; j++) {
      if (x) {
        mem.push_back(s[i]);
        id[mem.size()-1] = cur_id;
      } else {
        mem.push_back('.');
      }
    }
    x = 1 - x;
    if (x) cur_id++;
  }

  // Fix the memory
  // for (int a = 0, b = mem.size()-1; a < b;) {
  //   if (mem[a] == '.' && mem[b] != '.') {
  //     swap(mem[a], mem[b]);
  //     id[a] = id[b];
  //     id[b] = -1;
  //     a++, b--;
  //   } else if (mem[a] != '.') {
  //     a++;
  //   } else if (mem[b] == '.') {
  //     b--;
  //   }
  // }
  for (int i = mem.size() - 1; i >= 0; i--) {
    if (mem[i] == '.') continue;
    
    int len = 1;
    if (i > 0) {
      for (int j = i-1; j >= 0; j--) {
        if (mem[j] == mem[i]) len++;
        else {
          i = j+1;
        };
      }
    }

    pair<int, int> gap = findGap(gaps, len, i);
    // Fix memory using the gap
  }

  long long int ans = 0;
  for (long long int i = 0; i < mem.size(); i++) {
    if (mem[i] == '.') break;
    ans += i * id[i];
  }
  cout << ans << endl;

  return 0;
}
