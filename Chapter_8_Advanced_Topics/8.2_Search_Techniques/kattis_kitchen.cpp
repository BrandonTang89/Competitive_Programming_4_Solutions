/**Kattis - kitchen
 * Relatively straightforward state-space Dijkstra where the state is the amount of liquid in each
 * of the containers. Note that we can just use a tuple of 5 ints to represent the state, but in the
 * transition, just check src and dest containers from 0..n-1. There may be a lot of states (64^5)
 * but most of these are unaccessible so we just use a map.
 * 
 * Time: O(? log n), Space: O(?) Unable to quantify the space that is actually accessible.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, dest;
vector<int> caps;
map<tuple<int, int, int, int, int>, int> dist;
priority_queue<tuple<int, tuple<int, int, int, int, int>>,
               vector<tuple<int, tuple<int, int, int, int, int>>>,
               greater<tuple<int, tuple<int, int, int, int, int>>>>
    pq;

int main()
{
    cin >> n;
    caps.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> caps[i];
    }
    cin >> dest;
    pq.push(make_tuple(0, make_tuple(caps[0], 0, 0, 0, 0)));

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        pq.pop();
        if (dist[state] < d) continue;

        auto [c1, c2, c3, c4, c5] = state;
        if (c1 == dest) {
            cout << d << endl;
            return 0;
        }
        vector<int> s = {c1, c2, c3, c4, c5};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (s[i] == 0 || s[j] == caps[j]) continue;
                // pour from i to j
                int toPour = min(s[i], caps[j] - s[j]);

                s[i] -= toPour;
                s[j] += toPour;

                auto newState = make_tuple(s[0], s[1], s[2], s[3], s[4]);
                if (dist.count(newState) == 0 || dist[newState] > dist[state] + toPour) {
                    dist[newState] = dist[state] + toPour;
                    pq.push(make_tuple(dist[newState], newState));
                }

                s[i] += toPour;
                s[j] -= toPour;
            }
        }
    }
    cout << "impossible" << endl;
    return 0;
}