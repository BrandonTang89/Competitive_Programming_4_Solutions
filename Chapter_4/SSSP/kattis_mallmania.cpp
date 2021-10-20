/* Kattis - mallmania
Since they can start their trip from any part of the perimeter of m1, we just do a multi source
BFS floodfill from all said perimeter cells. We then iterate through the p2 values and get the minimum.

Note that values of coordinates are from 0 to 2000 inclusive. So do the boundary check properly.

Time: O(2000*2000), Mem: O(2000*2000)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<tuple<int,int>> m1, m2; 
int p1, p2, r, c;
int dist[2009][2009];
queue<tuple<int,int>> q;
int dc[] = {0, 0, -1, 1};
int dr[] = {1, -1, 0, 0};

int main(){
    fast_cin();
    while (true){
        cin >> p1;
        if (p1 == 0)break;
        memset(dist, -1, sizeof(dist));
        m1.clear(); m2.clear();

        for (int i=0; i<p1; i++){
            cin >> r >> c;
            m1.emplace_back(r, c);
            dist[r][c] = 0;
            q.emplace(r, c);
        }
        cin >> p2;
        for (int i=0;i<p2;i++){
            cin >> r >> c;
            m2.emplace_back(r, c);
        }   

        while (!q.empty()){
            auto &[r, c] = q.front();
            q.pop();

            for (int i=0;i<4;i++){
                int nc = c + dc[i];
                int nr = r + dr[i];

                if (nc < 0 || nr < 0 || nc > 2000 || nr > 2000)continue;
                if (dist[nr][nc] != -1)continue;

                dist[nr][nc] = dist[r][c] + 1;
                q.emplace(nr, nc);
            }
        }

        int min_dist =  INT_MAX;
        for (int i=0;i<p2;i++){
            auto &[r,c] = m2[i];
            min_dist = min(min_dist, dist[r][c]);
        }

        cout << min_dist << endl;

    }
    return 0;
}