/**Kattis - nineknights
 * Very easy 2D grid problem.
 * 
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

char board[5][5];

int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool attacking(int r, int c){
    for(int i = 0; i < 8; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0 || nr >= 5 || nc < 0 || nc >= 5) continue;
        if(board[nr][nc] == 'k') return true;
    }
    return false;
}
int main(){
    for (int i=0; i<5; i++){
        cin >> board[i];
    }

    int counter = 0; 
    for (int r=0; r<5; r++){
        for (int c=0; c<5; c++){
            if (board[r][c] == 'k'){
                counter++;
                if (attacking(r, c)){
                    cout << "invalid" << endl;
                    return 0;
                }
            }
        }
    }
    if (counter != 9) cout << "invalid" <<endl;
    else cout << "valid" << endl;

    return 0;
}