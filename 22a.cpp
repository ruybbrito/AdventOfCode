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
  return s.substr(0, s.size() - n);
}

char ch_xor(char a, char b) {
  return a == b ? '0' : '1';
}

string mix(string a, string b) {
  string c;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  for (int ptr = 0; ptr < max(a.size(), b.size()); ptr++) {
    if (ptr < min(a.size(), b.size())) c.push_back(ch_xor(a[ptr], b[ptr]));
    else if (ptr < a.size()) c.push_back(a[ptr]);
    else if (ptr < b.size()) c.push_back(b[ptr]);
  }
  reverse(c.begin(), c.end());
  return c;
}

string prune(string s) {
  return s.size() <= 24 ? s : s.substr(s.size() - 24); 
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
