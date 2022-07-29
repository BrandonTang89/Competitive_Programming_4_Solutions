/**Kattis - zipline
 * Looks straightforward at a glance, but low-key requires some thinking to get it right.
 * Observe that when the person is x meters from the right wall on a rope of length l and is y
 * meters above the ground, we get the constraint that hypot(h-y, x) + hypot(g-y, w-x) = l. Observe
 * that for each value of x, we can compute the value of l such that y = 0. Let this value of l be
 * l0(x) where l0(x) is a function of x.
 *
 * Notice that for all l<l0(x), the person will never touch the ground at x, for all l>l0(x), the
 * person will intersect the ground at x. But at l=l0, the person will barely scrape the ground,
 * which is the condition that we should be looking for that gives the maximum length of the rope.
 * Plotting l against x while y = 0, we observe that the graph has only 1 minimum point. If we set
 * l to be equal to l0(x) at that minimum point, our person will barely scrape the ground at that
 * point, but not any other points, giving us our maximum length of rope possible.
 *
 * Knowing this, we can ternary search l0(x) to find the x value that minimises l0(x) and thus gives
 * us the maximum length of rope possible.
 * 
 * Note that since r != 0, we should reduce g and h by r to get the correct answer.
 * 
 * Time: O(200), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, w, g, h, r;
int main() {
    cin >> n;
    cout << fixed << setprecision(10);
    for (int tc = 0; tc < n; tc++) {
        cin >> w >> g >> h >> r;
        if (g > h) swap(g, h);
        cout << hypot((h - g), w) << " ";
        g -= r;
        h -= r;

        double lo = 0, hi = w + g + h;
        for (int i = 0; i < 200; i++) {
            double mid_lo = lo + (hi - lo) / 3;
            double mid_hi = hi - (hi - lo) / 3;
            double mid_lo_cost = hypot(h, mid_lo) + hypot(g, w - mid_lo);
            double mid_hi_cost = hypot(h, mid_hi) + hypot(g, w - mid_hi);
            if (mid_lo_cost < mid_hi_cost)
                hi = mid_hi;
            else
                lo = mid_lo;
        }
        cout << hypot(h, lo) + hypot(g, w - lo) << endl;
    }

    return 0;
}