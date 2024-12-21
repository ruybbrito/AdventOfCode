#include <iostream>
#include <map>

using namespace std;

// dir = 0 -> up
// dir = 1 -> right
// dir = 2 -> down
// dir = 3 -> left

typedef pair<int, int> pii;

const int INF = 10000000;

char M[4][3];
map<char, pii> MI;

char K[2][3];
map<char, pii> KI;

bool is_oob_M(pii pos) {
  return pos.first < 0 || pos.first >= 4 || pos.second < 0 || pos.second >= 3 || M[pos.first][pos.second] == '*';
}

bool is_oob_K(pii pos) {
  return pos.first < 0 || pos.first >= 2 || pos.second < 0 || pos.second >= 3 || M[pos.first][pos.second] == '*';
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

string solve_second(string &s) {
  string ans = "";
  int x = 0, y = 2, cur = 0;
  while (cur < s.size()) {
    if (s[cur] == K[x][y]) {
      ans.push_back('A');
      cur++;
    }
    else {
      pii at = make_pair(x, y);
      pii next = KI[s[cur]];
      int dx = abs(at.first - next.first), dy = abs(at.second - next.second);
      while (dx--) ans.push_back(next.first > at.first ? 'v' : '^');
      while (dy--) ans.push_back(next.second > at.second ? '>' : '<');
      x = next.first, y = next.second;
    }
  }
  return ans;
}

// Count how many ways we can build s from the current state
int solve_third(string &s) {
  int ans = 0;
  int x = 0, y = 2, cur = 0;
  while (cur < s.size()) {
    if (s[cur] == K[x][y]) ans++, cur++;
    else {
      pii at = make_pair(x, y);
      pii next = KI[s[cur]];
      int dx = abs(at.first - next.first), dy = abs(at.second - next.second);
      ans += dx + dy;
      x = next.first, y = next.second;
    }
  }
  return ans;
}

int solve(string s, int depth) {
  string ans;
  vector<string> ret = solve_first(s, ans, 0, 3, 2);
  
  int min_len = INF;
  for (int i = 0; i < ret.size(); i++) {
    string next = ret[i];
    for (int j = 0; j < depth; j++) {
      next = solve_second(next);
    }
    
    min_len = min(min_len, solve_third(next));
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

int get_num(string s) {
  s.pop_back();
  return stoi(s);
}

int main() {
  // Set keypads
  set_keypad_0();
  set_keypad_1();

  string s;
  int ans = 0;
  while (cin >> s) {
    ans += (solve(s, 12) * get_num(s));
  }
  cout << ans << endl;
  
  return 0; 
}


//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

// ^^<A^>AvAvvA // 12
// (^^) –> 1 turns (-)
// (^<) –> 1 turns (v<A)
// (<A) –> 1 turns (^>>A)
// (A^) –> 2 turns (<A)
// (^>) –> 1 turns (v>A)
// (>A) –> 1 turns (^A)
// (Av) –> 2 turns (v<A)
// (vA) –> 2 turns (^>A)
// (vv) –> 1 turns (-)
// first –> ^

// <AAv<A^>>A<Av>A^Av<A^>Av<AA^>A // 30
// (^^) –> 
// (^<) –> 
// (^>) –> 3 turns (v>A)
// (^A) –> 1 turns (>A)
// (>A) –> 4 turns (^A)
// (>>) –> 1 turns (-)
// (vA) –> 
// (vv) –> 
// (v<) –> 3 turns (<A)
// (v>) –> 1 turns (>A)
// (<A) –> 5 turns (^>>A)
// (A^) –> 
// (Av) –> 
// (AA) –> 

// (78)
// (^^) –> 
// (^<) –> 
// (^>) –> 5
// (^A) –> 4
// (>A) –> 12
// (>>) –> 5
// (vA) –> 
// (vv) –> 
// (v<) –> 
// (v>) –> 3
// (<A) –> 3
// (A^) –> 
// (Av) –> 
// (AA) –> 
