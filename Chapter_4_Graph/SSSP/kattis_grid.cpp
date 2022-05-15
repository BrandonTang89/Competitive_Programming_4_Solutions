/**Kattis - grid
 * Floodfill with a varying stepsize at different grid cells, just modify the flood fill
 * BFS code slightly.
 *  
 * Time: O(wh), Space: O(wh)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w;
string row;
vector<vector<int>> grid, dist;
queue<tuple<int,int>> q;

int dc[] = {0, 0, 1, -1};
int dr[] = {1, -1, 0, 0};

int main(){
    fast_cin();
    cin >> h >> w;
    grid.assign(h, vector<int>(w, 0));
    dist.assign(h, vector<int>(w, -1));

    for (int r=0; r<h; r++){
        cin >> row;
        for (int c=0; c<w; c++){
            grid[r][c] = row[c] - '0';
        }
    }

    q.push(make_tuple(0,0));
    dist[0][0] = 0;

    while (!q.empty()){
        auto [r, c] = q.front();
        q.pop();
        if (r == h-1 && c == w-1) break;

        for (int i=0; i<4; i++){
            int nr = r + dr[i]*grid[r][c];
            int nc = c + dc[i]*grid[r][c];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push(make_tuple(nr, nc));
        }
    }
    cout << dist[h-1][w-1] << endl;

    return 0;
}