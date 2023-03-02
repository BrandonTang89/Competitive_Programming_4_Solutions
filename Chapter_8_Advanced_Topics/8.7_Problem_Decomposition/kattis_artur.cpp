/**Kattis - artur
 * Coordinate Geom + Topological Sort. So clearly the sticks form a DAG where there is an edge u->v
 * if u needs to be removed before v. We are trying to find a valid topological ordering on the DAG.
 * The difficult part is determining if we need to remove stick a before stick b.
 *
 * By symmetry, assume the left of a is to the left of b (ax1 <= bx1)
 * I use 3 cases:
 * 1. a is completely to the left of b. No intersection.
 * 2. a is completely vertical, then we see if b1 is above a (we can use either a1 or a2)
 * 3. a is not vertical, then we see if the gradient of a is less than the gradient of (a1, b1)
 *
 * Work out the cases on paper...
 *
 * Debugging: I forgot to set grad as a double... this wasted 30 mins of my time. Assert statements
 * are your friend.
 *
 * Time: O(n^2), Mem: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<tuple<int, int, int, int>> v;
vector<int> topo, visited;
vector<vector<int>> adjlist;

double grad(int x1, int y1, int x2, int y2)
{
    assert(x1 != x2 || y1 != y2);  // not the same point
    if (x1 == x2) return (y2 > y1 ? 1e9 : -1e9);
    return (double)(y2 - y1) / (double)(x2 - x1);
}
void dfs(int u)
{
    visited[u] = 1;
    for (auto v : adjlist[u]) {
        if (!visited[v]) dfs(v);
    }
    topo.push_back(u);
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if (x1 == x2 && y1 > y2) swap(y1, y2);
        v.push_back({x1, y1, x2, y2});
    }
    adjlist.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [ax1, ay1, ax2, ay2] = v[i];
            auto [bx1, by1, bx2, by2] = v[j];
            int a = i, b = j;
            if (ax1 > bx1) {
                swap(ax1, bx1);
                swap(ay1, by1);
                swap(ax2, bx2);
                swap(ay2, by2);
                swap(a, b);
            }

            if (ax2 < bx1) continue;  // no intersection
            if (ax1 == ax2) {
                if (by1 > ay2) {  // a comes before b
                    adjlist[a].push_back(b);
                }
                else {  // b comes before a
                    adjlist[b].push_back(a);
                }
                continue;
            }
            assert(grad(ax1, ay1, ax2, ay2) != grad(ax1, ay1, bx1, by1));
            if (grad(ax1, ay1, ax2, ay2) < grad(ax1, ay1, bx1, by1)) {
                adjlist[a].push_back(b);
            }
            else {
                adjlist[b].push_back(a);
            }
        }
    }
    visited.assign(n, 0);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }
    reverse(topo.begin(), topo.end());
    for (auto x : topo) cout << x + 1 << " ";
    cout << endl;
    return 0;
}