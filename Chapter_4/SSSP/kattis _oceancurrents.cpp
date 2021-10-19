/* Kattis - oceancurrents
A "classic" 0-1 BFS floodfill question. Just implement carefully and correctly.
Note that we can't just blindly do BFS, we need to treat this as weighted SSSP and do the check for more optimal distance.

Time: O(wh* num_q), Mem: O(wh)
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
int grid[1009][1009], dist[1009][1009];

int num_q, sr, sc, tr, tc;
string line;
deque<pair<int,int>> q;
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

int main(){
    cin >> h >> w;
    for (int r=0;r<h;r++){
        cin >> line;
        for (int c=0;c<w;c++){
            grid[r][c] = line[c] - '0';
        }
    }


    cin >> num_q;
    for (int query=0; query<num_q; query++){
        cin >> sr >> sc >> tr >> tc;
        sr--; sc--; tr--; tc--;
        memset(dist, -1, sizeof(dist)); // all unvisited
        q.clear();

        q.emplace_back(sr, sc);
        dist[sr][sc] = 0;

        while(!q.empty()){
            int r = q.front().first;
            int c = q.front().second; 
            //printf("%d, %d, %d\n", r, c, dist[r][c]);
            q.pop_front(); 

            if (r == tr && c == tc)break;

            for (int i=0;i<8; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nc < 0 || nr < 0 || nc >= w || nr >= h)continue;
                if (dist[nr][nc] != -1){
                    if (dist[nr][nc] <= dist[r][c] + (i == grid[r][c] ? 0 : 1)){ // if we can't improve this further
                        continue;
                    }
                };

                dist[nr][nc]  = dist[r][c] + (i == grid[r][c] ? 0 : 1); 
                if (i == grid[r][c]){
                    q.emplace_front(nr, nc);
                }
                else{
                    q.emplace_back(nr, nc);
                }
            }
        }
        cout << dist[tr][tc] << endl;
    }

    return 0;
}