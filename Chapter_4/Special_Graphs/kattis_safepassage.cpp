/* Kattis - safepassage
Observation 1:
    Here the graph looks cyclic, but using intuition, it would make sense that if the cloak
    is on the left, u should run with 2 people if possible, and if the cloak is on the right
    you should run back with only 1 guy. I really can't be bothered to think of a proof, but
    AC is AC. 
    
    Note that I actually didn't bother implementing this speed up at the start,
    I still ACed. So this observation isnt actually that important.

However, that is not that important due to the "generous" time limits. As such,
we can afford to use dijkstra rather than toposort + DAG SSSP. The only annoying
thing is the transitions are quite hard to write. Just go slow and itll be okay.
Notice how I use j == n to denote only 1 guy running. Also by using j = i as the
starting, we ensure n >= j > i >= 0 which prevents (1,0) and (0,1) being both
considered.

Time: O(n^2 * (2^n) log(2^n) = n^3 * 2^n)
Mem: O(2^n)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, u, v, w;
const int INF = 1e9;
vi people;
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>>
    pq;
// (dist, clock pos, bitmask)
vector<vector<int>> dist;  // dist[pos][bm]
int main() {
    fast_cin();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w;
        people.emplace_back(w);
    }
    people.emplace_back(0);
    dist.emplace_back(vector<int>((1 << n), INF));  // dist[0]
    dist.emplace_back(vector<int>((1 << n), INF));  // dist[1]

    dist[0][0] = 0;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
        auto [d, cloak, bm] = pq.top();
        pq.pop();

        if (d > dist[cloak][bm]) continue;  // inferior pair

        // printf("cloak: %d, bm: %d, dist: %d\n", cloak, bm, d);
        if (bm == ((1 << n) - 1)) {  // all on that side
            break;
        }

        int mask = bm;
        if (cloak == 0) {  // cloak on left
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) {  // if ith guy is available on the left
                    for (int j = i; j <= n; j++) {
                        if (i == j) continue;  // important check

                        // run back with 2 person unless last guy left!!
                        if ((j == n)) {
                            if ((1 << __builtin_ctz(mask)) != mask) continue;
                        }

                        if (((mask & (1 << j)) == 0) ||
                            (j == n)) {  // jth guy is also available / no only 1 guy

                            if (j != n) {
                                v = (mask ^ (1 << i)) ^ (1 << j);  // both of them go
                            } else {
                                v = (mask ^ (1 << i));  // one guy go
                            }

                            // usual processes
                            if (dist[cloak][bm] + max(people[i], people[j]) >= dist[1 - cloak][v]) {
                                continue;
                            }

                            dist[1 - cloak][v] = dist[cloak][bm] + max(people[i], people[j]);
                            pq.emplace(dist[1 - cloak][v], 1 - cloak, v);
                        }
                    }
                }
            }
        }
        if (cloak == 1) {  // cloak on right
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i))) {  // if ith guy is available on the right
                    int j = n;            // only run back with 1 guy !!
                    if ((mask & (1 << j)) ||
                        (j == n)) {  // jth guy is also available / no only 1 guy
                        if (j != n) {
                            v = (mask ^ (1 << i)) ^ (1 << j);  // both of them go
                        } else {
                            v = (mask ^ (1 << i));  // one guy go
                        }

                        // usual processes
                        if (dist[cloak][bm] + max(people[i], people[j]) >= dist[1 - cloak][v]) {
                            continue;
                        }

                        dist[1 - cloak][v] = dist[cloak][bm] + max(people[i], people[j]);
                        pq.emplace(dist[1 - cloak][v], 1 - cloak, v);
                    }
                }
            }
        }
    }

    cout << dist[1][((1 << n) - 1)] << endl;

    return 0;
}