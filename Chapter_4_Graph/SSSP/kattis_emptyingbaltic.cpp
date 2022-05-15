/* kattis - emptyingbaltic

Observation 1:
    When considering how much water will eventually be drained from a cell r,c, we realise it is actually
    drained until the level of the minimum max height along all paths from r,c to the drain. This is
    actually similar to the SSSP principle but instead of minimising distance, we minimise the maximum 
    height along the path to get to r,c.

    So our distance values will all be replaced by "minimum max height to get to r,c". And instead
    the the dist to nr, nc being dist(r,c) + w, instead it will be max(grid(nr,nc), ldu(r,c)).

While this problem looks scary cos its some strange variant, once you figure out the observation,
the implementation actually isn't that difficult.

Time: O(hw log hw), Mem: O(hw)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, s_r, s_c;
vector<vector<int>>grid, ldu; //grid slows elevation, ldu (level drained until) shows how far the water level is drained
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
int main(){
    fast_cin();
    cin >> h >> w;
    grid.assign(h, vector<int>(w, 0));
    ldu.assign(h, vector<int>(w, 0));

    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            cin >> grid[r][c];
            grid[r][c] = min(grid[r][c], 0); // we can more or less ignore all heights above 0
        }
    }
    cin >> s_r >> s_c; // starting row and column
    s_r--;
    s_c--;
    pq.emplace(grid[s_r][s_c], s_r, s_c);
    ldu[s_r][s_c] = grid[s_r][s_c];
    
    
    while (!pq.empty()){
        auto [d, r, c] = pq.top();
        pq.pop();
        //printf("d: %d, r: %d, c:%d\n", d, r, c);
        if (d > ldu[r][c])continue; // inferior pair

        for (int i=0;i<8;i++){
            int nc = c + dc[i];
            int nr = r + dr[i];
            if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;

            if (max(ldu[r][c], grid[nr][nc]) >= ldu[nr][nc])continue; // relaxing through this node doesn't help
            ldu[nr][nc] = max(ldu[r][c], grid[nr][nc]); 
            pq.emplace(ldu[nr][nc], nr, nc);
        }
    }

    ll total = 0;
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            //cout << ldu[r][c]<< " ";
            total -= ldu[r][c];
        }
        //cout << endl;
    }
    cout << total << endl;
    return 0;
}