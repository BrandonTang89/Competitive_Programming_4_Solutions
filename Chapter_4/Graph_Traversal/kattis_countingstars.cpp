/**Kattis - countinstars
 * Use either DFS or BFS flood fill to count the number of connected components. Easy question.
 * 
 * Time: O(hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w;
string row;
vector<vector<char>> board;
vector<vector<bool>> visited;

void dfs(int x, int y) {
    if (x < 0 || x >= h || y < 0 || y >= w || visited[x][y] || board[x][y] == '#') return;
    visited[x][y] = true;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}
int main(){
    int case_num = 1;
    while (cin >> h >> w){

        board.assign(h, vector<char>(w));
        visited.assign(h, vector<bool>(w, false));
        for (int i = 0; i < h; i++){
            cin >> row;
            for (int j = 0; j < w; j++){
                board[i][j] = row[j];
            }
        }
        int ans = 0;
        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                if (board[i][j] == '-' && !visited[i][j]){
                    ans++;
                    dfs(i, j);
                }
            }
        }
        cout << "Case " << case_num++ << ": " << ans << endl;
    }


    return 0;
}