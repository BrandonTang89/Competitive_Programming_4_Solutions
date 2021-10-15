/* Kattis - 10kindsofpeople
A pretty cool flood fill problem. A cool trick is just to use different polarities to indicate
components of binary and decimal seperately. However, a more general version for n different types
of components would be to set the base number to be 0, 1, 2, ..., n-1. And then add n for each
new component. then just use modulo arithmetic to determine the component type :)

Time: O(hw), Mem: O(hw)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, q;
string s;
int binary_counter = -1, decimal_counter = 2; 
int grid[1001][1001];

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void flood(int r, int c){
    int cur_type = grid[r][c];
    if (cur_type == 1){
        grid[r][c] = decimal_counter;
    }
    else if (cur_type == 0){
        grid[r][c] = binary_counter;
    }
    else{
        return;
    }

    for (int i=0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w)continue;
        if (grid[nr][nc] != cur_type)continue;
        flood(nr, nc);
    }
    return;

}

int main(){
    fast_cin();
    cin >> h >> w;
    memset(grid, 0, sizeof(grid));
    
    for (int r=0;r<h;r++){
        cin >> s;
        for (int c=0; c<w; c++){
            grid[r][c] = (int) (s[c] - '0');
        }
    }
    
    for (int r=0;r<h;r++){
        for (int c=0;c<w;c++){
            if (grid[r][c] == 0){
                flood(r, c);
                binary_counter--;
            }
            else if (grid[r][c] == 1){
                //printf("deci at %d %d\n", r, c);
                flood(r,c);
                decimal_counter++;
            }
        }
    }
    
    //for (int r=0;r<h;r++){for (int c=0;c<w;c++){cout << grid[r][c];}cout << endl;}


    cin >> q;
    int r1, c1, r2, c2;
    for (int i=0;i<q;i++){
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        //cout << grid[r1][c1] << " | " <<  grid[r2][c2] << endl;
        if (grid[r1][c1] != grid[r2][c2]){
            cout << "neither" << endl; // different component
        }
        else if (grid[r1][c1] > 1){
            cout << "decimal" << endl;
        }
        else if (grid[r1][c1] < 0){
            cout << "binary" << endl;
        }
    }


    return 0;
}