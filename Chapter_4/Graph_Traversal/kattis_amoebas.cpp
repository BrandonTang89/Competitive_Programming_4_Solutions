/**Kattis - amoebas
 * Simple floodfill again, we use DFS and the 8 directional dr dc arrays. Count the number of connected
 * components
 * 
 * Time: O(hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, ans = 0;
string row;
vector<vector<char>> grid;
vector<vector<bool>> visited;

// 8 Direction Flood Fill
int dr[] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dc[] = {0, 1, 0, -1, 1, 1, -1, -1};

void dfs(int r, int c){
    visited[r][c] = true;
    for(int i = 0; i < 8; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == '#' && !visited[nr][nc]){
            dfs(nr, nc);
        }
    }
}
int main(){
    cin >> h >> w;
    grid.assign(h, vector<char>(w));
    visited.assign(h, vector<bool>(w, false));
    for(int i = 0; i < h; i++){
        cin >> row;
        for (int j = 0; j < w; j++) {
            grid[i][j] = row[j];
        }
    }

    for (int r=0; r<h; r++) {
        for (int c=0; c<w; c++) {
            if (grid[r][c] == '#' && !visited[r][c]) {
                ans++;
                dfs(r, c);
            }
        }
    }
    cout << ans << endl;
    return 0;
}