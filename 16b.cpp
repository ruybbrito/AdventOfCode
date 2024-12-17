#include <iostream>
#include <map>
#include <set>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;
typedef pair<pii, int> position;
typedef pair<int, position> piii;

pii S, E;
vector<string> m;

const int INF = 100000000;

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

bool can_go(pii pos, int dir) {
  pii next = get_next(pos, dir);
  return !is_oob(m, next) && (m[next.first][next.second] == '.' || m[next.first][next.second] == 'E');
}

vector<position> all_valid(pii pos, int dir) {
  vector<pair<pii, int> > ans;
  if (can_go(pos, dir)) ans.push_back(make_pair(get_next(pos, dir), dir));
  if (can_go(pos, next_dir(dir))) ans.push_back(make_pair(get_next(pos, next_dir(dir)), next_dir(dir)));
  if (can_go(pos, prev_dir(dir))) ans.push_back(make_pair(get_next(pos, prev_dir(dir)), prev_dir(dir)));
  return ans;
}

void print_solutions(set<pii>& visited) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (visited.find(make_pair(i, j)) != visited.end()) {
        cout << "O";
      } else {
        cout << m[i][j];
      }
    }
    cout << endl;
  }
}

int solve() {
  priority_queue<piii, vector<piii>, greater<piii> > pq;

  int dist[200][200];
  set<pii> parents[200][200];
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      dist[i][j] = INF;
    }
  }

  pq.push(make_pair(0, make_pair(S, 3)));
  dist[S.first][S.second] = 0;

  while (!pq.empty()) {
    piii cur = pq.top();
    pq.pop();

    vector<position> valid = all_valid(cur.second.first, cur.second.second);
    for (int i = 0; i < valid.size(); i++) {
      pii next = get_next(cur.second.first, cur.second.second);
      position adj = valid[i];
      pii adj_pos = adj.first;
      int adj_dir = adj.second;
      int weight = adj_pos == next ? 1 : 1001;

      if (cur.second.first == make_pair(7, 4)) {
        cout << adj_pos.first << " " << adj_pos.second << " " << weight << endl;
        cout << dist[adj_pos.first][adj_pos.second] << endl;
        cout << dist[cur.second.first.first][cur.second.first.second] << endl;
        cout << parents[adj_pos.first][adj_pos.second].size() << endl;
      }

      if (dist[adj_pos.first][adj_pos.second] >= dist[cur.second.first.first][cur.second.first.second] + weight) {
        dist[adj_pos.first][adj_pos.second] = dist[cur.second.first.first][cur.second.first.second] + weight;
        parents[adj_pos.first][adj_pos.second].insert(cur.second.first);
        pq.push(make_pair(dist[adj_pos.first][adj_pos.second], adj));
      }
    }
  }

  set<pii> visited;
  queue<pii> q;
  q.push(E);
  while (!q.empty()) {
    pii top = q.front();
    q.pop();
    visited.insert(top);
    
    for (set<pii>::iterator it = parents[top.first][top.second].begin(); it != parents[top.first][top.second].end(); it++) {
      q.push(*it);
    }
  }

  print_solutions(visited);

  // return visited.size();
  return dist[E.first][E.second];
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

  cout << solve() << endl;

  return 0;
}
