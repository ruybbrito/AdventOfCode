#include <iostream>
#include <map>
#include <set>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;
typedef pair<pii, int> raindeer;

pii S, E;
vector<string> m;

const int INF = 10000000;

bool is_oob(vector<string>& m, pii pos) {
  return pos.first < 0 || pos.second < 0 || pos.first >= m.size() || pos.second >= m[0].size();
}

int next_dir(int dir) {
  return (dir + 1) % 4;
}

int prev_dir(int dir) {
  return (((dir - 1) % 4) + 4) % 4;
}

pii get_next(pii pos, int dir) {
  int iNext = dir == 0 ? pos.first - 1 : dir == 2 ? pos.first + 1 : pos.first;
  int jNext = dir == 1 ? pos.second + 1 : dir == 3 ? pos.second - 1 : pos.second;
  return make_pair(iNext, jNext);
}

bool can_go(set<pii>& path, pii pos, int dir) {
  pii next = get_next(pos, dir);
  return !is_oob(m, next) && (m[next.first][next.second] == '.' || m[next.first][next.second] == 'E') && path.find(next) == path.end();
}

int solve(set<pii>& path, pii pos, int dir, int ans) {
  if (pos == E) {
    cout << ans << endl;
    return ans;
  }
  
  int cur_ans = INF;
  
  // Go straight
  if (can_go(path, pos, dir)) {
    pii next = get_next(pos, dir);
    path.insert(next);
    cur_ans = min(cur_ans, solve(path, next, dir, ans + 1));
    path.erase(path.find(next));
  }

  // Can turn right
  int n = next_dir(dir);
  if (can_go(path, pos, n)) {
    pii next = get_next(pos, n);
    path.insert(next);
    cur_ans = min(cur_ans, solve(path, next, n, ans + 1001));
    path.erase(path.find(next));
  }

  // Can turn left
  int p = prev_dir(dir);
  if (can_go(path, pos, p)) {
    pii next = get_next(pos, p);
    path.insert(next);
    cur_ans = min(cur_ans, solve(path, next, p, ans + 1001));
    path.erase(path.find(next));
  }

  return cur_ans;
}

int main() {
  string s;
  while (getline(cin, s))
    m.push_back(s);

  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (m[i][j] == 'S') {
        S = make_pair(i, j);
      }
      if (m[i][j] == 'E') {
        E = make_pair(i, j);
      }
    }
  }

  set<pii> path;
  path.insert(S);
  cout << solve(path, S, 3, 0) << endl;

  return 0;
}
