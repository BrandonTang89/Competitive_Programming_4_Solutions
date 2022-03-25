/**Shopee Code League 2022 - Shopee Xpress Delivery
 * Simple flood-fill dijkstra question with extra edges between the nodes with the same value of black hole.
 * 
 * TIme: O(E log V), Memory: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, INF = 1e9;
int grid[1001][1001], dist[1001][1001];
vector<pair<int, int>> holes[255];
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq; // d, r, c

// 4 directional movement
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main(){
    cin >> h >> w;
    for (int i=0; i<h; i++){
        for (int j=0; j<w; j++){
            dist[i][j] = INF;
            cin>>grid[i][j];
            if (grid[i][j] != 0) holes[grid[i][j]].push_back(make_pair(i, j));
        }
    }
    dist[0][0] = 0;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        if (r == h-1 && c == w-1) break;
        pq.pop();
        if (d > dist[r][c]) continue;  // inferior pair
        // check movements to holes
        for (auto [nr, nc] : holes[grid[r][c]]) {
            if (dist[r][c] >= dist[nr][nc])
                continue;
            dist[nr][nc] = dist[r][c];
            pq.emplace(dist[nr][nc], nr, nc);
        }
        for (int i = 0; i < 4; i++) { // regular stuff
            int nc = c + dc[i];
            int nr = r + dr[i];
            if (nc < 0 || nr < 0 || nc >= w || nr >= h) continue;
                    
            // assume the edge weight of all cells to nr, nc is grid[nr][nc]
            if (dist[r][c] + 1 >= dist[nr][nc])
                continue;
            dist[nr][nc] = dist[r][c] + 1;
            pq.emplace(dist[nr][nc], nr, nc);
        }
    }

    cout << dist[h-1][w-1] << endl;

    return 0;
}