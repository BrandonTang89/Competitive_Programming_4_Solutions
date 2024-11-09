#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e;
vector<unordered_set<int>> adjlist;
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> e;
        adjlist.assign(n, unordered_set<int>());

        vector<tuple<int, int, int>> ans;
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist[u].insert(v);
            adjlist[v].insert(u);
        }

        queue<int> q;  // nodes that have > degree 1
        for (int i = 0; i < n; i++) {
            if (adjlist[i].size() > 1) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            while (adjlist[u].size() > 1) {
                int v1 = *adjlist[u].begin();
                int v2 = *(++adjlist[u].begin());
                assert(v1 != v2);

                ans.emplace_back(u, v1, v2);
                adjlist[v2].erase(u);
                adjlist[v1].erase(u);
                adjlist[u].erase(v1);
                adjlist[u].erase(v2);
                if (adjlist[v1].find(v2) == adjlist[v1].end()) {
                    // delete each other too
                    adjlist[v1].insert(v2);
                    adjlist[v2].insert(v1);
                } else {
                    adjlist[v1].erase(v2);
                    adjlist[v2].erase(v1);
                }
            }
        }

        vector<pair<int, int>> pairs;
        vector<int> singles;

        for (int i = 0; i < n; i++) {
            if (adjlist[i].size() == 0) {
                singles.push_back(i);
            } else if (adjlist[i].size() == 1) {
                if (i < *adjlist[i].begin()) pairs.emplace_back(i, *adjlist[i].begin());
            } else {
                assert(false);
            }
        }

        if (pairs.size() == 0) {  // empty
            assert(ans.size() <= 2 * max(n, e));

            cout << ans.size() << endl;
            for (auto [u, v1, v2] : ans) {
                cout << u + 1 << " " << v1 + 1 << " " << v2 + 1 << endl;
            }
            continue;
        }

        // make a tree
        int root = pairs[0].first;
        for (int i = 1; i < pairs.size(); i++) {
            ans.emplace_back(root, pairs[i].first, pairs[i].second);
        }

        int curl = pairs[0].first;
        int curr = pairs[0].second;

        for (auto s : singles) {
            ans.emplace_back(curl, curr, s);
            curr = curl;
            curl = s;
        }

        cout << ans.size() << endl;
        assert(ans.size() <= 2 * max(n, e));
        for (auto [u, v1, v2] : ans) {
            cout << u + 1 << " " << v1 + 1 << " " << v2 + 1 << endl;
        }
    }

    return 0;
}