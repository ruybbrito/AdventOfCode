#include <iostream>

typedef long long int ll;

using namespace std;

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

string next_power(const string &a) {
    string ret = "1";
    for (int i = 0; i < a.size(); i++) ret.push_back('0');
    return ret;
}

string next_int(const string &a) {
    ll num = stoll(a);
    return to_string(num+1);
}

int main() {
  string s;
  cin >> s;
  vector<string> ps = split(s, ",");
  ll ans = 0;
  for (int i = 0; i < ps.size(); i++) {
    vector<string> parts = split(ps[i], "-");
    string a = parts[0];
    string b = parts[1];
    string aa, ab;
    ll num_a = stoll(a);
    ll num_b = stoll(b);
    while (num_a <= num_b) {
        if (a.size() % 1 == 0) {
            aa = a.substr(0, a.size()/2);
            ab = a.substr(a.size()/2);
            if (aa == ab) {
                ans += stoll(a);
            }
            a = next_int(a);
        } else {
            a = next_power(a);
        }
        num_a = stoll(a);
    }
  }
  cout << ans << endl;

  return 0;
}
