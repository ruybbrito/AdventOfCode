#include <iostream>

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

string bit_seq(long long int n) {
  string s = "";
  while (n) {
    s += to_string(n%2);
    n >>= 1;
  }
  while (s.size() < 3) s += "0";
  reverse(s.begin(), s.end());
  return s;
}

string bit_seq_from_vec(vector<long long int>& v) {
  string s = "";
  for (int i = 0; i < v.size(); i++) {
    s += bit_seq(v[i]);
  }
  return s;
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
  string bseq = bit_seq_from_vec(pp);

  for (int i = 0; i < bseq.size(); i++) {
    cout << bseq << endl;

    a = to_decimal(bseq), b = 0, c = 0;
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

    for (int j = 0; j < ans.size(); j++) {
      cout << ans[j] << " ";
    }
    cout << endl;
    for (int j = 0; j < p.size(); j++) {
      cout << p[j] << " ";
    }
    cout << endl;

    char q = bseq.back();
    bseq.pop_back();
    bseq.insert(bseq.begin(), q);
  }

  return 0; 
}


// Register A: X
// Register B: 0
// Register C: 0

// Program: 2,4,1,2,7,5,1,3,4,4,5,5,0,3,3,0

// (a = X, b = 0, c = 0)

// ptr = 0, input = (2, 4)
// (a = X, b = X % 8, c = 0)

// ptr = 2, input = (1, 2)
// (a = X, b = (X % 8)^2, c = 0)

// ptr = 4, input = (7, 5)
// (a = X, b = (X % 8)^2, c = X >> ((X % 8)^2)

// ptr = 6, input = (1, 3)
// (a = X, b = ((X % 8)^2)^3, c = X >> ((X % 8)^2)

// ptr = 8, input = (4, 4)
// (a = X, b = (((X % 8)^2)^3)^(X >> ((X % 8)^2)), c = X >> (X % 8)^2)

// ptr = 10, input = (5, 5)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X, b = (((X % 8)^2)^3)^(X >> ((X % 8)^2)), c = X >> (X % 8)^2)

// ptr = 12, input = (0, 3)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = (((X % 8)^2)^3)^(X >> ((X % 8)^2)), c = X >> (X % 8)^2)

// ptr = 12, input = (0, 3)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = (((X % 8)^2)^3)^(X >> ((X % 8)^2)), c = X >> (X % 8)^2)

// ptr = 0, input = (2, 4)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = (X>>3) % 8, c = X >> (X % 8)^2)

// ptr = 2, input = (1, 2)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = ((X>>3)%8)^2, c = X >> (X % 8)^2)

// ptr = 4, input = (7, 5)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = ((X>>3)%8)^2, c = (X>>3)>>(((X>>3)%8)^2) )

// ptr = 6, input = (1, 3)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = (((X>>3)%8)^2)^3, c = (X>>3)>>(((X>>3)%8)^2) )

// ptr = 8, input = (4, 4)
// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// (a = X>>3, b = ((((X>>3)%8)^2)^3)^((X>>3)>>(((X>>3)%8)^2)), c = (X>>3)>>(((X>>3)%8)^2) )

// ptr = 10, input = (5, 5)
// 4 = ((((X>>3)%8)^2)^3)^((X>>3)>>(((X>>3)%8)^2))%8
// (a = X>>3, b = ((((X>>3)%8)^2)^3)^((X>>3)>>(((X>>3)%8)^2)), c = (X>>3)>>(((X>>3)%8)^2) )

// It's a number between 2^42 and 2^43




// 2 = (((X % 8)^2)^3)^(X >> (X % 8)^2)) % 8
// 2 = ((X % 8)^1)^(X/(pow(2, X % 8))) % 8
// 2 = ( (X % 8) ^ 1 ^ (X/(pow(2, X % 8))) ) % 8
