/**Kattis - closestpair1
 * The classic problem. Here we implement the linesweep algorithm which is pretty effective since the
 * points are uniformly distributed!
 * 
 * Time: O(im not sure), Space: O(n)
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

int n, last_point;
pair<ld, ld> points[100009];
set<pair<ld, ld>> s; // here we will store y, x so that it maintains sort by y

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
    return hypot(a.first - b.first, a.second - b.second);
}

int main(){
    cout << fixed << setprecision(2);
    while (1){
        cin >> n;
        if (n == 0)break;
        s.clear();
        last_point = 0;
        for (int i=0; i<n; i++){
            ld x, y;
            cin >> x >> y;
            points[i] = {x, y};
        }
        sort(points, points+n);
        ld ans = 1e12;
        pair<pair<ld, ld>, pair<ld, ld>> ans_pair;
        for (int i=0; i<n; i++){
            while (points[i].first - points[last_point].first >= ans){ // while last point is out of ranges
                s.erase({points[last_point].second, points[last_point].first}); // remove last point
                last_point++;
            }

            auto lo_it = s.lower_bound({points[i].second - ans, -100009.0}); // find the lowest point
            auto hi_it = s.upper_bound({points[i].second + ans, 100009.0}); // find the highest point

            for (auto it = lo_it; it != hi_it; it++){
                ld d = dist(points[i], {it->second, it->first});
                if (ans > d){
                    ans = d;
                    ans_pair = {points[i], {it->second, it->first}};
                }
            }
            s.insert({points[i].second, points[i].first});
        }
        assert(ans < 1e12);
        cout << ans_pair.first.first << " " << ans_pair.first.second << " " << ans_pair.second.first << " " << ans_pair.second.second << endl;
    }

    return 0;
}