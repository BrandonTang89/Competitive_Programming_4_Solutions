/**Kattis - grapevine
 * Modified Kahn's algorithm, given several nodes that are ready to spread the rumour, we propogate
 * the one that is ready to spread the rumour the earliest. The moment a node has had enough people
 * tell him, we can then just add him the the queue of ready to spread.
 * 
 * Time: O(V log V + E), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> mp;
vector<int> t, heard;
vector<vector<int>> adjlist;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // min heap
int n, e, d;
int main() {
    cin >> n >> e >> d;
    adjlist.assign(n, vector<int>());
    t.assign(n, 0);
    heard.assign(n, 0);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s >> t[i];
        mp[s] = i;
    }
    for (int i = 0; i < e; i++) {
        string u, v;
        cin >> u >> v;
        adjlist[mp[u]].emplace_back(mp[v]);
        adjlist[mp[v]].emplace_back(mp[u]);
    }

    string r;
    cin >> r;

    int ans = 0;
    pq.push({0, mp[r]});
    heard[mp[r]] = 1;

    while (!pq.empty()) {
        auto [time, u] = pq.top();
        pq.pop();
        if (time >= d) break;
        for (int v : adjlist[u]) {
            if (!heard[v]) {
                heard[v] = 1;
                ans++;
            }
            t[v]--;
            if (t[v] == 0) {
                pq.push({time + 1, v});
            }
        }
    }
    cout << ans << endl;

    return 0;
}