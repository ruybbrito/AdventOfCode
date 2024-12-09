#include <iostream>
#include <map>

using namespace std;

int main() {
  string s;
  cin >> s;

  string mem = "";
  map<int, long long int> id;
  for (int i = 0; i < 100 * s.size(); i++) id[i] = -1;
  
  int x = 1, cur_id = 0;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < s[i]-'0'; j++) {
      if (x) {
        mem.push_back(s[i]);
        id[mem.size()-1] = cur_id;
      } else {
        mem.push_back('.');
      }
    }
    x = 1 - x;
    if (x) cur_id++;
  }

  // Fix the memory
  for (int a = 0, b = mem.size()-1; a < b;) {
    if (mem[a] == '.' && mem[b] != '.') {
      swap(mem[a], mem[b]);
      id[a] = id[b];
      id[b] = -1;
      a++, b--;
    } else if (mem[a] != '.') {
      a++;
    } else if (mem[b] == '.') {
      b--;
    }
  }

  long long int ans = 0;
  for (long long int i = 0; i < mem.size(); i++) {
    if (mem[i] == '.') break;
    ans += i * id[i];
  }
  cout << ans << endl;

  return 0;
}
