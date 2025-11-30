#include <iostream>
#include <map>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

pii S, E;
vector<string> m;

const int N = 70 + 1;
const int INF = 100000000;

bool is_oob(pii pos) {
  return pos.first < 0 || pos.second < 0 || pos.first >= m.size() || pos.second >= m[0].size();
}

bool can_go(int visited[200][200], pii pos) {
  return m[pos.first][pos.second] == '.' && !visited[pos.first][pos.second];
}

vector<pii> all_valid(int visited[200][200], pii pos) {
  vector<pii> ans;
  if (can_go(visited, make_pair(pos.first+1, pos.second))) ans.push_back(make_pair(pos.first+1, pos.second));
  if (can_go(visited, make_pair(pos.first-1, pos.second))) ans.push_back(make_pair(pos.first-1, pos.second));
  if (can_go(visited, make_pair(pos.first, pos.second+1))) ans.push_back(make_pair(pos.first, pos.second+1));
  if (can_go(visited, make_pair(pos.first, pos.second-1))) ans.push_back(make_pair(pos.first, pos.second-1));
  return ans;
}

int solve() {
  priority_queue<piii, vector<piii>, greater<piii> > pq;

  int dist[200][200], visited[200][200];
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      dist[i][j] = INF;
      visited[i][j] = 0;
    }
  }

  pq.push(make_pair(0, S));
  dist[S.first][S.second] = 0;
  visited[S.first][S.second] = 1;

  while (!pq.empty()) {
    piii cur = pq.top();
    pq.pop();

    vector<pii> valid = all_valid(visited, cur.second);
    for (int i = 0; i < valid.size(); i++) {
      pii adj = valid[i];

      if (dist[adj.first][adj.second] > dist[cur.second.first][cur.second.second] + 1) {
        dist[adj.first][adj.second] = dist[cur.second.first][cur.second.second] + 1;
        visited[adj.first][adj.second] = 1;
        pq.push(make_pair(dist[adj.first][adj.second], adj));
      }
    }
  }

  return dist[E.first][E.second];
}

int main() {
  string s;
  for (int i = 0; i < N; i++) {
    s = "";
    for (int j = 0; j < N; j++) s.push_back('.');
    m.push_back(s);
  }
  
  int x, y;
  int cnt = 0;
  while (getline(cin, s)) {
    int pos = s.find(",");
    x = stoi(s.substr(0, pos));
    s.erase(0, pos+1);
    y = stoi(s);

    if (cnt < 1024) {
      m[y][x] = '#';
      cnt++;
    }
  }

  S = make_pair(0, 0);
  E = make_pair(N-1, N-1);

  cout << solve() << endl;

  return 0;
}
