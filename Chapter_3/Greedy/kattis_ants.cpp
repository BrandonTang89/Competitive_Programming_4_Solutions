/**Kattis - ants
 * For the earliest, it is quite obvious that all ants should just walk to the edge nearest to them.
 * For the latest, we cannot do any better than the ant moving away fro mthe edge they are nearest
 * to. This is because when 2 ants collide, instead of viewing it as they are reversing direction,
 * we can just view it as they pass by each other without colliding since the there will still be
 * 1 ant moving to the left of the collision and 1 ant moving to the right of the collision. In this
 * view, there are no collisions and the optimality of the solution is obvious.
 *
 * Time: O(n), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int num_tc, l, n;
int maxi, mini, earliest;
int main() {
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> l >> n;
        maxi = 0;
        mini = INT_MAX;
        earliest = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            maxi = max(maxi, x);
            mini = min(mini, x);
            earliest = max(earliest, min(x, l - x));
        }
        cout << earliest << " " << max(l - mini, maxi) << endl;
    }

    return 0;
}