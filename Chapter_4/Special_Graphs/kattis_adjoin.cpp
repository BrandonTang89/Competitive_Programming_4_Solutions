/* Kattis - adjoin
Given a forest of undirected trees, create a spanning tree with the smallest diameter by
joining the trees in the forest.

Determine the diameter of each tree in the initial forest, then sort by diameter.
We can connect all the centroids to the centroid of the tree of the largest diameter
This will be the gauranteed minimum diameter spanning tree.

This is because this will limit the diameter approximately (+1 sometimes) the largest diameter
of the trees of the forest for most of the cases. for small edge cases like if the largest tree
is a single node or a single edge, the algorithm will still work but the diameter will larger
than that of the largest tree. To prevent having to deal with multiple edge cases, 
we choose to simulation the joining and running the diameter algorithm again!

Note the speed-up technique of last_used_dist to prevent multiple calls to reinitialise dist
Also note how we don't need to reinitialise the parent array.
These 2 improvements allow for 0.05s execution rather than TLE :)

Time: O(n log n) for the sort of the diameters of the forest
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int n, e, u, v, centroid, radius, counter = 1;
int farthest_dist, farthest_node;
vector<vi> adjlist;
vi visited, dist, parent,
    last_used_dist;                 // visited stores whether already processed tree with node
vector<tuple<int, int>> diameters;  // diameter, centroid
void dfs(int u) {
    visited[u] = 1;
    if (dist[u] > farthest_dist) {
        farthest_dist = dist[u];
        farthest_node = u;
    }
    for (int v : adjlist[u]) {
        if (last_used_dist[v] != counter) {
            parent[v] = u;
            dist[v] = dist[u] + 1;
            last_used_dist[v] = counter;
            dfs(v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    adjlist.assign(n, vi());
    visited.assign(n, 0);
    last_used_dist.assign(n, 0);
    dist.assign(n, 0);
    parent.assign(n, -1);
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }

    for (int i = 0; i < n; i++) {
        // if the tree with the node has not been processed, process it
        if (visited[i] == 0) {
            // printf("dfs from %d\n", i);
            farthest_node = i;
            farthest_dist = 0;
            counter++;
            dist[i] = 0;
            last_used_dist[i] = counter;
            dfs(i);
            // printf("node x: %d\n", farthest_node);

            farthest_dist = 0;
            counter++;
            dist[farthest_node] = 0;
            last_used_dist[farthest_node] = counter;
            dfs(farthest_node);

            centroid = farthest_node;
            radius = farthest_dist / 2;
            while (dist[centroid] > radius) {
                centroid = parent[centroid];
            }
            diameters.emplace_back(farthest_dist, centroid);
        }
    }

    // Combine the forest into a spanning tree
    sort(diameters.begin(), diameters.end(), greater<tuple<int, int>>());
    int main_centroid = get<1>(diameters[0]);
    for (int i = 1; i < (int)diameters.size(); i++) {
        // printf("diameter: %d, centroid: %d\n", get<0>(diameters[i]), get<1>(diameters[i]));
        adjlist[get<1>(diameters[i])].emplace_back(main_centroid);
        adjlist[main_centroid].emplace_back(get<1>(diameters[i]));
    }

    // Determine the diameter of the spanning tree and print it
    farthest_dist = 0;
    counter++;
    dist[0] = 0;
    last_used_dist[0] = counter;
    dfs(0);

    farthest_dist = 0;
    counter++;
    dist[farthest_node] = 0;
    last_used_dist[farthest_node] = counter;
    dfs(farthest_node);

    printf("%d\n", farthest_dist);
    return 0;
}