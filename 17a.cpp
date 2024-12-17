#include <iostream>

using namespace std;

int a, b, c;
int ptr;

int combo_operand(int operand) {
  if (operand <= 3) return operand;
  else if (operand == 4) return a;
  else if (operand == 5) return b;
  else if (operand == 6) return c;
  else return 0;
}

pair<string, int> operate(int opcode, int operand) {
  switch (opcode) {
    case 0: // adv
      a =  a / pow(2, operand);
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
      b =  a / pow(2, operand);
      break;
    case 7: // cdv
      c =  a / pow(2, operand);
      break;
  }

  return make_pair("", -1);
}

int main() {
  vector<int> p;
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

  string ans = "";
  while (ptr + 1 < p.size()) {
    int opcode = p[ptr];
    int operand = p[ptr+1];

    pair<string, int> out = operate(opcode, operand);
    if (out.second != -1) {
      ptr = out.second;
    } else {
      ptr += 2;
    }

    if (out.first.size() > 0) {
      ans += (out.first)+",";
    }
  }

  ans.pop_back();
  cout << ans << endl;
  
  return 0; 
}
