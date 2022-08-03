#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, m;
vector<vector<int>> adjmat;
vector<pair<int, string>> ballots;

vector<int> visited;
void dfs(int u) {
    visited[u] = 1;
    for (int i=0; i<n; i++){
        if (i == u || adjmat[u][i] != 1)continue;
        if (visited[i] == 1)continue;
        dfs(i);
    }
}
int main() {
    cin >> n >> m;
    ballots.assign(m, {0, ""});
    for (int i = 0; i < m; i++) {
        cin >> ballots[i].first >> ballots[i].second;
    }
    adjmat.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int i_winning = 0;
            for (auto &[p, s] : ballots) {
                size_t posi = s.find('A' + i);
                size_t posj = s.find('A' + j);

                if (posi < posj) {
                    i_winning += p;
                } else {
                    i_winning -= p;
                }
            }

            if (i_winning > 0) {
                adjmat[i][j] = 1;
            } else {
                adjmat[j][i] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        visited.assign(n, 0);
        dfs(i);
        char c = 'A' + i;
        if (find(visited.begin(), visited.end(), 0) != visited.end()) {
            // cannot win
            cout << c << ": can't win\n";
        } else {
            // can win
            cout << c << ": can win\n";
        }
    }

    return 0;
}