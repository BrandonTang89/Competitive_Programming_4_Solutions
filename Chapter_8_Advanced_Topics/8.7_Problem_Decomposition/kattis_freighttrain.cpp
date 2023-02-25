/**Kattis - freighttrain
 * BSTA + Greedy Problem. The BSTA component is clear, we binary search for the minimum size of
 * trains that go to Luxembourg. The greedy part is about deciding the minimum number of trains it
 * takes to do the shipments if each train going forward is at most length x. This may take sometime
 * to think about. Let the next (possibly empty) wagon to deal with be at index cur and the next
 * non-empty wagon be at index v[nextwagon].
 *
 * Now, we will have to move the wagon at cur somewhere, either forwards or backwards. If we can
 * cover the wagon at cur and include some wagons from v[nextwagon] to the train without busting the
 * limit, then we do that and send the train forward. This would always be at least as optimal
 * (probably more in most cases) as sending the wagons uptil v[nextwagon] back since we would have
 * less trains to send forward, minimising the total number of trains used.
 *
 * If we cannot cover any amount of wagons from v[nextwagon], then obviously we should send as many
 * empty wagons back as possible (greedily). This ensures that the next train going forward covers
 * as many wagons as possible, minimising the amount of trains needed.
 * 
 * Time: O(W log (N/L)), Mem: O(W)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, w, l;
vector<int> v;

bool check(int x)
{
    // Can we do this with each train taking at most x wagons?
    if (x * l >= n) return true;  // if we can just send all wagons to luxembourg, then we can do it

    int nextwagon = 0;  // v[nextwagon] is the index of the next nonempty wagon
    int cur = 1;        // the index of the next empty/nonempty wagon
    int needed = 0;
    while (nextwagon < w) {
        if (v[nextwagon] - cur < x) {
            needed++;
            cur += x;
            while (nextwagon < w && v[nextwagon] < cur) nextwagon++;
        }
        else {
            needed++;
            cur = v[nextwagon];  // take everything until the next wagon to luxembourg
        }
    }
    if (cur <= n) {  // if we still have some empty wagons left, take them all back
        needed++;
    }
    // cout << "x = " << x << " needed = " << needed << endl;
    return needed <= l;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> w >> l;
        v.resize(w);
        for (int i = 0; i < w; i++) {
            cin >> v[i];
        }
        int le = 1;  // each train at least takes 1 wagon
        int ri =
            (n - 1) / l +
            1;  // each train at most takes ceil(n/l) wagons if we move all of them to luxembourg

        while (le < ri) {
            int mid = (le + ri) / 2;
            if (check(mid)) {
                ri = mid;
            }
            else {
                le = mid + 1;
            }
        }

        cout << le << endl;
    }

    return 0;
}