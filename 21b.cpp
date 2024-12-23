#include <iostream>
#include <map>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;
typedef pair<char, char> pcc;

const long long int INF = 100000000000000000LL;

char M[4][3];
map<char, pii> MI;

char K[2][3];
map<char, pii> KI;

bool is_oob_M(pii pos) {
  return pos.first < 0 || pos.first >= 4 || pos.second < 0 || pos.second >= 3 || M[pos.first][pos.second] == '*';
}

bool is_oob_K(pii pos) {
  return pos.first < 0 || pos.first >= 2 || pos.second < 0 || pos.second >= 3 || K[pos.first][pos.second] == '*';
}

vector<string> vec_concat(vector<string> a, vector<string> b, vector<string> c, vector<string> d) {
  vector<string> v;
  for (int i = 0; i < a.size(); i++) {
    v.push_back(a[i]);
  }
  for (int i = 0; i < b.size(); i++) {
    v.push_back(b[i]);
  }
  for (int i = 0; i < c.size(); i++) {
    v.push_back(c[i]);
  }
  for (int i = 0; i < d.size(); i++) {
    v.push_back(d[i]);
  }
  return v;
}

vector<string> solve_first(string &s, string ans, int idx, int x, int y) {
  if (idx == s.size()) {
    vector<string> v;
    v.push_back(ans);
    return v;
  }

  if (M[x][y] == s[idx]) {
    ans.push_back('A');
    return solve_first(s, ans, idx + 1, x, y);
  }

  pii next = MI[s[idx]];
  vector<string> up, down, left, right;

  // Can go up
  if (next.first < x && !is_oob_M(make_pair(x-1, y))) {
    ans.push_back('^');
    up = solve_first(s, ans, idx, x - 1, y);
    ans.pop_back();
  }

  // Can go down
  if (next.first > x && !is_oob_M(make_pair(x+1, y))) {
    ans.push_back('v');
    down = solve_first(s, ans, idx, x + 1, y);
    ans.pop_back();
  }
  
  // Can go right
  if (next.second > y && !is_oob_M(make_pair(x, y+1))) {
    ans.push_back('>');
    left = solve_first(s, ans, idx, x, y + 1);
    ans.pop_back();
  }

  // Can go left
  if (next.second < y && !is_oob_M(make_pair(x, y-1))) {
    ans.push_back('<');
    right = solve_first(s, ans, idx, x, y - 1);
    ans.pop_back();
  }

  return vec_concat(up, down, left, right);
}

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

pair<map<pcc, long long int>, char> calculate_transitions(map<pcc, long long int> transitions, char first_character) {
  map<pcc, long long int> next;
  for (map<pcc, long long int>::iterator it = transitions.begin(); it != transitions.end(); it++) {
    pcc m = it->first;
    string trans;
    if (m.first == m.second) {
      next[make_pair('A','A')] += it->second;
    } else {
      if (m.first == '^') {
        if (m.second == '<') {
          trans = "Av<A"; // Checked
        } else if (m.second == '>') {
          trans = "Av>A"; // Checked
        } else if (m.second == 'v') {
          trans = "AvA"; // Checked
        } else if (m.second == 'A') {
          trans = "A>A"; // Checked
        }
      } else if (m.first == '<') {
        if (m.second == '^') {
          trans = "A>^A"; // Checked
        } else if (m.second == '>') {
          trans = "A>>A"; // Checked
        } else if (m.second == 'v') {
          trans = "A>A"; // Checked
        } else if (m.second == 'A') {
          trans = "A>>^A"; // Checked
        }
      } else if (m.first == '>') {
        if (m.second == '^') {
          trans = "A<^A"; // Checked
        } else if (m.second == '<') {
          trans = "A<<A"; // Checked
        } else if (m.second == 'v') {
          trans = "A<A"; // Checked
        } else if (m.second == 'A') {
          trans = "A^A"; // Checked
        }
      } else if (m.first == 'v') {
        if (m.second == '^') {
          trans = "A^A"; // Checked
        } else if (m.second == '<') {
          trans = "A<A"; // Checked
        } else if (m.second == '>') {
          trans = "A>A"; // Checked
        } else if (m.second == 'A') {
          trans = "A^>A"; // Checked
        }
      } else if (m.first == 'A') {
        if (m.second == '^') {
          trans = "A<A"; // Checked
        } else if (m.second == '<') {
          trans = "Av<<A"; // Checked
        } else if (m.second == '>') {
          trans = "AvA"; // Checked
        } else if (m.second == 'v') {
          trans = "A<vA"; // Checked
        }
      }

      for (int i = 1; i < trans.size(); i++) {
        next[make_pair(trans[i-1], trans[i])] += it->second;
      }
    }
  }

  // Add the extra path from A to first_character
  string trans = "";
  switch (first_character) {
    case '^':
      trans = "<A"; // Checked
      break;
    case '<':
      trans = "v<<A"; // Checked
      break;
    case '>':
      trans = "vA"; // Checked
      break;
    case 'v':
      trans = "<vA"; // Checked
      break;
    case 'A':
      trans = "A"; // Checked
      break;
  }

  for (int i = 1; i < trans.size(); i++) {
    next[make_pair(trans[i-1], trans[i])] += 1LL;
  }

  return make_pair(next, trans[0]);
}

