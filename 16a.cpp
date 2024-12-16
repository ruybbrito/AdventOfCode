#include <iostream>
#include <map>

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

bool can_go(int mark[150][110], pii pos, int dir) {
  pii next = get_next(pos, dir);
  return !is_oob(m, next) && (m[next.first][next.second] == '.' || m[next.first][next.second] == 'E') && !mark[next.first][next.second];
}

int solve(int mark[150][110], pii pos, int dir, int ans) {
  if (pos == E) {
    return ans;
  }
  
  int cur_ans = INF;
  
  // Go straight
  if (can_go(mark, pos, dir)) {
    pii next = get_next(pos, dir);
    mark[next.first][next.second] = 1;
    cur_ans = min(cur_ans, solve(mark, next, dir, ans + 1));
    mark[next.first][next.second] = 0;
  }

  // Can turn right
  int n = next_dir(dir);
  if (can_go(mark, pos, n)) {
    pii next = get_next(pos, n);
    mark[next.first][next.second] = 1;
    cur_ans = min(cur_ans, solve(mark, next, n, ans + 1001));
    mark[next.first][next.second] = 0;
  }

  // Can turn left
  int p = prev_dir(dir);
  if (can_go(mark, pos, p)) {
    pii next = get_next(pos, p);
    mark[next.first][next.second] = 1;
    cur_ans = min(cur_ans, solve(mark, next, p, ans + 1001));
    mark[next.first][next.second] = 0;
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

  int mark[150][110];
  for (int i = 0; i < 150; i++) {
    for (int j = 0; j < 110; j++) {
      mark[i][j] = 0;
    }  
  }

  mark[S.first][S.second] = 1;
  cout << solve(mark, S, 3, 0) << endl;

  return 0;
}
