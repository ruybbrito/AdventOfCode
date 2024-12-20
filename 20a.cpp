#include <iostream>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;

vector<string> M;
pii S, E;

bool is_oob(pii pos) {
  return pos.first < 0 || pos.second < 0 || pos.first >= M.size() || pos.second >= M[0].size();
}

pii get_next(pii pos, int dir) {
  int iNext = dir == 0 ? pos.first - 1 : dir == 2 ? pos.first + 1 : pos.first;
  int jNext = dir == 1 ? pos.second + 1 : dir == 3 ? pos.second - 1 : pos.second;
  return make_pair(iNext, jNext);
}

int cheat(int dist[200][200], pii pos, int dir) {
  pii next = get_next(pos, dir);
  pii next_next = get_next(next, dir);

  if (
    !is_oob(next) &&
    !is_oob(next_next) &&
    M[next.first][next.second] == '#' &&
    M[next_next.first][next_next.second] != '#' &&
    dist[next_next.first][next_next.second] > dist[pos.first][pos.second] + 2
  ) {
    return dist[next_next.first][next_next.second] - (dist[pos.first][pos.second] + 2);
  } else {
    return -1;
  }
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

  int dist[200][200], visited[200][200];
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

  vector<int> dirs;
  dirs.push_back(0);
  dirs.push_back(1);
  dirs.push_back(2);
  dirs.push_back(3);

  int ans = 0;
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M[i].size(); j++) {
      if (M[i][j] == '#') continue;

      // Check if we can cheat 
      for (int d = 0; d < 4; d++) {
        int ch = cheat(dist, make_pair(i, j), d);
        if (ch >= 100) {
          ans++;
        }
      }
    }
  }

  cout << ans << endl;
  
  return 0; 
}
