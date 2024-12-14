#include <iostream>
#include <map>

using namespace std;

const int GRID_W = 101;
const int GRID_H = 103;
const int SEC = 500;

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

int is_symmetric(map<pii, int>& cnt) {
  for (int y = 0; y < GRID_H; y++) {
    for (int x = 0; x < GRID_W; x++) {
      int a = cnt[make_pair(x, y)], b = cnt[make_pair(GRID_W - x - 1, y)];
      if (a != b) return 0;    
    }
  }
  return 1;
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

  map<int, map<pii, int> > cnt;
  for (int sec = 0; sec <= 10000000; sec++) {
    for (int i = 0; i < robots.size(); i++) {
      pii pos = get_position_on_nth_second(robots[i], sec);
      cnt[sec][pos]++;
    }
  }
  
  for (int sec = 0; sec <= 10000000; sec++) {
    if (!is_symmetric(cnt[sec])) {
      continue;
    }

    cout << sec << endl;
    for (int y = 0; y < GRID_H; y++) {
      for (int x = 0; x < GRID_W; x++) {
        int k = cnt[sec][make_pair(x, y)];
        cout << (k == 0 ? "." : (k == 1 ? "X" : "O"));
      }
      cout << endl;
    }

    break;
  }

  return 0;
}
