/**Kattis - starnotatree
 * Reading comprehension + gradient descent. The problem statement itself is long and complex,
 * but its actually not too hard because its just a basic gradient descent with 1 global
 * minima.
 * 
 * Time: O(n), Space: O(n)
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

int n;
vector<pair<ld, ld>> points;
ld f(ld x, ld y){ // sum of euclidean distances between points and (x, y)
    ld res = 0;
    for(auto &p : points){
        ld dx = p.first - x;
        ld dy = p.second - y;
        res += hypot(dx, dy);
    }
    return res;
}

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main(){
    int n;
    cin >> n;
    for (int i=0; i<n; i++){
        ld x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    ld cx = 5000.0, cy = 5000.0;
    for (ld d = 5000.0; d > 1e-12; d *= 0.99){
        for (int dir=0; dir<4; dir++){
            ld nx = cx + d * dx[dir];
            ld ny = cy + d * dy[dir];
            if (f(nx, ny) < f(cx, cy)){
                cx = nx;
                cy = ny;
                break;
            }
        }
    }
    cout << fixed << setprecision(12) << f(cx, cy) << endl;
    

    return 0;
}