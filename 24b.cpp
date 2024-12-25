#include <iostream>
#include <map>
#include <set>

using namespace std;

typedef pair<string, string> pss;


// op = 0 –> OR
// op = 1 –> AND
// op = 2 –> XOR

// (64892933710960)
string expected_seq = "1110110000010100010000010000110010010001110000";

// 312 nodes in total
// 45 nodes x, 45 nodes y, 46 nodes z
// 11 nodes z are wrong
// 169 nodes could be wrong

map<string, int> value;
set<string> keys;
set<string> keys_with_value, init_keys_with_value;
map<string, vector<pair<pss, int> > > operations;
map<string, vector<pss> > operands;
map<string, int> depth;

vector<string> split(string s) {
  vector<string> ret;
  string tmp = "";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ' ') {
      ret.push_back(tmp);
      tmp = "";
    } else {
      tmp += s[i];
    }
  }
  ret.push_back(tmp);
  return ret;
}

int get_op(string s) {
  switch (s[0]) {
    case 'O':
      return 0;
    case 'A':
      return 1;
    case 'X':
      return 2;
    default:
      return -1;
  }
}

int get_value(string op1, string op2, int op) {
  switch (op) {
    case 0:
      return value[op1] | value[op2];
    case 1:
      return value[op1] & value[op2];
    case 2:
      return value[op1] ^ value[op2];
    default:
      return -1;
  }
}

long long int to_decimal(string s) {
  string r = s;
  reverse(r.begin(), r.end());
  long long int ans = 0;
  for (int i = r.size()-1; i >= 0; i--) {
    ans += r[i] == '1' ? (1LL<<i) : 0;
  }
  return ans;
}

int check_depth(string t) {
  int max_depth = 1;
  for (int j = 0; j < operands[t].size(); j++) {
    max_depth = max(max_depth, 1 + check_depth(operands[t][j].first));
    max_depth = max(max_depth, 1 + check_depth(operands[t][j].second));
  }

  return depth[t] = max_depth;
}

void check_str_depth() {
  for (int i = 0; i <= 45; i++) {
    string num = to_string(i);
    if (num.size() == 1) num = "0" + num;
    string z = "z" + num;
    check_depth(z);
  }
}

string simulate_and_find_bit_seq() {
  keys_with_value = init_keys_with_value;

  while (keys_with_value.size() < keys.size()) {
    for (map<string, vector<pair<pss, int> > >::iterator it = operations.begin(); it != operations.end(); it++) {
      string op1 = it->first;
      if (keys_with_value.find(op1) != keys_with_value.end()) {
        for (int i = 0; i < it->second.size(); i++) {
          string op2 = it->second[i].first.first;
          string op3 = it->second[i].first.second;
          int op = it->second[i].second;

          if (keys_with_value.find(op2) != keys_with_value.end() && keys_with_value.find(op3) == keys_with_value.end()) {
            value[op3] = get_value(op1, op2, op);
            keys_with_value.insert(op3);
          }
        }
      }
    }
  }

  string bit_seq = "";
  for (set<string>::iterator it = keys.begin(); it != keys.end(); it++) {
    if ((*it)[0] == 'z') {
      bit_seq += (value[*it] ? '1' : '0');
    }
  }

  reverse(bit_seq.begin(), bit_seq.end());
  return bit_seq;
}

int expected_depth(string z) {
  if (z == "z00") return 2;

  int x = stoi(z.substr(1));
  return (2 * x) + 1;
}

int is_key_swappable(string x) {
  return x[0] != 'x' && x[0] != 'y';
}

void fix_setup(map<string, string> &swaps, bool do_operations) {
  // Fix operands
  for (map<string, vector<pss> >::iterator it = operands.begin(); it != operands.end(); it++) {
    if (swaps[it->first] != "") {
      vector<pss> tmp = operands[it->first];
      operands[it->first] = operands[swaps[it->first]];
      operands[swaps[it->first]] = tmp;
    }
  }

  if (do_operations) {
    // Fix operations
    for (map<string, vector<pair<pss, int> > >::iterator it = operations.begin(); it != operations.end(); it++) {
      for (int i = 0; i < it->second.size(); i++) {
        if (swaps[it->second[i].first.second] != "") {
          it->second[i].first.second = swaps[it->second[i].first.second];
        }
      }
    }
  }
}

void solve(map<string, string> &swaps, int cur) {
  string num = to_string(cur);
  if (num.size() == 1) num = "0" + num;
  string cur_z = "z" + num;

  cout << cur_z << " " << swaps.size() << endl;

  if (cur == 46) {
    if (swaps.size() == 8) {
      for (map<string, string>::iterator it = swaps.begin(); it != swaps.end(); it++) {
        cout << it->first << " " << it->second << endl;
      }
    }

    return;
  }

  // Recalc depth
  check_str_depth();
  if (depth[cur_z] != expected_depth(cur_z)) {
    // Find a swap that would get us there
    for (set<string>::iterator x = keys.begin(); x != keys.end(); x++) {
      if (!is_key_swappable(*x) || swaps[*x] != "") {
        continue;
      }

      for (set<string>::iterator y = keys.begin(); y != keys.end(); y++) {
        if (!is_key_swappable(*y) || swaps[*y] != "") {
          continue;
        }

        if (*x == *y) continue;

        cout << "Trying " << *x << " " << *y << endl;

        // Add swap
        swaps[*x] = *y;
        swaps[*y] = *x;
        fix_setup(swaps, false);

        // Recalc depth
        check_str_depth();
        if (depth[cur_z] == expected_depth(cur_z)) {
          solve(swaps, cur + 1);
        }

        // Remove swap
        swaps[*x] = "";
        swaps[*y] = "";
        fix_setup(swaps, false);
      }
    }
  } else {
    solve(swaps, cur + 1);
  }

  return;
}

int main() {
  map<string, string> swaps;
  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    if (s[3] == ':') {
      value[s.substr(0, 3)] = stoi(s.substr(5));
      keys.insert(s.substr(0, 3));
      init_keys_with_value.insert(s.substr(0, 3));
    } else {
      vector<string> ss = split(s);
      keys.insert(ss[0]);
      keys.insert(ss[2]);
      keys.insert(ss[4]);

      operations[ss[0]].push_back(make_pair(make_pair(ss[2], ss[4]), get_op(ss[1])));
      operands[ss[4]].push_back(make_pair(ss[0], ss[2]));
    }
  }

  string bit_seq = simulate_and_find_bit_seq();

  cout << bit_seq << endl;
  cout << expected_seq << endl;
  cout << to_decimal(bit_seq) << endl;
  cout << to_decimal(expected_seq) << endl;

  solve(swaps, 0);

  return 0; 
}
