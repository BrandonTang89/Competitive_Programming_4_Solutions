/**Kattis - collapse
 * Modified version of Kahn's algorithm. We maintain a queue of all dying islands, then for each
 * dying island, we remove their produce from all islands that receive goods from them. If a
 * receiving island, now has less than enough goods to survive, it is dying and is then added to the
 * queue.
 * 
 * Time: O(E + V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<vector<pair<int, int>>> adjlist;  // v, amt
vector<int> amt_excess, alive;
queue<int> q;
int main() {
    cin >> n;
    adjlist.assign(n, vector<pair<int, int>>());
    amt_excess.assign(n, 0);
    alive.assign(n, 1);

    for (int i = 0; i < n; i++) {
        cin >> amt_excess[i];
        amt_excess[i] *= -1;

        int e;
        cin >> e;
        for (int j = 0; j < e; j++) {
            int v, amt;
            cin >> v >> amt;
            v--;
            adjlist[v].emplace_back(i, amt);
            amt_excess[i] += amt;
        }
    }

    int dead = 0;
    alive[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        dead += 1;
        for (auto& p : adjlist[v]) {
            int u = p.first;
            int amt = p.second;
            if (alive[u]) {
                amt_excess[u] -= amt;
                if (amt_excess[u] < 0) {
                    alive[u] = 0;
                    q.push(u);
                }
            }
        }
    }
    cout << n - dead << endl;

    return 0;
}