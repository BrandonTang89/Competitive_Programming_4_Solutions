/**Kattis - draughts
 * Doesn't look that easy but it actually is. Just use the standard design patterns of a recursive backtracking solution:
 * Modify a global state, run a recursive function, then undo the modification.
 * 
 * Time: O(1) (technically speaking), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int t;
char grid[10][10];

int dr[] = {1, 1, -1, -1};
int dc[] = {1, -1, 1, -1};
int bf(int r, int c){
    int possible_cap = 0;
    for (int i=0; i<4; i++){
        if (grid[r+dr[i]][c+dc[i]] != 'B') continue;
        if (grid[r+2*dr[i]][c+2*dc[i]] != '#') continue;

        grid[r+dr[i]][c+dc[i]] = '#';
        possible_cap = max(possible_cap, 1 + bf(r+2*dr[i], c+2*dc[i]));
        grid[r+dr[i]][c+dc[i]] = 'B';
    }
    return possible_cap;
}
int main(){
    cin >> t;
    for (int tc=0; tc<t; tc++){
        for (int r=0; r<10; r++){
            for (int c=0; c<10; c++){
                cin >> grid[r][c];
            }
        }

        int ans = 0;
        for (int r=0; r<10; r++){
            for (int c=0; c<10; c++){
                if (grid[r][c] == 'W'){
                    grid[r][c] = '#';
                    ans = max(ans, bf(r, c));
                    grid[r][c] = 'W';
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}