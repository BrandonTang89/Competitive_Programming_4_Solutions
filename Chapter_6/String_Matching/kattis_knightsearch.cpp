/**Kattis - knightsearch
 * Simplish recursive backtracking with knight type movement on a 2D grid.
 * 
 * Time: O(8^10 * n^2) Could be easily optimised with DP to O(n^2 * 10)
 * Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n;
string s = "ICPCASIASG";
vector<vector<char>> board;
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};

// recursive backtracking to find s within board (if possible)
bool can_find(int r, int c, int char_index){
    if(char_index == (int) s.size()){
        return true;
    }
    if(r < 0 || r >= n || c < 0 || c >= n){
        return false;
    }
    if(board[r][c] != s[char_index]){
        return false;
    }
    for(int i = 0; i < 8; i++){
        if(can_find(r + dr[i], c + dc[i], char_index + 1)){
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n;
    board.assign(n, vector<char>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(can_find(i, j, 0)){
                cout << "YES" << endl;
                return 0;
            }
        }
    }
    cout << "NO" << endl;


    return 0;
}