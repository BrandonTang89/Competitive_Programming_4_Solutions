/**Kattis - hidingchickens
 * The problem would be simpler if the fox returned to the root at the end. But it doesn't, so how? Well observe 
 * that we will traverse between the root and each node at least once. The ending essentially allows us to not
 * return one time. So how can we use this? we should greedily select to go to cut away the longest distance between
 * the root and a node. So we use the dp with bitmask technique to find total min distance if the fox
 * returned back to the root at the end, then we minus off this amount.
 * 
 * Time: O(2^N * N), Space: O(2^N)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ld rootx, rooty, x, y;
ld EPS = 1e-9;
pair<ld, ld> holes[21];
pair<ld, ld> root;
int n;

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}

ld memo[(1 << 20) + 9];
ld dp(int mask) {  // ith bit is 1 if ith hole is not filled
    if (abs(memo[mask]+1) > EPS) return memo[mask];
    if (mask == 0) return 0;

    int next_hole = __builtin_ctz(mask);
    ld ans = 2*dist(root, holes[next_hole]) + dp(mask ^ (1 << next_hole));

    int bm = mask;
    bm -= (1 << next_hole);
    // try either going to this hole and back or going to another hole as well
    while (bm){
        int a = __builtin_ctz(bm);
        bm -= (1 << a);
        ans = min(ans, dist(root, holes[a]) + dist(root, holes[next_hole]) + dist(holes[a], holes[next_hole]) + dp(mask^(1<<a)^(1<<next_hole)));
    }

    return memo[mask] = ans;


}
int main() {
    cin >> rootx >> rooty;
    root = {rootx, rooty};
    cin >> n;
    ld furthest_dist = 0;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        holes[i] = {x, y};
        furthest_dist = max(furthest_dist, dist(root, holes[i]));
    }

    for (int i=0; i<(1<<n); i++) {
        memo[i] = -1;
    }

    cout << fixed << setprecision(15);
    cout << dp((1 << n) - 1) - furthest_dist << endl;


    return 0;
}