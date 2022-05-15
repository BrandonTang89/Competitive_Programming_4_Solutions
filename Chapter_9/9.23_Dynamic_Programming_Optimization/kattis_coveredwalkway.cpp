/**kattis - coveredwalkway
 * Dynamic programming with convex hull speed up (but with congruent parabolas rather than lines).
 * Let g[i] be the position of point i. Let dp(i) be the cost of covering the first i points. dp(i)
 * = min(dp(j-1) + cost(g[i], g[j])) for j = 1..i where cost(x, y) is the cost of using 1 cover to
 * cover from x to y. Cost(x, y) = c + (x
 * - y)^2.
 *
 * Letting dp(i) = y, g[i] = x, dp(j-1) be c_j, g[j] = m_j, we get that y = min(c_j + c + (x -
 * m_j)^2) for j = 1..i. Ie we are getting the bottom "convex hull" of the set of parabolas (from 1
 * to i). Notice that since m_j and c_j are non-decreasing, we can use the convex hull technique to
 * add curves to a set of "important" curves in amortised O(1) time by merely checking the last
 * added curve and seeing if adding the new curve makes the last curve useless!
 *
 * Let opt(i) be argmin(dp(j-1) + cost(g[i], g[j])) for j = 1..i. We can observe that opt(i) <=
 * opt(i+1) for all i this means that after finding the opt(i) while computing dp(i), we only need
 * to check from opt(i) onward to get dp(i+1), ie after finding the index of the minimum parabola
 * for dp(i), the index of the minimum parabola for dp(i+1) must be at least as large as the index
 * of the minimum parabola for dp(i). This allows us to compute dp(0)..dp(n-1) in O(n) amortised
 * time!
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, c;
const double INF = 1e12, EPS = 1e-12;
struct tcurve {
    ll m, c;   // y = c_global + c + (x - m)^2
    double p;  // x value of intersection between this curve and previous curve
};
vector<tcurve> curves;

double getX(ll m1, ll c1, ll m2, ll c2) {  // compute x position of intersection of curves
    return ((double)(m1 * m1 - m2 * m2 + c1 - c2)) / ((double)(2 * (m1 - m2)));
}

void addcurve(ll m, ll c) {
    double p = -INF;
    while (!curves.empty()) {
        p = getX(curves.back().m, curves.back().c, m, c);
        if (p < curves.back().p - EPS)  // curves.back() is useless
            curves.pop_back();
        else
            break;
    }
    curves.push_back((tcurve){m, c, p});
}

ll k = 0;  // global variable that tracks where we left off, ie opt(i-1)
ll getBestY(ll x) {
    k = min(k, (ll)curves.size());
    while (k + 1 < (int)curves.size() && curves[k + 1].p <= x + EPS) k++;  // increase linearly
    return (c + curves[k].c + (x - curves[k].m) * (x - curves[k].m));
}

int main() {
    cin >> n >> c;
    ll ans = 0;
    vector<ll> g(n);

    for (int i = 0; i < n; i++) {
        cin >> g[i];
        addcurve(g[i], ans);
        ans = getBestY(g[i]);
    }
    cout << ans << endl;
    return 0;
}