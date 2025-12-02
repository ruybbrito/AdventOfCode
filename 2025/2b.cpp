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

string next_int(const string &a) {
    ll num = stoll(a);
    return to_string(num+1);
}

bool is_n_partition(const string &a, int n) {
    bool ret = a.size() % n == 0;
    if (!ret) {
        return false;
    }

    for (int i = 0; i+n < a.size(); i++) {
        ret = ret && a[i] == a[i+n];
    }

    return ret;
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
    ll num_a = stoll(a);
    ll num_b = stoll(b);
    while (num_a <= num_b) {
        for (int i = 1; i <= a.size()/2; i++) {
            if (is_n_partition(a, i)) {
                ans += stoll(a);
                break;
            }
        }
        a = next_int(a);
        num_a = stoll(a);
    }
  }
  cout << ans << endl;

  return 0;
}
