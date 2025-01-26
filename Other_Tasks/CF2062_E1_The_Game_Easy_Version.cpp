#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int maxi;
vector<int> numMaxInSubtree;
vector<vector<int>> adjlist;
vector<int> value, parent;
void countMaxInSubtree(int u) {
    numMaxInSubtree[u] = (value[u] == maxi);
    for (auto v : adjlist[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        countMaxInSubtree(v);
        numMaxInSubtree[u] += numMaxInSubtree[v];
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        adjlist.assign(n, vector<int>());
        value.assign(n, 0);
        numMaxInSubtree.assign(n, 0);
        maxi = 0;
        
        set<int> svs;
        for (int i = 0; i < n; i++) {
            cin >> value[i];
            maxi = max(maxi, value[i]);
            svs.insert(value[i]);
        }
        vector<int> uniqueVals = vector<int>(svs.begin(), svs.end());
        reverse(uniqueVals.begin(), uniqueVals.end()); // reverse to get the values in decreasing order

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        parent.assign(n, -1);
        parent[0] = 0;
        countMaxInSubtree(0);

        int totalMax = numMaxInSubtree[0];
        if (svs.size() == 1) {
            cout << 0 << endl;
            continue;
        }

        int secondMax = *(--(--svs.end()));

        vector<int> criticalPath;
        int u = 0;
        int prevVal = value[u];
        while (true) {
            criticalPath.push_back(u);

            int newu = -1;
            for (auto v : adjlist[u]) {
                if (v == parent[u]) {
                    continue;
                }
                if (numMaxInSubtree[v] == totalMax) {
                    newu = v;
                }
            }

            if (newu == -1) {
                break;
            }
            u = newu;
        }

        set<int> critpathSet(criticalPath.begin(), criticalPath.end());
        vector<int> critNodeToIdx(n, -1);
        for (int i = 0; i < criticalPath.size(); i++) {
            critNodeToIdx[criticalPath[i]] = i;
        }

        map<int, vector<int>> m;
        for (int i = 0; i < n; i++) {
            m[value[i]].push_back(i);
        }


        int curEnd = criticalPath.size() - 1;
        int ans = 0;
        for (int i = 1; i < uniqueVals.size() && !ans; i++) { // iterate over unique values in decreasing order
            int val = uniqueVals[i];
            int newEnd = curEnd;
            for (auto u : m[val]) {
                if (critpathSet.find(u) == critpathSet.end()) { // if we find this value not on a critical path, we can pick it
                    ans = u + 1;
                    break;
                }

                assert(critNodeToIdx[u] != -1);
                if (critNodeToIdx[u] > curEnd) {    // if we find a node of this value deeper than a node of a bigger value, we can pick it
                    ans = u + 1;
                    break;
                }

                newEnd = min(newEnd, critNodeToIdx[u]);
            }

            curEnd = newEnd;
        }

        cout << ans << endl;
    }

    return 0;
}