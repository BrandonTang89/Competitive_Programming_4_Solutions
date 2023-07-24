/**Kattis - jumpingyoshi
 * Relatively fine state-space BFS. The state is (node, status) where status = 0 means the frog is
 * actually there, status = 1 means the frog is jumping forward and is hovering over the node,
 * status = 2 means the frog is jumping backwards and is hovering over the node. Surely you can
 * figure out the rest.
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

int n;
vector<int> arr;
vector<vector<int>> dist;
int maxDist = 0;
queue<pair<int, int>> q;
vector<vector<int>> adjlist1, adjlist2;
int main()
{
    fast_cin();
    cin >> n;
    arr.resize(n);
    adjlist1.assign(n, vector<int>());
    adjlist2.assign(n, vector<int>());

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        int j = i - arr[i];
        if (j >= 0 && j < n) {
            adjlist1[j].push_back(i);
        }
        j = i + arr[i];
        if (j >= 0 && j < n) {
            adjlist2[j].push_back(i);
        }
    }
    dist.assign(n, vector<int>(3, 1e9));
    dist[0][0] = 0;  // dist[u][1] is the jump forward, dist[u][2] is the jump backward
    q.push({0, 0});

    while (!q.empty()) {
        auto [u, k] = q.front();
        q.pop();
        if (k == 0) {
            maxDist = max(maxDist, u);
            int i = u + arr[u];
            if (i >= 0 && i < n && dist[i][1] == 1e9) {
                dist[i][1] = dist[u][k] + 1;
                q.push({i, 1});
            }
            i = u - arr[u];
            if (i >= 0 && i < n && dist[i][2] == 1e9) {
                dist[i][2] = dist[u][k] + 1;
                q.push({i, 2});
            }
        }
        else if (k == 1) {
            for (auto v : adjlist1[u]) {
                if (dist[v][0] == 1e9) {
                    dist[v][0] = dist[u][k] + 1;
                    q.push({v, 0});
                }
            }
        }
        else {
            for (auto v : adjlist2[u]) {
                if (dist[v][0] == 1e9) {
                    dist[v][0] = dist[u][k] + 1;
                    q.push({v, 0});
                }
            }
        }
    }
    cout << maxDist << endl;

    return 0;
}