pair<map<pcc, long long int>, char> initial_state(string &s) {
  map<pcc, long long int> next;
  for (int i = 1; i < s.size(); i++) {
    next[make_pair(s[i-1], s[i])]++;
  }
  
  return make_pair(next, s[0]);
}

long long int calculate_len(map<pcc, long long int> &transitions) {
  long long int ans = 1LL;
  for (map<pcc, long long int>::iterator it = transitions.begin(); it != transitions.end(); it++) {
    ans += it->second;
  }
  return ans;
}

long long int solve(string s, int depth) {
  string ans;
  vector<string> ret = solve_first(s, ans, 0, 3, 2);
  
  long long int min_len = INF;
  for (int i = 0; i < ret.size(); i++) {
    pair<map<pcc, long long int>, char> state = initial_state(ret[i]);
    for (int k = 0; k < depth; k++) {
      state = calculate_transitions(state.first, state.second);
    }

    min_len = min(min_len, calculate_len(state.first));
  }

  return min_len;
}

// +---+---+---+
// | 7 | 8 | 9 |
// +---+---+---+
// | 4 | 5 | 6 |
// +---+---+---+
// | 1 | 2 | 3 |
// +---+---+---+
//     | 0 | A |
//     +---+---+

void set_keypad_0() {
  M[0][0] = '7';
  M[0][1] = '8';
  M[0][2] = '9';
  M[1][0] = '4';
  M[1][1] = '5';
  M[1][2] = '6';
  M[2][0] = '1';
  M[2][1] = '2';
  M[2][2] = '3';
  M[3][0] = '*';
  M[3][1] = '0';
  M[3][2] = 'A';

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      MI[M[i][j]] = make_pair(i, j);
    }
  }
}

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

void set_keypad_1() {
  K[0][0] = '*';
  K[0][1] = '^';
  K[0][2] = 'A';
  K[1][0] = '<';
  K[1][1] = 'v';
  K[1][2] = '>';

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      KI[K[i][j]] = make_pair(i, j);
    }
  }
}

long long int get_num(string s) {
  string ss = s;
  ss.pop_back();
  return stoll(ss);
}

int main() {
  // Set keypads
  set_keypad_0();
  set_keypad_1();

  string s;
  long long int ans = 0;
  while (cin >> s) {
    ans += (solve(s, 25) * get_num(s));
  }
  cout << ans << endl;

  return 0; 
}

// 274856120650160
// 265994052643760
// 274379456744896
// 1601417218531384
// 425538413136652
// 415296734621604
// 271308640918218
// 231309103124520 (correct!)
