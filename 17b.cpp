#include <iostream>
#include <map>

using namespace std;

long long int a, b, c;
int ptr;

long long int combo_operand(long long int operand) {
  if (operand <= 3) return operand;
  else if (operand == 4) return a;
  else if (operand == 5) return b;
  else if (operand == 6) return c;
  else return 0;
}

pair<string, long long int> operate(long long int opcode, long long int operand) {
  switch (opcode) {
    case 0: // adv
      a = (a >> combo_operand(operand));
      break;
    case 1: // axl
      b = b ^ operand;
      break;
    case 2: // bst
      b = combo_operand(operand) % 8;
      break;
    case 3: // jnz
      if (a == 0) break;
      else return make_pair("", operand);
      break;
    case 4: // bxc
      b = b ^ c;
      break;
    case 5: // out
      return make_pair(to_string(combo_operand(operand) % 8), -1);
    case 6: // bdv
      b = (a >> combo_operand(operand));
      break;
    case 7: // cdv
      c = (a >> combo_operand(operand));
      break;
  }

  return make_pair("", -1);
}

string bit_seq(long long int n, int len) {
  string s = "";
  while (n) {
    s += to_string(n%2);
    n >>= 1;
  }
  while (s.size() < len) s += "0";
  reverse(s.begin(), s.end());
  return s;
}

string bit_seq_from_vec(vector<long long int>& v) {
  string s = "";
  for (int i = 0; i < v.size(); i++) {
    s += bit_seq(v[i], 3);
  }
  return s;
}

long long int my_func(long long int X) {
  return ((((X % 8)^2)^3)^(X>>((X % 8)^2))) % 8;
}

bool vec_eq(vector<long long int> &a, vector<long long int> &b) {
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) return false;
  }  
  return true;
}

bool verify(vector<long long int> &pp, long long int aa) {
  vector<long long int> p = pp;
  reverse(p.begin(), p.end());

  a = aa, b = 0, c = 0;
  ptr = 0;

  vector<long long int> ans;
  while (ptr + 1 < p.size()) {
    long long int opcode = p[ptr];
    long long int operand = p[ptr+1];

    pair<string, long long int> out = operate(opcode, operand);
    if (out.second != -1) {
      ptr = out.second;
    } else {
      ptr += 2;
    }

    if (out.first.size() > 0) {
      ans.push_back(stoll(out.first));
    }
  }

  if (vec_eq(ans, p)) {
    cout << aa << endl;
    return true;
  }

  return false;
}

void solve(vector<long long int> &pp, int idx, long long int a_cur) {
  if (idx == pp.size()) {
    verify(pp, a_cur);
    return;
  }

  long long int b_cur = pp[idx];
  for (long long int j = 0; j < 8; j++) {
    long long int tmp = (a_cur << 3) + j;
    if (my_func(tmp) == b_cur) {
      solve(pp, idx+1, tmp);
    }
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

int main() {
  vector<long long int> p;
  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    if (s.substr(0, 11) == "Register A:") {
      s.erase(0, 12);
      a = stoi(s);
    }
    else if (s.substr(0, 11) == "Register B:") {
      s.erase(0, 12);
      b = stoi(s);
    }
    else if (s.substr(0, 11) == "Register C:") {
      s.erase(0, 12);
      c = stoi(s);
    }
    else if (s.substr(0, 8) == "Program:") {
      s.erase(0, 9);
      while (s.size() > 0) {
        p.push_back(stoi(s.substr(0, 1)));
        if (s.size() >= 2) s.erase(0, 2);
        else s.erase(0, 1);
      }
    }
  }

  vector<long long int> pp = p;
  reverse(pp.begin(), pp.end());

  solve(pp, 0, 0);

  return 0; 
}
