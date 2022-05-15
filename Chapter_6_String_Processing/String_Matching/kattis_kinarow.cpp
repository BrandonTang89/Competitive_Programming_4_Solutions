/**Kattis - kinarow
 * The key observation is that any winning row/column/diagonal has a left most (or top most)
 * square that we can start at and follow along in one of 4 directions. We just brute force
 * check each square as a candidate starting square and move in all 4 directions.
 * 
 * Time: O(hwk) ~= O(n^3)
 * Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int l, h, w, k;
vector<vector<char>> board;
int dr[] = {1,0,1,1}; // down, right, right down, right up
int dc[] = {0,1,1,-1};

// check for k sym in a row
bool win(int r, int c, int pos, char sym, int dir){
    if (pos == k) return true;
    if (r < 0 || r >= h || c < 0 || c >= w) return false;
    if (board[r][c] != sym) return false;

    // printf("%d %d %d %d\n", r, c, pos, dir);
    return win(r+dr[dir], c+dc[dir], pos+1, sym, dir);
}

int main(){
    fast_cin();
    cin >> l;
    int total_gretel = 0, total_hansel = 0;
    for (int game=0; game<l; game++){
        cin >> w >> h >> k;
        board.assign(h, vector<char>(w));
        for (int i=0; i<h; i++){
            for (int j=0; j<w; j++){
                cin >> board[i][j];
            }
        }
        // gretel -> 'o', hansel -> 'x'
        bool gretel = false;
        bool hansel = false;
        for (int i=0; i<h; i++){
            for (int j=0; j<w; j++){
                if (win(i, j, 0, 'o', 0) || win(i, j, 0, 'o', 1) || win(i, j, 0, 'o', 2) || win(i, j, 0, 'o', 3)){
                    gretel = true;
                }
                if (win(i, j, 0, 'x', 0) || win(i, j, 0, 'x', 1) || win(i, j, 0, 'x', 2) || win(i, j, 0, 'x', 3)){
                    hansel = true;
                }

                if (gretel || hansel) break;
            }
            if (gretel || hansel) break;
        }

        total_gretel += gretel;
        total_hansel += hansel;
    }
    cout << total_hansel << ":" << total_gretel << endl;

    return 0;
}