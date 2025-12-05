#include <iostream>

typedef long long int ll;

using namespace std;

int main() {
  string s;
  vector<pair<ll, ll> > ranges;
  ll a, b, c;
  int ans = 0;
  while (cin >> s) {
    if (s.find('-') != string::npos) {
        a = stoll(s.substr(0, s.find('-')));
        b = stoll(s.substr(s.find('-')+1, s.length() - s.find('-')));
        ranges.push_back(make_pair(a, b));
    } else {
        c = stoll(s);
        for (int i = 0; i < ranges.size(); i++) {
            if (c >= ranges[i].first && c <= ranges[i].second) {
                ans++;
                break;
            }
        }
    }
  }

  cout << ans << endl;

  return 0;
}
