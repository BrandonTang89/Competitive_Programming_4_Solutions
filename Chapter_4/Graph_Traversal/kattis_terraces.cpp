/* Kattis - terraces

This is a slightlu fancy flood fill question.

Idea 1:
    We can group all connected cells of the same height together into one "pool". Then, if any cell in this pool is
    connected to a lower level cell, it means the pool is invalid. Else it is a valid pool to plant, thus we add 
    the pool size to our answer. We can do the flooding of each pool along with the checking validity together in 1
    run of DFS :)

Time: O(hw), Mem: O(hw)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

bool visited[501][501];
int heights[501][501];
int n, w, h;
int cc_size;
bool valid_pool;

int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};

void dfs(int r, int c){
    visited[r][c] = true;
    cc_size++;
    for (int i=0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr < 0 || nr >= h || nc < 0 || nc >= w)continue;
        if (heights[nr][nc] < heights[r][c])valid_pool = false;
        if (heights[nr][nc] == heights[r][c] && !visited[nr][nc]){
            dfs(nr, nc);
        }
    }
}

int main(){
    fast_cin();
    cin >> w >> h;
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            cin >> heights[r][c];
        }
    }
    int ans = 0;
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            if (!visited[r][c]){
                cc_size = 0;
                valid_pool = true;
                dfs(r, c);
                if(valid_pool)ans += cc_size;
            }
        }
    }

    cout << ans << endl;
    return 0;
}