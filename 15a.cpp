#include <iostream>
#include <map>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;

pii next_dir(pii cur, int dir) {
  int iNext = dir == 0 ? cur.first - 1 : dir == 2 ? cur.first + 1 : cur.first;
  int jNext = dir == 1 ? cur.second + 1 : dir == 3 ? cur.second - 1 : cur.second;
  return make_pair(iNext, jNext);
}

pii prev_dir(pii cur, int dir) {
  int iPrev = dir == 0 ? cur.first + 1 : dir == 2 ? cur.first - 1 : cur.first;
  int jPrev = dir == 1 ? cur.second - 1 : dir == 3 ? cur.second + 1 : cur.second;
  return make_pair(iPrev, jPrev);
}

// Attempts to move the robot and returns the new position
pii move_robot(vector<string>& m, pii pos, int dir) {
  pii next = next_dir(pos, dir);
  if (m[next.first][next.second] == '#') {
    // Hit a wall, do nothing
    return pos;
  } else if (m[next.first][next.second] == '.') {
    // Move to the next position
    swap(m[pos.first][pos.second], m[next.first][next.second]);
    return next;
  } else {
    // Hit boxes, try to move them
    while (m[next.first][next.second] == 'O') {
      next = next_dir(next, dir);
    }
    
    if (m[next.first][next.second] == '#') {
      // Boxes hit a wall, do nothing
      return pos;
    } else {
      // Can move the boxes
      pii prev = prev_dir(next, dir);
      while (m[prev.first][prev.second] == 'O') {
        swap(m[prev.first][prev.second], m[next.first][next.second]);
        next = prev;
        prev = prev_dir(prev, dir);
      }

      swap(m[prev.first][prev.second], m[next.first][next.second]);
      return next;
    }
  }
}

long long int get_gps(vector<string>& m) {
  long long int ans = 0;
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (m[i][j] == 'O') ans += (100 * i + j);
    }
  }
  return ans;
}

void print_map(vector<string>& m) {
  for (int i = 0; i < m.size(); i++) {
    cout << m[i] << endl;
  }
}

int main() {
  vector<string> m;
  string ops;

  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    else if (s[0] == '#') {
      m.push_back(s);
    } else {
      ops += s;
    }
  }

  pii pos;
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (m[i][j] == '@') {
        pos = make_pair(i, j);
        break;
      }
    }
  }

  for (int i = 0; i < ops.size(); i++) {
    // cout << ops[i] << endl;
    if (ops[i] == '>') pos = move_robot(m, pos, 1);
    else if (ops[i] == '<') pos = move_robot(m, pos, 3);
    else if (ops[i] == '^') pos = move_robot(m, pos, 0);
    else if (ops[i] == 'v') pos = move_robot(m, pos, 2);
    // print_map(m);
  }

  cout << get_gps(m) << endl;

  return 0;
}
