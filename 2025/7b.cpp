#include <iostream>
#include <set>

typedef long long int ll;

using namespace std;

ll paths[200][200];

int main() {
    string s;
    vector<string> m;
    while (cin >> s) {
        m.push_back(s);
    }

    memset(paths, 0, sizeof paths);

    set<int> c;
    for (int j = 0; j < m[0].size(); j++) {
        if (m[0][j] == 'S') {
            c.insert(j);
            paths[0][j] = 1;
        }
    }

    for (int i = 1; i < m.size(); i++) {
        set<int> nc, sp;
        for (int j = 0; j < m[i].size(); j++) {
            if (m[i][j] == '^' && c.find(j) != c.end()) {
                sp.insert(j);
                if (j > 0) {
                    nc.insert(j-1);
                    paths[i][j-1] += paths[i-1][j];
                }

                if (j+1 < m[i].size()) {
                    nc.insert(j+1);
                    paths[i][j+1] += paths[i-1][j];
                }
            }
        }
        
        for (set<int>::iterator it = sp.begin(); it != sp.end(); it++) {
            c.erase(*it);
            paths[i][*it] = 0;
        }

        for (set<int>::iterator it = c.begin(); it != c.end(); it++) {
            paths[i][*it] += paths[i-1][*it];
        }

        for (set<int>::iterator it = nc.begin(); it != nc.end(); it++) {
            c.insert(*it);
        }
    }

    ll ans = 0;
    for (int j = 0; j < m[0].size(); j++) {
        ans += paths[m.size()-1][j];
    }
    cout << ans << endl;

    return 0;
}


