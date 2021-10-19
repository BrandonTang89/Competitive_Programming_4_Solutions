/* Kattis - millionairemadness
Despite this problem being listed in the MST topic of CP4, we actually do not use MST to solve it.
This is because usage of MST to solve mini max path problems generally applies to undirected graphs.
However, here we have a directed graph since donald can jump from any heigher mountain to any
lower mountain regardless of ladder size where as he can only climb a height gap equal to the 
height of his ladder.

Thus, we choose to use the BSTA technique since it is obvious that if a height n is possible, all
heights > n are possible while if a height n is not possible, all heights <= n are also not possible.

Time: O(hw log ans), where ans ranges from [0, 1e9]
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, le, ri;
int grid[1009][1009];
bool visited[1009][1009];
int dc[] = {0, 0, 1, -1};
int dr[] = {1, -1, 0, 0};

void dfs(int r, int c, int n){
    visited[r][c] = true;

    for (int i=0; i<4;i++){
        int nc = c + dc[i];
        int nr = r + dr[i];

        if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;
        if (visited[nr][nc])continue;
        if (grid[nr][nc] - grid[r][c] > n)continue;

        dfs(nr, nc, n);
    }
}

bool can_work(int n){
    memset(visited, 0, sizeof(visited));
    dfs(0, 0, n);
    return visited[h-1][w-1];
}
int main(){
    fast_cin();
    le = ri = 0;
    cin >> h >> w;
    for (int r=0;r<h;r++){
        for(int c=0;c<w;c++){
            cin >> grid[r][c];
            ri = max(ri, grid[r][c]);
        }
    }

    int mid;
    while (le + 1 < ri){
        mid = (le+ri)/2;
        if (can_work(mid)){
            ri = mid;
        }
        else{
            le = mid + 1;
        }
    }
    if (can_work(le))ri = le;

    cout << ri << endl; 


    return 0;
}