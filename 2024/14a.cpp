#include <iostream>
#include <map>

using namespace std;

const int GRID_W = 101;
const int GRID_H = 103;
const int SEC = 100;

typedef pair<int, int> pii;
typedef pair<pii, pii> robot;

pii to_pair(string& s) {
  int pos = s.find(",");
  return make_pair(stoi(s.substr(0, pos)), stoi(s.substr(pos+1, s.size() - pos)));
}

int safe_mod(int n, int k) {
  return ((n % k) + k) % k;
}

pii get_position_on_nth_second(robot r, int sec) {
  pii init_p = r.first;
  pii v = r.second;

  int final_x = safe_mod(init_p.first + (v.first * sec), GRID_W);
  int final_y = safe_mod(init_p.second + (v.second * sec), GRID_H);

  return make_pair(final_x, final_y);
}

int quadrant(pii p) {
  if (p.first == GRID_W / 2 || p.second == GRID_H / 2) return -1;

  if (2 * p.first < GRID_W && 2 * p.second < GRID_H) return 0;
  else if (2 * p.first > GRID_W && 2 * p.second > GRID_H) return 3;
  else if (2 * p.first < GRID_W && 2 * p.second > GRID_H) return 2;
  else if (2 * p.first > GRID_W && 2 * p.second < GRID_H) return 1;
  
  return -1;
}

int main() {
  vector<robot> robots;
  string s, p, v;
  while (getline(cin, s)) {
    int pos = s.find(" ");
    p = s.substr(2, pos - 2);
    s.erase(0, pos + 1);
    v = s.substr(2, s.size() - 2);
    robots.push_back(make_pair(to_pair(p), to_pair(v)));
  }

  map<pii, int> cnt;
  for (int i = 0; i < robots.size(); i++) {
    pii pos = get_position_on_nth_second(robots[i], SEC);
    cnt[pos]++;
  }

  // for (int y = 0; y < GRID_H; y++) {
  //   for (int x = 0; x < GRID_W; x++) {
  //     cout << cnt[make_pair(x, y)];
  //   }
  //   cout << endl;
  // }

  map<int, long long int> m;
  for (int y = 0; y < GRID_H; y++) {
    for (int x = 0; x < GRID_W; x++) {
      pii pos = make_pair(x, y);
      m[quadrant(pos)] += cnt[pos];
    }
  }

  cout << m[0] * m[1] * m[2] * m[3] << endl;
  return 0;
}
