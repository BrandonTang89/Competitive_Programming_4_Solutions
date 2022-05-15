/* Kattis - 
This question is 95% identical to millionairemadness. Just that now we can start from any cell
on the left and end on any cell on the right. In this case, MST could be used. However, BSTA
works alot easier due saving effort on converting the graph from a grid to an edge list and 
running kruskal. 

Time: O(hw log ans), where ans ranges from [0, 1e6] (log2 of 1e6 is only 20)
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

bool hit_other_size;
void dfs(int r, int c, int n){
    visited[r][c] = true;
    if (c == w-1){
        hit_other_size = true;
        return;
    }

    for (int i=0; i<4;i++){
        int nc = c + dc[i];
        int nr = r + dr[i];

        if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;
        if (visited[nr][nc])continue;
        if (grid[nr][nc] > n)continue; // can't walk there

        dfs(nr, nc, n);
    }
}

bool can_work(int n){
    memset(visited, 0, sizeof(visited));
    hit_other_size = false;
    for (int i=0; i<h; i++)
        if (grid[i][0] <= n)
            dfs(i, 0, n);
    return hit_other_size;
}
int main(){
    fast_cin();
    ri = 0;
    le = INT_MAX;
    cin >> h >> w;
    for (int r=0;r<h;r++){
        for(int c=0;c<w;c++){
            cin >> grid[r][c];
            ri = max(ri, grid[r][c]);
            le = min(le, grid[r][c]);
        }
    }

    int mid;
    while (le + 1 < ri){
        mid = (le+ri)/2;
        //printf("le: %d, ri: %d, mid: %d\n", le, ri, mid);
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