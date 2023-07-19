/** Kattis - mobilization
 * Math + greedy + complete search. The hardest part is the math. First is the obvious observation
 * that we should normalise the health and potency values by dividing by the cost. It immediately
 * follows that if we have a unit (x, y) where health = x and potency = y, as well as another unit
 * with parameters (X, Y) with x <= X and y <= Y then we can discard the first unit immediately.
 *
 * Now we can actually make the further observation that there will be an optimal selection where we
 * will only pick from 2 specific units! Suppose we have 3 units (a, b), (c, d) and (e, f) with a <=
 * c <= e and b >= d >= f. Notice we can form another "virtual unit" with parameters (c. x) from a
 * weighted average of (a, b) and (e, f) since a <= c <= e.
 *
 * If x > d then obviously the (c, d) unit is useless so we are left with 2 units (a, b) and (e, f).
 * Else if the virual unit (c, x) formed has x < d then no optimal configuration will have both (a,
 * b) and (e, f) since we can replace one of them (and decrease the other) with some amount of (c,
 * d).
 *
 * Now inductively apply this on all n unit types to reduce the search space to just 2 unit types.
 *
 * Consider the maximum value attained by only using units (a, b) and (c, d). This is selecting a
 * value of x in [0, 1] such that f(x) = (ax + (1 - x)c)(bx + (1 - x)d) is maximised. This is a
 * quadratic curve that is concave if (a-c)*(b-d) is negative, i.e. we can't prune off either (a, b)
 * or (c, d). In this case, the maximum occurs at the stationary point if it is within the interval
 * [0, 1] else it occurs on the boundary closer to the stationary point. Finding the stationary
 * point can be done analytically and the code to produce it's x value is in the getMax function
 * below.
 *
 * Having all this, we simply do a O(n^2) iterative complete search to get the best value.
 *
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
double budget;

vector<pair<double, double>> arr, pruned;

inline double getMax(double a, double b, double c, double d)
{
    double x = d / (2.0 * (d - b)) + c / (2.0 * (c - a));  // stationary point
    if (x < 0) return (a * b);
    if (x > 1) return (c * d);
    return (a * x + (1 - x) * c) * (b * x + (1 - x) * d);
}
int main()
{
    fast_cin();
    cin >> n >> budget;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        double c;
        cin >> c >> arr[i].first >> arr[i].second;
        arr[i].first = arr[i].first / c;
        arr[i].second = arr[i].second / c;
    }
    sort(arr.begin(), arr.end(), greater<pair<double, double>>());

    pruned.push_back(arr[0]);
    for (int i = 1; i < n; i++) {  // pruning
        if (arr[i].second > pruned.back().second) {
            pruned.push_back(arr[i]);
        }
    }

    n = pruned.size();
    double ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = max(ans,
                      getMax(pruned[i].first, pruned[i].second, pruned[j].first, pruned[j].second));
        }
    }
    cout << fixed << setprecision(10) << ans * budget * budget << endl;
    return 0;
}