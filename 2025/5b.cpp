#include <iostream>

typedef long long int ll;

using namespace std;

bool cmp(pair<ll, ll> &a, pair<ll, ll> &b) {
    if (a.first != b.first) {
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

bool overlap(pair<ll, ll> &a, pair<ll, ll> &b) {
    if (a.second < b.first || b.second < a.first) {
        return false;
    }

    return true;
}

pair<ll, ll> combine(pair<ll, ll> &a, pair<ll, ll> &b) {
    return make_pair(min(a.first, b.first), max(a.second, b.second));
}

int main() {
  string s;
  vector<pair<ll, ll> > ranges, final_ranges;
  ll a, b;
  while (cin >> s) {
    if (s.find('-') != string::npos) {
        a = stoll(s.substr(0, s.find('-')));
        b = stoll(s.substr(s.find('-')+1, s.length() - s.find('-')));
        ranges.push_back(make_pair(a, b));
    }
  }

  sort(ranges.begin(), ranges.end(), cmp);

  for (int idx = 0; idx < ranges.size();) {
    pair<ll, ll> base = ranges[idx];
    int i = idx+1;
    for (; i < ranges.size(); i++) {
        if (overlap(base, ranges[i])) {
            base = combine(base, ranges[i]);
        } else {
            final_ranges.push_back(base);
            idx = i;
            break;
        }
    }

    if (i == ranges.size()) {
        final_ranges.push_back(base);
        break;
    }
  }

  ll ans = 0;
  for (int i = 0; i < final_ranges.size(); i++) {
    ans += final_ranges[i].second - final_ranges[i].first + 1;
  }

  cout << ans << endl;

  return 0;
}
