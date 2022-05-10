/**Kattis - wheretolive
 * Gradient descent but without decreasing learning rate, just improve until no more
 * improvement. We start from lowest possible x and y such that we break ties by not
 * moving without improving.
 * 
 * Time: O(2000*n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;

int n;
vector<pair<ld, ld>> points;
ld f(ld x, ld y){ // sum of euclidean distances between points and (x, y)
    ld res = 0;
    for(auto &p : points){
        ld dx = p.first - x;
        ld dy = p.second - y;
        res += (dx*dx + dy*dy); // least squares cost function
    }
    return res;
}

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int main(){
    while (1){
        cin >> n;
        if (n == 0)break;
        points.clear();
        for (int i=0; i<n; i++){
            ld x, y;
            cin >> x >> y;
            points.emplace_back(x, y);
        }

        int cr = 0, cc = 0;
        while (true){
            bool improved = false;
            for (int dir=0; dir<4; dir++){
                int nr = cr + dr[dir];
                ld nc = cc + dc[dir];
                if (nr < 0 || nr >= 1001 || nc < 0 || nc >= 1001) continue;
                if (f(nr, nc) < f(cr, cc)){ // must improve
                    cr = nr;
                    cc = nc;
                    improved = true;
                    break;
                }
            }
            if (!improved) break;
        }
        cout << cr << " " << cc << endl;

    }
    return 0;
}