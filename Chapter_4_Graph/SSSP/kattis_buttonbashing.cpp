/**Kattis - buttonbashing
 * BFS on implicit graph. Nodes are all values from 0 to 3600. This is basically a much easier 
 * version of the problem 246greaaat which was really hard.
 * 
 * Time: O(e*3600), Space: O(3600 + e)
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

vi dist;
queue<int> q;
const int INF = 1e9;
int e, v, num_tc, dest, n;
vector<int> transitions;
int main() {
    fast_cin();
    cin >> num_tc;
    n = 3601;
    for (int tc = 0; tc < num_tc; tc++) {
        dist.assign(n, INF);  // INF = 1e9 here
        transitions.clear();

        cin >> e >> dest;
        for (int i = 0; i < e; i++) {
            cin >> v;
            transitions.push_back(v);
        }
        dist[0] = 0;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto d : transitions) {  // C++17 style, w ignored
                v = u + d;
                v = max(0, v);
                v = min(v, n - 1);
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;  // dist[v] != INF now
                    q.push(v);              // for next iteration
                }
            }
        }

        for (int i=dest; i<n; i++) {
            if (dist[i] != INF) {
                printf("%d %d\n", dist[i], i - dest);
                break;
            }
        }
    }

    return 0;
}