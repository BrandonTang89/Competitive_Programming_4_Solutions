/* Kattis - islands3
Observation 1:
    Notice that if we start flooding from an island and run into some clouds, we should just
    assume that the cloud is also land so that we can use it to connect to some other land to
    continue maintaining only 1 island!

    However, we should not flood from clouds since the cloud component might itself be an island.

    Thus, we should only flood from land, but when we do so, assume all C as L. Count number of islands

Time: O(wh), Mem: O(wh)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w;
string s;
char grid[1003][1003];
bool visited[1009][1009];

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

// flood all L, convert C into L. then count number of L components
void flood(int r, int c){
    visited[r][c] = true;
    for (int i=0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w){
            continue;
        }
        if (grid[nr][nc] == 'W' || visited[nr][nc] == true)continue;
        flood(nr, nc);
    }
}

int main(){
    fast_cin();
    cin >> h >> w;
    for (int r=0;r<h;r++){
        cin >> s;
        for (int c=0; c<w; c++){
            grid[r][c] = s[c];
        }
    }

    int islands = 0;
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
             if (grid[r][c] == 'L' && visited[r][c] == false){
                 flood(r, c);
                 islands++;
             }
        }
    }
    cout << islands << endl;

    return 0;
}