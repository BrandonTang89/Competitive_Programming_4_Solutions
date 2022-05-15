/* Kattis - coast
This problem can be solved somewhat elegantly by flood filling sea components from the edges to find 
out what is sea and label it. The same flood fill function can then be upgraded to flood fill the
land also and count the length of the coast. One could make a separate function but that would
result in alot of repeated code

Time: O(hw), Mem: (hw)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w;
int coast = 0;
string s;
int grid[1003][1003];
int ct[1003][1003]; //cell type, sea: 0, land: 1, lake: -1

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void flood(int r, int c, int cell_type){
    ct[r][c] = cell_type;

    for (int i=0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w){
            if (cell_type == 1)coast++;
            continue;
        }
        if (cell_type == 1){
            if (ct[nr][nc] == 0){
                coast++;
            }
        }
    
        if (grid[nr][nc] != cell_type)continue; // wrong cell type
        if (ct[nr][nc] != -1)continue; // visited before
        flood(nr, nc, cell_type);
    }
    return;

}


int main(){
    fast_cin();
    memset(ct, -1, sizeof(ct));
    cin >> h >> w;
    for (int r=0;r<h;r++){
        cin >> s;
        for (int c=0; c<w; c++){
            grid[r][c] = (int) (s[c] - '0');
        }
    }

    // for (int r=0;r<h;r++){for (int c=0;c<w;c++){cout << grid[r][c];}cout << endl;}
    // determine the sea tiles
    for (int r=0;r<h;r+=(h-1)){ // 0 and h-1
        for (int c=0;c<w;c++){
            if (ct[r][c] == -1 && grid[r][c] == 0){  //unvisited water tile
                //printf("sea at %d %d\n", r, c);
                flood(r, c, 0);
            }
        }
        if (h == 1)break;
    }
    for (int c=0;c<w;c+=(w-1)){ // c == 0 and c == w-1
        for (int r=0;r<h;r++){ 
            if (ct[r][c] == -1 && grid[r][c] == 0){  //unvisited water tile
                flood(r, c, 0);
            }
        }
        if (w == 1)break;
    }

    
    // determine the land tiles and coast
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            if (ct[r][c] == -1 && grid[r][c] == 1){  //unvisited land tile
                //printf("land at %d %d\n", r, c);
                flood(r, c, 1);
            }
        }
    }
    //for (int r=0;r<h;r++){for (int c=0;c<w;c++){cout << ct[r][c];}cout << endl;}
    cout << coast << endl;


    return 0;
}