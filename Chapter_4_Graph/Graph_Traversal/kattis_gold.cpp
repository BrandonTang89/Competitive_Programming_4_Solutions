/**Kattis - gold
 * BFS floodfill, but with the modification that we don't go to any adjancent cells if there exist
 * a draft, ie there exist a trap that we could potentially go to.
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

int h, w, s_r, s_c;
vector<vector<char>> grid;
vector<vector<int>> dist;
string row;

int dc[] = {0, 1, 0, -1};
int dr[] = {1, 0, -1, 0};

queue<pair<int,int>> q;

int main(){
    cin >> w >> h;
    grid.assign(h, vector<char>(w));
    dist.assign(h, vector<int>(w, -1));
    for (int r=0; r<h; r++){
        cin >> row;
        for (int c=0; c<w; c++){
            grid[r][c] = row[c];
            if (row[c] == 'P'){
                s_r = r;
                s_c = c;
            }
        }
    }
    dist[s_r][s_c] = 0;
    q.push({s_r, s_c});

    int gold = 0;
    while (!q.empty()){
        auto &[r, c] = q.front();
        q.pop();
        gold += (grid[r][c] == 'G');
        bool draft = false;
        for (int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (grid[nr][nc] == '#') continue;
            if (grid[nr][nc] == 'T'){
                draft = true;
                break;
            }
        }
        if (draft) continue;

        for (int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (grid[nr][nc] == '#') continue;
            if (dist[nr][nc] == -1){
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    cout << gold << endl;


    return 0;
}