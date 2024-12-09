#include <iostream>
#include <map>

using namespace std;

// Tries to find a gap of length >= len with index up to r
// Can be optimized to log(N), but I can't be bothered.
pair<int, int> findGap(vector<pair<int, int> >& gaps, int len, int r) {
  pair<int, int> bestGap = make_pair(-1, -1);
  for (int i = 0; i < gaps.size(); i++) {
    if (gaps[i].first < r && gaps[i].second >= len) {
      if (bestGap.first == -1 || bestGap.first > gaps[i].first) {
        bestGap = gaps[i];
      }
    }
  }
  
  return bestGap;
}

// Can be optimized to log(N), but I can't be bothered.
void removeGap(vector<pair<int, int> >& gaps, pair<int, int> old_gap) {
  for (int i = 0; i < gaps.size(); i++) {
    if (gaps[i] == old_gap) {
      gaps.erase(gaps.begin() + i);
      return;
    }
  }

  return;
}

int main() {
  string s;
  cin >> s;

  string mem = "";
  map<int, long long int> id;
  vector<pair<int, int> > gaps, blocks;
  for (int i = 0; i < 100 * s.size(); i++) id[i] = -1;
  
  int x = 1, cur_id = 0;
  for (int i = 0; i < s.size(); i++) {
    // Found gap
    if (!x && s[i]-'0' > 0) {
      gaps.push_back(make_pair(mem.size(), s[i]-'0'));
    }

    // Found block
    if (x && s[i]-'0' > 0) {
      blocks.push_back(make_pair(mem.size(), s[i]-'0'));
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

  reverse(blocks.begin(), blocks.end());

  for (int i = 0; i < blocks.size(); i++) {
    pair<int, int> gap = findGap(gaps, blocks[i].second, blocks[i].first);
    if (gap.first == -1) {
      // Can't find a placement for the block
      continue;
    }

    removeGap(gaps, gap);
    if (blocks[i].second != gap.second) {
      pair<int, int> newGap = make_pair(gap.first + blocks[i].second, gap.second - blocks[i].second);
      gaps.push_back(newGap);
    }

    // Fix the memory
    for (int j = 0; j < blocks[i].second; j++) {
      swap(mem[gap.first + j], mem[blocks[i].first + j]);
      id[gap.first + j] = id[blocks[i].first + j];
      id[blocks[i].first + j] = -1;
    }
  }

  long long int ans = 0;
  for (long long int i = 0; i < mem.size(); i++) {
    if (mem[i] != '.') ans += i * id[i];
  }
  cout << ans << endl;

  return 0;
}
