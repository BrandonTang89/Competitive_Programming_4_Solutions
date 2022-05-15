/* Kattis - flight
Given a spanning tree, remove an edge and create another edge to form a spanning tree with a smaller
diameter

We try removing each edge and then replacing it with the edge between the 2 centers of the resulting
trees. Note the annoying to find edge case where the new edge is the same as the removed edge.

Time: O(V^2), Space: O(V)
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

int n, u, v, farthest_dist, farthest_node, diameter, radius, center;
vector<vi> adjlist;
vector<tuple<int, int>> el;
vi dist, parent, centers, visited;  // parent for center determination

void dfs(int u, int r_u, int r_v) {
    visited[u] = 1;
    if (dist[u] > farthest_dist) {
        farthest_dist = dist[u];
        farthest_node = u;
    }
    for (auto v : adjlist[u]) {
        if (dist[v] == -1) {
            // avoid using the pseudo removed edge
            if (u == r_u || u == r_v) {
                if (v == r_u || v == r_v) continue;
            }
            parent[v] = u;
            dist[v] = dist[u] + 1;
            dfs(v, r_u, r_v);
        }
    }
}

int main() {
    cin >> n;
    adjlist.assign(n, vi());
    parent.assign(n, -1);
    el.clear();
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
        el.push_back(make_tuple(min(u, v), max(u, v)));
    }

    int best_diameter = n;
    int best_ru = 0, best_rv = 0;
    int best_cu = 0, best_cv = 0;
    for (auto &[r_u, r_v] : el) {
        centers.clear();
        visited.assign(n, 0);

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            dist.assign(n, -1);
            farthest_node = i;
            farthest_dist = 0;
            dist[i] = 0;
            dfs(i, r_u, r_v);

            farthest_dist = 0;
            dist.assign(n, -1);
            dist[farthest_node] = 0;
            dfs(farthest_node, r_u, r_v);

            diameter = farthest_dist;
            radius = diameter / 2;
            center = farthest_node;
            while (dist[center] > radius) {
                center = parent[center];
            }
            centers.emplace_back(center);
        }

        // place in the new edge
        adjlist[centers[0]].emplace_back(centers[1]);
        adjlist[centers[1]].emplace_back(centers[0]);

        // determine the diameter
        dist.assign(n, -1);
        farthest_node = 0;
        farthest_dist = 0;
        dist[0] = 0;
        dfs(0, r_u, r_v);

        farthest_dist = 0;
        dist.assign(n, -1);
        parent.assign(n, -1);
        dist[farthest_node] = 0;
        dfs(farthest_node, r_u, r_v);

        diameter = farthest_dist;

        // remove the edges
        adjlist[centers[0]].pop_back();
        adjlist[centers[1]].pop_back();

        // printf("ru: %d, rv: %d, diameter: %d\n", r_u, r_v, diameter);
        // printf("c1: %d, c2: %d\n", centers[0], centers[1]);
        // update best
        if (diameter < best_diameter) {
            if (r_u == min(centers[0], centers[1]) && r_v == max(centers[0], centers[1])) {
                continue;
            }
            best_diameter = diameter;
            best_ru = r_u;
            best_rv = r_v;
            best_cu = centers[0];
            best_cv = centers[1];
        }
    }

    cout << best_diameter << endl;
    cout << min(best_ru + 1, best_rv + 1) << " " << max(best_ru + 1, best_rv + 1) << endl;
    cout << min(best_cu + 1, best_cv + 1) << " " << max(best_cu + 1, best_cv + 1) << endl;
    return 0;
}