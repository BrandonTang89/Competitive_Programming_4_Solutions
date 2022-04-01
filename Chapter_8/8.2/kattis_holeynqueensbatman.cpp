/**Kattis - holeynqueensbatman
 * The textbook complete search question. We just slightly modify the ideas/code from CP4 to
 * deal with the holey board.
 * 
 * Time: O(n!!) i have no clue how they pulled this out
 * Space: O(m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int n, m; 
int OK;
ll ans = 0;
vector<int> board; // by column, for use later
void backtrack(int rw, int ld, int rd){
    if (rw == OK){
        ans++;
        return;
    }
    int c = __builtin_popcount(rw);
    int pos = (OK & board[c] & ~(rw | ld | rd));
    while (pos){
        int p = pos & -pos; // possible position of next queen
        pos -= p;
        backtrack(rw | p, (ld | p) << 1, (rd | p) >> 1);
    }
}
int main(){
    while (true){
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        OK = (1 << n) -1;
        board.assign(n, OK);
        for (int i=0; i<m; i++){
            int r, c;
            cin >> r >> c;
            board[c] ^= (1 << r);
        }
        ans = 0;
        backtrack(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}