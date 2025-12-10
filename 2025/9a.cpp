#include <iostream>
#include <set>
#include <map>

typedef long long int ll;

using namespace std;

vector<int> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<int> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(stoi(token));
    }

    res.push_back(stoi(s.substr(pos_start)));
    return res;
}

ll area(pair<int, int> &a, pair<int, int> &b) {
    return (long long int)abs(a.first-b.first+1) * (long long int)abs(a.second-b.second+1);
}

int main() {
    string s;
    vector<pair<int, int> > G;
    while (cin >> s) {
        vector<int> v = split(s, ",");
        G.push_back(make_pair(v[0], v[1]));
    }

    ll ans = 0;
    for (int i = 0; i < G.size(); i++) {
        for (int j = i+1; j < G.size(); j++) {
            ans = max(ans, area(G[i], G[j]));
        }
    }

    cout << ans << endl;

    return 0;
}


