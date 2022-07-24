/**Kattis - qanat
 * Interesting problem. If we have 0 vertical shafts, we can compute the minimum cost in O(1) by
 * moving each piece of dirt to the nearer of 2 holes. If we have 1 shaft, we can ternary search for
 * the location of the shaft, at each interation, we can compute the cost of moving the dirt on the
 * right of the shaft to either that hole or to the mother hole. We then realise that we are left
 * with the 0 shaft case on the left side, albeit a smaller version of the triangle, but still a
 * similar triangle! As such, we can deal with this sub-problem that we have solved already. 
 * 
 * Generally, if we have solved the sub problem of i-1 shafts, we can solve the sub problem of i holes
 * by ternary searching for the ith hole and using the solution of the sub problem of i-1 holes.
 * 
 * Time: O(n * 100), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;


typedef long double ld;

ld w, h, ah;
int n;
vector<pair<ld, ld>> memo;  // position of shift (assuming width 1), total cost

ld right_cost(ld pos) {
    ld vertical_height = pos * ah;
    ld total_length = vertical_height + ah + (1.0 - pos);
    return (total_length / 2.0) * (total_length / 2.0) -
           (vertical_height) * (vertical_height) / 2.0;
}
int main() {
    cin >> w >> h >> n;
    memo.assign(n + 1, {0, 0});

    ah = h / w;                                              // adjusted height
    memo[0] = {0, ((ah + 1.0) / 2.0) * ((ah + 1.0) / 2.0)};  // assume no vertical shafts needed

    for (int shaft = 1; shaft <= n; shaft++) {
        ld hi = 1.0, lo = 0.0;
        for (int i = 0; i < 100; i++) {
            ld mid_lo = lo + (hi - lo) / 3.0;
            ld mid_hi = hi - (hi - lo) / 3.0;

            ld mid_lo_cost = right_cost(mid_lo) + memo[shaft - 1].second * mid_lo * mid_lo;
            ld mid_hi_cost = right_cost(mid_hi) + memo[shaft - 1].second * mid_hi * mid_hi;

            if (mid_lo_cost < mid_hi_cost) {
                hi = mid_hi;
            } else {
                lo = mid_lo;
            }
        }
        memo[shaft] = {lo, right_cost(lo) + memo[shaft - 1].second * lo * lo};
    }
    cout << fixed << setprecision(10);
    cout << memo[n].second * w * w << endl;
    ld mul = w;
    vector<ld> ans(n);
    for (int i = n; i > 0; i--) {
        mul *= memo[i].first;
        ans[i - 1] = mul;
    }
    for (int i = 0; i < min(n, 10); i++) {
        cout << ans[i] << endl;
    }

    return 0;
}