#include <iostream>
#include <map>

using namespace std;

int K = 2000;
int L = 24;

string bit_seq(long long int n) {
  string s = "";
  while (n) {
    s += to_string(n%2);
    n >>= 1;
  }
  while (s.size() < L) s.push_back('0');
  reverse(s.begin(), s.end());
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

string shift_left(string s, int n) {
  while (n--) s.push_back('0');
  return s;
}

string shift_right(string s, int n) {
  while (n--) s.pop_back();
  return s;
}

char ch_xor(char a, char b) {
  return a == b ? '0' : '1';
}

string mix(string a, string b) {
  string aa = a, bb = b;
  string c;
  reverse(aa.begin(), aa.end());
  reverse(bb.begin(), bb.end());
  int ptr = 0;
  for (; ptr < min(aa.size(), bb.size()); ptr++) {
    c.push_back(ch_xor(aa[ptr], bb[ptr]));
  }
  while (ptr < aa.size()) {
    c.push_back(aa[ptr]);
    ptr++;
  }
  while (ptr < bb.size()) {
    c.push_back(bb[ptr]);
    ptr++;
  }
  reverse(c.begin(), c.end());
  return c;
}

string prune(string s) {
  reverse(s.begin(), s.end());
  string v = s.substr(0, 24);
  reverse(v.begin(), v.end());
  return v;
}

string next_secret(string secret) {
  // Calculate the result of multiplying the secret number by 64.
  // Then, mix this result into the secret number.
  // Finally, prune the secret number.
  // x = (x ^ (x << 6) –> find last 24 digits
  secret = prune(mix(secret, shift_left(secret, 6)));

  // Calculate the result of dividing the secret number by 32.
  // Round the result down to the nearest integer.
  // Then, mix this result into the secret number.
  // Finally, prune the secret number.
  secret = prune(mix(secret, shift_right(secret, 5)));

  // Calculate the result of multiplying the secret number by 2048.
  // Then, mix this result into the secret number.
  // Finally, prune the secret number.
  return prune(mix(secret, shift_left(secret, 11)));
}

int main() {
  long long int n, ans = 0;
  while (cin >> n) {
    string secret = bit_seq(n);
    for (int i = 0; i < K; i++) {
      secret = next_secret(secret);
    }
    
    ans += to_decimal(secret);
  }
  cout << ans << endl;
  return 0;
}


// 20068964552
