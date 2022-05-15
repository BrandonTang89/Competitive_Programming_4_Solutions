/**Kattis - pizza
 * Gradient descent but without decreasing learning rate, just improve until no more
 * improvement.
 * 
 * Time: O((h + w) * hw), Space: O(h * w)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int num_tc;
int h, w;
vector<vector<int>> grid;
int f(int pizr, int pizc){ // sum of euclidean distances between points and (x, y)
    ld res = 0;
    for (int r=0; r<h; r++){
        for (int c=0; c<w; c++){
            res += (abs(pizr - r) + abs(pizc - c))*grid[r][c];
        }
    }
    return res;
}

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int main(){
    cin >> num_tc;
    while (num_tc--){
        cin >> w >> h;
        grid.resize(h, vector<int>(w));
        for (int r=0; r<h; r++){
            for (int c=0; c<w; c++){
                cin >> grid[r][c];
            }
        }

        int cr = 0, cc = 0;
        while (true){
            bool improved = false;
            for (int dir=0; dir<4; dir++){
                ld nr = cr + dr[dir];
                ld nc = cc + dc[dir];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                if (f(nr, nc) < f(cr, cc)){
                    cr = nr;
                    cc = nc;
                    improved = true;
                    break;
                }
            }
            if (!improved) break;
        }
        cout << f(cr, cc) << " blocks" << endl;

    }
    return 0;
}