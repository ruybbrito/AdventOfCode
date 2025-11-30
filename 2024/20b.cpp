#include <iostream>
#include <map>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;

vector<string> M;
pii S, E;

int dist[200][200], visited[200][200];

const int MAX_CHEAT_LEN = 20;
const int MIN_SAVE = 100;

bool is_oob(pii pos) {
  return pos.first < 0 || pos.second < 0 || pos.first >= M.size() || pos.second >= M[0].size();
}

long long int count_cheats(pii pos) {
  long long int ans = 0;
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M[0].size(); j++) {
      // Cannot reach this position with up to MAX_CHEAT_LEN moves
      int len = abs(i - pos.first) + abs(j - pos.second);
      if (len > MAX_CHEAT_LEN) continue;
      
      pii next = make_pair(i, j);
      if (
        M[next.first][next.second] != '#' &&
        dist[next.first][next.second] != -1 &&
        dist[next.first][next.second] - (dist[pos.first][pos.second] + len) >= MIN_SAVE
      ) {
        ans++;
      }
    }
  }
  return ans;
}

int main() {
  string s;
  while (cin >> s) {
    M.push_back(s);
  }

  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M[i].size(); j++) {
      if (M[i][j] == 'S') S = make_pair(i, j);
      if (M[i][j] == 'E') E = make_pair(i, j);
    }
  }

  memset(dist, -1, sizeof(dist));

  dist[S.first][S.second] = 0;
  visited[S.first][S.second] = 1;
  
  pii cur = S;
  while (cur != E) {
    if (!is_oob(make_pair(cur.first+1, cur.second)) && !visited[cur.first+1][cur.second] && M[cur.first+1][cur.second] != '#') {
      dist[cur.first+1][cur.second] = dist[cur.first][cur.second] + 1;
      visited[cur.first+1][cur.second] = 1;
      cur = make_pair(cur.first+1, cur.second);
      continue;
    } else if (!is_oob(make_pair(cur.first-1, cur.second)) && !visited[cur.first-1][cur.second] && M[cur.first-1][cur.second] != '#') {
      dist[cur.first-1][cur.second] = dist[cur.first][cur.second] + 1;
      visited[cur.first-1][cur.second] = 1;
      cur = make_pair(cur.first-1, cur.second);
      continue;
    } else if (!is_oob(make_pair(cur.first, cur.second+1)) && !visited[cur.first][cur.second+1] && M[cur.first][cur.second+1] != '#') {
      dist[cur.first][cur.second+1] = dist[cur.first][cur.second] + 1;
      visited[cur.first][cur.second+1] = 1;
      cur = make_pair(cur.first, cur.second+1);
      continue;
    } else if (!is_oob(make_pair(cur.first, cur.second-1)) && !visited[cur.first][cur.second-1] && M[cur.first][cur.second-1] != '#') {
      dist[cur.first][cur.second-1] = dist[cur.first][cur.second] + 1;
      visited[cur.first][cur.second-1] = 1;
      cur = make_pair(cur.first, cur.second-1);
      continue;
    }
  }

  long long int ans = 0;
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M[i].size(); j++) {
      if (dist[i][j] != -1 && M[i][j] != 'E') {
        // Count number of cheats starting at (i, j)
        ans += count_cheats(make_pair(i, j));
      }
    }
  }
  cout << ans << endl;

  return 0; 
}

// 626179
