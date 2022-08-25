/**Kattis - hogwarts2
 * Interesting graph modelling question. We construct a statespace graph where each node is a pair
 * (a, b) which represents the person being at node a on the first graph and being at node b on the
 * secoond graph. Then each edge moves from (a, b) to (na, nb). Each node has 4 outgoing edges that
 * correspond to the instruction stating one of the 4 doors. We are looking for whether we can get
 * to (n, _) which means the senior can get to the last room and whether we run into a case where we
 * are at (n, x) where x != n, indicating that the senior can get to the last room in a way that the junior
 * will not be at the last room.
 * 
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adjlist[2];
vector<vector<int>> visited;
bool possible = false;
bool yes = true;
void dfs(int a, int b) {
    visited[a][b] = 1;
    if (a == n) {
        possible = true;
        if (b != n) {
            yes = false;
        }
    }

    for (int i = 0; i < 4; i++) {
        int na = adjlist[0][a][i];
        int nb = adjlist[1][b][i];
        if (visited[na][nb] == 0) {
            dfs(na, nb);
        }
    }
}
int main() {
    cin >> n;
    adjlist[0].assign(n + 1, vector<int>(4, 0));
    adjlist[1].assign(n + 1, vector<int>(4, 0));
    visited.assign(n + 1, vector<int>(n + 1, 0));

    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < 4; i++) {
            cin >> adjlist[0][u][i];
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < 4; i++) {
            cin >> adjlist[1][u][i];
        }
    }
    dfs(1, 1);

    if (possible) {
        if (yes) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}