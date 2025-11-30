#include <iostream>
#include <map>
#include <set>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;
typedef pair<pii, pii> box;

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

set<box> find_boxes(vector<string>& m, pii init, int dir) {
  set<box> boxes;
  if (m[init.first][init.second] != '[' && m[init.first][init.second] != ']') {
    return boxes;
  } else {
    pii closing;
    if (m[init.first][init.second] == '[') {
      closing = make_pair(init.first, init.second + 1);
      boxes.insert(make_pair(init, closing));
    } else if (m[init.first][init.second] == ']') {
      closing = make_pair(init.first, init.second - 1);
      boxes.insert(make_pair(closing, init));
    }

    set<box> next_boxes = find_boxes(m, next_dir(init, dir), dir);
    for (set<box>::iterator it = next_boxes.begin(); it != next_boxes.end(); it++) {
      boxes.insert(*it);
    }

    next_boxes = find_boxes(m, next_dir(closing, dir), dir);
    for (set<box>::iterator it = next_boxes.begin(); it != next_boxes.end(); it++) {
      boxes.insert(*it);
    }

    return boxes;
  }
}

bool can_move_boxes(vector<string>& m, set<box>& s, int dir) {
  for (set<box>::iterator it = s.begin(); it != s.end(); it++) {
    pii open  = it->first, close = it->second;
    pii open_next = next_dir(open, dir), close_next = next_dir(close, dir);

    if (m[open_next.first][open_next.second] == '#') {
      return false;
    }

    if (m[close_next.first][close_next.second] == '#') {
      return false;
    }
  }

  return true;
}

bool sort_asc(const box& a, const box& b) {
  return a.first.first < b.first.first;
}

bool sort_desc(const box& a, const box& b) {
  return a.first.first > b.first.first;
}

void move_boxes(vector<string>& m, set<box>& s, int dir) {
  vector<box> v;
  for (set<box>::iterator it = s.begin(); it != s.end(); it++) {
    v.push_back(*it);
  }

  sort(v.begin(), v.end(), dir == 0 ? sort_asc : sort_desc);

  for (int i = 0; i < v.size(); i++) {
    pii open  = v[i].first, close = v[i].second;
    pii open_next = next_dir(open, dir), close_next = next_dir(close, dir);

    swap(m[open.first][open.second], m[open_next.first][open_next.second]);
    swap(m[close.first][close.second], m[close_next.first][close_next.second]);
  }
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
    // Horizontal move is easy, just repeat the previous logic
    if (dir == 1 || dir == 3) {
      while (m[next.first][next.second] == '[' || m[next.first][next.second] == ']') {
        next = next_dir(next, dir);
      }
      
      if (m[next.first][next.second] == '#') {
        // Boxes hit a wall, do nothing
        return pos;
      } else {
        // Can move the boxes
        pii prev = prev_dir(next, dir);
        while (m[prev.first][prev.second] == '[' || m[prev.first][prev.second] == ']') {
          swap(m[prev.first][prev.second], m[next.first][next.second]);
          next = prev;
          prev = prev_dir(prev, dir);
        }

        swap(m[prev.first][prev.second], m[next.first][next.second]);
        return next;
      }
    } else {
      // Vertical move is a bit more complicated
      set<box> boxes = find_boxes(m, next, dir);
      if (!can_move_boxes(m, boxes, dir)) {
        // Boxes hit a wall, do nothing
        return pos;
      }

      // Move boxes vertically
      move_boxes(m, boxes, dir);
      swap(m[pos.first][pos.second], m[next.first][next.second]);
      return next;
    }
  }
}

long long int get_gps(vector<string>& m) {
  long long int ans = 0;
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[i].size(); j++) {
      if (m[i][j] == '[') ans += (100 * i + j);
    }
  }
  return ans;
}

void print_map(vector<string>& m) {
  for (int i = 0; i < m.size(); i++) {
    cout << m[i] << endl;
  }
}

string evolve_map(string& s) {
  string ret = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'O') ret += "[]";
    else if (s[i] == '#') ret += "##";
    else if (s[i] == '.') ret += "..";
    else if (s[i] == '@') ret += "@.";
  }
  return ret;
}

int main() {
  vector<string> m;
  string ops;

  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    else if (s[0] == '#') {
      m.push_back(evolve_map(s));
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
