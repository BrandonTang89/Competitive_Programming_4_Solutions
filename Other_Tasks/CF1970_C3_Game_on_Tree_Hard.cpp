/**CF1970 C3
 * We use dp(e) to compute if the player now playing wins assuming we have just traversed the
 * directed edge e so we are confined to that specific subtree. We add fake edges for the start of
 * each game.
 *
 * Time: O(n), Space: O(n)
 */
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

int n, t;
vector<vector<pair<int, int>>> adjlist;  // adjlist[u] = {<v1, edgeIndex>, <v2, edgeIndex>, ...}
vector<int> from, to;
int eidx = 0;

vector<int> memo;
int dp(int ein)
{
    if (memo[ein] != -1) return memo[ein];

    int u = (ein < eidx) ? to[ein] : (ein - eidx);
    int parent = (ein < eidx) ? from[ein] : -1;

    bool win = false;
    for (auto &[v, e] : adjlist[u]) {
        if (v == parent) continue;
        if (!dp(e)) win = true;
    }
    if (win) return memo[ein] = 1;
    return memo[ein] = 0;
}
int main()
{
    fast_cin();
    cin >> n >> t;
    adjlist.resize(n);
    from.resize(2 * n);
    to.resize(2 * n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].emplace_back(v, eidx++);
        from[eidx - 1] = u;
        to[eidx - 1] = v;
        adjlist[v].emplace_back(u, eidx++);
        from[eidx - 1] = v;
        to[eidx - 1] = u;
    }

    memo.resize(3 * n, -1);

    for (int i = 0; i < t; i++) {
        int start;
        cin >> start;
        start--;

        if (dp(eidx + start))
            cout << "Ron\n";
        else
            cout << "Hermione\n";
    }
    return 0;
}