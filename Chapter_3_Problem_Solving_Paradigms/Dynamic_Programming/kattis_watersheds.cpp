/**Kattis - watersheds
 * Relatively easy dp, the state is the position and the transition is to set the value of the pos to
 * the value of the pos where the water flows to if the pos is not a sink or to the next value if the pos
 * is a sink.
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

int h, w, num_sinks;
int dr[] = {-1, 0, 0, 1}; // North, West, East, South
int dc[] = {0, -1, 1, 0};
vector<vector<int>> grid, memo;

int dp(int r, int c){
    if (memo[r][c] != -1) return memo [r][c];
    int smallest_dir = -1, cur_smallest = grid[r][c];
    for (int i=0; i<4; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] < cur_smallest){
            smallest_dir = i;
            cur_smallest = grid[nr][nc];
        }
    }

    if (smallest_dir == -1){
        // sink
        return memo[r][c] = num_sinks++;
    }
    return memo[r][c] = dp(r + dr[smallest_dir], c + dc[smallest_dir]);
}
int main(){
    int num_tc;
    cin >> num_tc;
    for (int tc=0; tc<num_tc; tc++){
        cout << "Case #" << tc+1 << ":\n";
        cin >> h >> w;
        grid.assign(h, vi(w, 0));
        memo.assign(h, vi(w, -1));
        num_sinks = 0;
        for (int r=0; r<h; r++){
            for (int c=0; c<w; c++){
                cin >> grid[r][c];
            }
        }
        
        for (int r=0; r<h; r++){
            for (int c=0; c<w; c++){
                cout << (char)('a'+dp(r, c)) << " ";
            }
            cout << endl;
        }
    }

    return 0;
}