/* Kattis - blockcrusher
Multiple source Dijkstra flood fill. Its like regular dijkstra but we use the classic flood fill tactics to know where the edges are.
Also we have to print the path

Time: O(hw log hw), Mem: O(hw)
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
int grid[23][63], dist[23][63];
tuple<int,int> parent[23][63];
string line;
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
// pq stores w, r, c
vector<tuple<int,int>> path;

int main(){
    while (true){
        cin >> h >> w;
        if (h == 0)break;
        
        for (int r=0;r<h;r++){
            cin >> line;
            for (int c=0;c<w;c++){
                grid[r][c] = line[c] - '0';
                parent[r][c] = make_tuple(-1, -1);
                dist[r][c] = INT_MAX;
            }
        }

        for (int c=0;c<w;c++){
            pq.emplace(0, 0, c); 
            dist[0][c] = grid[0][c];
        }

        while (!pq.empty()){
            auto [d, r, c] = pq.top();
            pq.pop();
            //printf("d: %d, r: %d, c:%d\n", d, r, c);
            if (d > dist[r][c])continue; // inferior pair
            for (int i=0;i<8;i++){
                int nc = c + dc[i];
                int nr = r + dr[i];
                if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;

                if (dist[r][c] + grid[nr][nc] >= dist[nr][nc])continue; // relaxing through this node doesn't help
                dist[nr][nc] = dist[r][c] + grid[nr][nc];
                parent[nr][nc] = make_tuple(r, c);
                pq.emplace(dist[nr][nc], nr, nc);
            }
        }

        int tr=h-1, tc=0, min_frac = INT_MAX;
        for (int c=0; c<w;c++){
            if (dist[h-1][c] < min_frac){
                tc = c;
                min_frac = dist[h-1][c];
            }
        }

        tuple<int,int> cur_node = make_tuple(tr, tc);
        while (true){
            auto &[r,c] = cur_node;
            grid[r][c] = -1;
            cur_node = parent[r][c];
            if (cur_node == make_tuple(-1,-1))
                break;
        }
        
        for (int r=0;r<h;r++){
            for (int c=0;c<w;c++){
                if (grid[r][c] == -1)cout << " ";
                else cout << grid[r][c];
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}