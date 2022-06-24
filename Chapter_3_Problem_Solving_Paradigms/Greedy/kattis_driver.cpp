/**Kattis - driver
 * Greedy problem. We do a linear pass on all the gates and at each instance we check if we have
 * enough time to pass through. Else we will do a few back and forths at the minimum cost gap that
 * we have already passed to get enough time to pass through the next gate.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<ll> C, T;
int main() {
    cin >> n;
    C.resize(n);
    T.resize(n);

    C[0] = 0;
    for (int i = 0; i < n - 1; i++) {
        cin >> C[i + 1];
    }
    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }

    ll cur_time = 0, cur_cost = 0, furthest = 0, cur_min = C[1];
    while (furthest != n - 1) {
        cur_time += 1;
        cur_cost += C[furthest + 1];

        ll time_left = T[furthest + 1] - cur_time;
        if (time_left > 0) {  // not enough time has passed yet
            ll reps = ceil(time_left / (2.0));
            cur_cost += reps * 2 * cur_min;
            cur_time += reps * 2;
        }
        furthest++;
        cur_min = min(cur_min, C[furthest + 1]);
    }
    cout << cur_cost << endl;

    return 0;
}