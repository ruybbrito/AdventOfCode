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
set<string> keys_with_value;
map<string, vector<pair<pss, int> > > operations;
map<string, vector<pss> > operands;

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

void count_possible_wrongs(string bit_seq) {
  set<string> wrongs;
  for (int i = 0; i < expected_seq.size(); i++) {
    if (expected_seq[i] != bit_seq[i]) {
      string wrong = "z" + to_string(expected_seq.size() - i - 1);

      queue<string> q;
      q.push(wrong);
      while (!q.empty()) {
        string t = q.front();
        wrongs.insert(t);
        q.pop();

        for (int j = 0; j < operands[t].size(); j++) {
          if (operands[t][j].first[0] != 'x' && operands[t][j].first[0] != 'y') {
            q.push(operands[t][j].first);
          }
          if (operands[t][j].second[0] != 'x' && operands[t][j].second[0] != 'y') {
            q.push(operands[t][j].second);
          }
        }
      }
    }
  }

  cout << wrongs.size() << endl;
}

int main() {
  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    if (s[3] == ':') {
      value[s.substr(0, 3)] = stoi(s.substr(5));
      keys.insert(s.substr(0, 3));
      keys_with_value.insert(s.substr(0, 3));
    } else {
      vector<string> ss = split(s);
      keys.insert(ss[0]);
      keys.insert(ss[2]);
      keys.insert(ss[4]);

      operations[ss[0]].push_back(make_pair(make_pair(ss[2], ss[4]), get_op(ss[1])));
      operands[ss[4]].push_back(make_pair(ss[0], ss[2]));
    }
  }

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
  cout << to_decimal(bit_seq) << endl;

  count_possible_wrongs(bit_seq);

  return 0; 
}
