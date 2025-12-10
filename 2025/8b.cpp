#include <iostream>
#include <set>
#include <map>

typedef long long int ll;

using namespace std;

int mark[1005];

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

ll calc_dist(vector<int> &a, vector<int> &b) {
    ll ans = 0;
    for (int i = 0; i <= 2; i++) {
        ll x = a[i] - b[i];
        ans += x*x;
    }
    return ans;
}

int dfs(map<int, vector<int> > &adj, int x) {
    if (mark[x]) {
        return 0;
    }

    mark[x] = 1;
    int ans = 1;
    
    for (int i = 0; i < adj[x].size(); i++) {
        ans += dfs(adj, adj[x][i]);
    }

    return ans;
}

void print_coordinates(map<int, vector<int> > &ps, int i) {
    cout << ps[i][0] << " " << ps[i][1] << " " << ps[i][2] << endl;
}

int main() {
    string s;
    map<int, vector<int> > ps;

    int idx = 0;
    while (cin >> s) {
        ps[idx++] = split(s, ",");
    }
    
    vector<pair<int, int> > pairs;
    map<pair<int, int>, ll> dist;

    for(int i = 0; i < idx; i++) {
        for (int j = i+1; j < idx; j++) {
            dist[make_pair(i, j)] = calc_dist(ps[i], ps[j]);
            pairs.push_back(make_pair(i, j));
        }
    }

    sort(pairs.begin(), pairs.end(), [&](pair<int, int> a, pair<int, int> b) {
        return dist[a] < dist[b];
    });

    map<int, vector<int> > adj;
    for (int i = 0; i < 5500; i++) {
        adj[pairs[i].first].push_back(pairs[i].second);
        adj[pairs[i].second].push_back(pairs[i].first);

        if (i >= 4500) {
            if (pairs[i].first == 902 || pairs[i].second == 902) {
                cout << pairs[i].first << " " << pairs[i].second << endl;
                print_coordinates(ps, pairs[i].first);
                print_coordinates(ps, pairs[i].second);
                break;
            }
        }
    }

    memset(mark, 0, sizeof mark);

    vector<int> sizes;
    for(int i = 0; i < idx; i++) {
        if (mark[i]) {
            continue;
        }

        int r = dfs(adj, i);
        sizes.push_back(r);
    }

    sort(sizes.begin(), sizes.end());
    for (int i = 0; i < sizes.size(); i++) {
        cout << sizes[i] << endl;
    }

    return 0;
}


