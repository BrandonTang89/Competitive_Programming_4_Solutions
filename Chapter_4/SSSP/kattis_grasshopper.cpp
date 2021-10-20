/* Kattis - grasshopper
This is the basic version of knight movement since the constraints are such that we can do a
bfs for every query.

Time: O(num_q * rc), Mem: O(rc)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int h, w, g_r, g_c, l_r, l_c;
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};
vector<vector<int>> dist;
queue<tuple<int,int>> q;

int main(){
    fast_cin();
    while (cin >> h >> w >> g_r >> g_c >> l_r >> l_c){
        g_r--; g_c--; l_r--; l_c--;

        dist.assign(h, vector<int>(w, -1));
        while(!q.empty())q.pop();

        dist[g_r][g_c] = 0;
        q.emplace(g_r, g_c);

        while (!q.empty()){
            auto &[r, c] = q.front();
            q.pop();

            if (r == l_r && c == l_c)break;
            
            for (int i=0;i<8;i++){
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;
                if (dist[nr][nc] != -1)continue;

                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }

        if (dist[l_r][l_c] != -1){
            cout << dist[l_r][l_c] << endl;
        }
        else{
            cout << "impossible" << endl;
        }
    }
    return 0;
}