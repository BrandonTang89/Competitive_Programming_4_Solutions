/* Kattis - robotsonagrid
A relatively easy question. The trick to not having to deal with all the stupid in-degree
and topological sort issues is to note that the row-major ordering of cells gives a 
topological sort!

Other than that, we have to deal with the annoyingness of an extra DFS subroutine just to check
if the exit is even reachable. Easy but abit waste time.

Also since the sums can get higher than INT limit, use ll for ways.

Time: O(n^2), Mem: O(n^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
string line;
bool grid[1002][1002], visited[1002][1002]; // true if walkable
ll ways[1002][1002];
int dc[] = {1, 0, 0, -1};
int dr[] = {0, 1, -1, 0};
const int MOD = 2147483647;

void dfs(int r, int c){
    visited[r][c] = true;
    for (int i=0; i<4;i++){
        int nc = c + dc[i];
        int nr = r + dr[i];

        if (nc < 0 || nr < 0 || nc >= n || nr >= n)continue;
        if (!grid[nr][nc])continue;
        if (visited[nr][nc])continue;

        dfs(nr, nc);
    }

}

int main(){
    fast_cin();
    cin >> n;
    for (int r=0;r<n;r++){
        cin >> line;
        for (int c=0;c<n;c++){
            grid[r][c] = (line[c] == '.' ? true : false);
        }
    }

    ways[0][0] = 1;
    for (int r=0;r<n;r++){
        for (int c=0;c<n;c++){
            if (!grid[r][c])continue;
            
            for (int i=0; i<2;i++){
                int nc = c + dc[i];
                int nr = r + dr[i];

                if (nc < 0 || nr < 0 || nc >= n || nr >= n)continue;
                if (!grid[nr][nc])continue;

                ways[nr][nc] += ways[r][c];
                ways[nr][nc] %= MOD;
            }
        }
    }
    dfs(0, 0);

    if (ways[n-1][n-1]){
        cout << ways[n-1][n-1] << endl;
    }
    else if (visited[n-1][n-1]){
        cout << "THE GAME IS A LIE" << endl;
    }
    else{
        cout << "INCONCEIVABLE" << endl;
    }
        
    return 0;
}